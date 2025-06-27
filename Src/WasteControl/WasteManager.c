/*
 * WasteManagerControl.c
 *
 *  Created on: 2021年10月11日
 *      Author: liwenqin
 */

#include "FreeRTOS.h"
#include "task.h"
#include "timers.h"
#include "SystemConfig.h"
#include "Common/Types.h"
#include "WasteManager.h"
#include "Tracer/Trace.h"
#include "DNCP/App/DscpSysDefine.h"
#include "SystemConfig.h"
#include "DNCP/Lai/LaiRS485Handler.h"
#include "DncpStack/DncpStack.h"
#include "System.h"
#include "Driver/UartDriver/Communication.h"
#include "Driver/DeviceIndicatorLED.h"
#include "Driver/HardwareType.h"

#define PUMP_COLLECT_CELL 0  //收集池泵索引
#define PUMP_CYCLE_CELL   1  //循环池索引
#define PUMP_MAX_VALUME  100000
#define PUMP_SPEED  0.25
#define PUMP_ACC  0.2

#define CMD_SYSTEM_STOP 		1 //全部停止
#define CMD_COLLECT_CELL_STOP   2 //停止收集池抽液
#define CMD_CYCLE_CELL_STOP		3 //停止循环池排液
#define CMD_CYCLE_HANDLE_STOP	4 //停止循环池废水处理
#define CMD_SYS_RESET 			5 //系统复位
#define CMD_COLLECT_PUMP_DRAIN	6 //收集池泵排液
#define CMD_COLLECT_PUMP_SUCK	7 //收集池泵抽液
#define CMD_CYCLE_PUMP_DRAIN	8 //循环池泵排液
#define CMD_CYCLE_PUMP_SUCK	    9 //循环池泵抽液

#define VALVE_OPEN				03
#define VALVE_CLOSE				01

// LaiRS485指令 定义
#define CMD_HOLD                3
#define CMD_READ                4
#define CMD_WRITE               6
// LaiRS485寄存器地址 定义
#define REGISTER_STATUS         0
#define REGISTER_CONTROL        1

// 寄存器定义
typedef enum
{
    SystemStatus = 0x00,		//读系统状态
    ErrorCode = 0x01,			//读错误代码
    CollectPumpParam = 0x02,	//读收集池泵参数
	CyclePumpParam = 0x03,		//读循环池泵参数
	CycleDeviceParam = 0x04,	//读净化设备参数
	ControlCode = 0x10,		    //写控制指令
	SetCollectPumpParam = 0x11, //写收集池泵参数
	SetCyclePumpParam = 0x12,   //写循环池泵参数
	SetCycleDeviceParam = 0x13  //写净化设备参数
}RegisterMap;

// 系统状态定义
typedef enum
{
    CollectCell_Start = 1,		//收集池启动
	CollectCell_Working = 2,    //收集池工作
	CollectCell_Delay = 3,      //收集池过抽
	CycleCell_Start = 4,		//循环池启动
	CycleCell_Working = 5,	    //循环池工作
	CycleCell_Emptying = 6,		//循环池排空
	CollectCell_WorkingOnly = 7,//仅收集池工作
	CycleCell_WorkingOnly = 8,  //仅循环池工作
}SysSatus;

// 错误码定义
typedef enum
{
    CollectCell_Normal = 0,			//收集池正常
	CollectCell_Error_Full = 1,    //收集池液位告警
	CollectCell_Error_Dangerous = 2,//收集池溢出告警
	CycleCell_Normal = 10,			//循环池正常
	CycleCell_Error_Full = 11,		//循环池液位告警
	CollectCell_Pump_Normal = 20,	//收集池泵正常
	CollectCell_Pump_Error = 21,	//收集池泵异常告警
	CycleCell_Pump_Normal = 22,		//循环池泵正常
	CycleCell_Pump_Error = 23,		//循环池泵异常告警
	CycleCell_Device_Error = 30,    //循环池设备异常
}ErrCode;

//废水系统
typedef struct
{
	SysSatus sysStatus;			//系统状态
	ErrCode	 collectCell;		//收集池状态
	ErrCode	 collectPump;		//收集池泵状态
	ErrCode  cycleCell;			//循环池状态
	ErrCode  cyclePump;			//循环池泵状态
	int collectPumpSuckTime;    //收集池泵抽液时长
	Uint16 collectPumpDelayTime;//收集池泵过抽时长
	int collectPumpTimeout;		//收集池泵超时时长
	int collectPumpTimecnt;	    //收集池泵计时
	int cyclePumpDrainTime;		//循环池泵排液时长
	int cyclePumpTimeout;		//循环池泵超时时长
	int cyclePumpTimecnt;	    //循环池泵计时
	int cycleHandleTime;	    //循环池设备工作时间
	int cycleWaterInTime;		//循环设备进水时间
	int cyclePowerOnDrainTime;  //循环设备进水完成后反排时间
	int cyclePowerOnSuckTime;   //循环设备进水完成后抽水时间
}WasteUnit;

// 收集池传感器定义
typedef enum
{
    Collect_High = 2,
    Collect_Middle = 1,
    Collecl_Low = 0,
}CollectCellSensor;

// 循环池传感器定义
typedef enum
{
    Cycle_High = 4,
    Cycle_Low = 3,
	Cycle_DeviceOutput = 6,//设备完成信号
}CycleCellSensor;

// 泵方向定义 0-逆时针, 1-顺时针
typedef enum
{
	Drain_Collect = 1,
	Suck_Collect = 0,
	Drain_Cycle = 1,
	Suck_Cycle = 0,
}DrainDir;

//上电状态
typedef enum
{
	PowerOn_DrainStart = 0,
	PowerOn_WaitEmpty = 1,
	PowerOn_SuckStart = 2,
	PowerOn_Idle = 3,
}PowerStatus;

static void WasteManager_CollectCellTaskHandle(void *pvParameters);
static void WasteManager_CycleCellTaskHandle(void *pvParameters);
static void WasteManager_InputDetectTaskHandle(void *pvParameters);

static xTaskHandle s_xCollectCellHandle;
static xTaskHandle s_xCycleCellHandle;
static xTaskHandle s_xInputHandle;
static int s_period = 1000;
static Uint8 s_tempValue[4] = {100,100,100,100};
static Bool s_debugMode = FALSE;

Byte s_sendBuf[8] = {0x01,0x04,0x00,0x01,0x00,0x00,0x00,0x00};
Byte s_sendBufMult[20] = {0};

#define MODE_DEBUG 	0

void WasteManager_Init(void)
{
	s_sendBuf[0] = HardwareType_GetAddr();//初始化设备地址
	s_sendBufMult[0] = HardwareType_GetAddr();//初始化设备地址
    xTaskCreate(WasteManager_InputDetectTaskHandle, "InputDetectTaskHandle", 256, NULL,
              		     6, &s_xInputHandle);
}

void WasteManager_StopAll(void)
{
	vTaskSuspend(s_xCycleCellHandle);
	vTaskSuspend(s_xCollectCellHandle);
	Printf("\n Stop All Task");
}

void WasteManager_StopCollectTask(void)
{
	vTaskSuspend(s_xCollectCellHandle);
	Printf("\n Stop Collect Cell Task");
}

void WasteManager_StopCycleTask(void)
{	
	vTaskSuspend(s_xCycleCellHandle);
	Printf("\n Stop Cycle Cell Task");
}

void WasteManager_ModbusPump(Uint8 index, DrainDir dir, float vol)
{
	Printf("\n Modbus Pump[%d] dir %d, vol %f",index, dir, vol);
}

void WasteManager_ErrorEvent(Uint16 code)
{
	s_sendBuf[1] = CMD_READ;
	s_sendBuf[3] = ErrorCode;
	s_sendBuf[5] = code;
	LaiRS485_ModbuSend(s_sendBuf, sizeof(s_sendBuf));
}

void WasteManager_Cmd(Uint8 cmd, Uint16 reg, Uint16 param)
{
	switch(cmd)
	{
		case CMD_READ: //读指令
			Printf("\n [Modbus] Read %d, %d", reg, param);
			for(Uint8 j = 0;j<param;j++)
			{
				Uint16 temp = Communication_GetCurrentDisplay(j+reg);
				s_sendBufMult[3+j*2] = (temp >> 8) & 0xFF;
				s_sendBufMult[4+j*2] = temp & 0xFF;
			}
			s_sendBufMult[1] = CMD_READ;
			s_sendBufMult[2] = param*2;
			LaiRS485_ModbuSend(s_sendBufMult, (3+param*2+2));
			break;
		case CMD_WRITE:
			Printf("\n [Modbus] Write %d, %d", reg ,param);
			if(reg<4)
			{
				s_tempValue[reg] = param;
			}
			else
			{
				Printf("\n [Modbus] Write Error index[%d]", reg);
			}
			s_sendBuf[1] = CMD_WRITE;
			s_sendBuf[2] = 0;
			s_sendBuf[3] = reg;
			s_sendBuf[4] = (param >> 8) & 0xFF;
			s_sendBuf[5] = param & 0xFF;
			LaiRS485_ModbuSend(s_sendBuf, sizeof(s_sendBuf));
			break;
		case CMD_HOLD:
			Printf("\n [Modbus] Hold %d, %d", reg ,param);
			for(Uint8 j = 0;j<param;j++)
			{
				Uint16 temp = Communication_GetCurrentDisplay(j+reg);
				s_sendBufMult[3+j*2] = (temp >> 8) & 0xFF;
				s_sendBufMult[4+j*2] = temp & 0xFF;
			}
			s_sendBufMult[1] = CMD_HOLD;
			s_sendBufMult[2] = param*2;
			LaiRS485_ModbuSend(s_sendBufMult, (3+param*2+2));
			break;
		default :
			Printf("\nInvalid Cmd %d",cmd);
	}
}

/*
 * 循环池信号检测任务，负责检测净化设备催化完成信号
 *
 *  * */
static void WasteManager_InputDetectTaskHandle(void *pvParameters)
{
	(void) pvParameters;
	static Uint32 cnt = 0;
	Uint8 reg = 0;
	Uint8 param = 0;
//	vTaskSuspend(NULL);
	DeviceIndicatorLED_SetBlink(500, 500, 500);
	while(1)
	{

		for(Uint8 i = 0;i < 4;i++)
		{
			if(!s_debugMode)
			{
				param = s_tempValue[i];
			}
			Communication_TurnOnLCD(i);
			System_Delay(10);
			Communication_DisplayNumber(i, param);
			System_Delay(10);
			Communication_DisplaySymbleAndTip(i, param);
			System_Delay(10);
		}
		if(s_debugMode)
		{
			param++;
			if(param>101)
			{
				param = 0;
			}
		}
		vTaskDelay(s_period / portTICK_RATE_MS);
	}
}

void WasteManager_Debug(Bool mode)
{
	if(mode)
	{
		s_debugMode = TRUE;
		s_period = 200;
	}
	else
	{
		s_debugMode = FALSE;
		s_period = 1000;
	}
}

void WasteManager_Test(Uint8 index, Uint8 param)
{
	s_tempValue[index] = param;
	Printf("Debug Set %d [%d]\n", index, param);
}

