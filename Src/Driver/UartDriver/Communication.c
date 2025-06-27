/**
 * @addtogroup module_Driver
 * @{
 */

/**
 * @file
 * @brief 命令行 Uart 驱动。
 * @details 仅供串口命令行程序使用，见 @ref Console.c
 *  主要的 RS232 通信实现移至 Console 模块。
 * @version 1.0.0
 * @author kim.xiejinqiang
 * @date 2012-10-31
 */

#include "Communication.h"
#include "string.h"
#include "Tracer/Trace.h"
#include "Common/Types.h"

#define MAX_DATA_LEN	11

static char s_SendResult[MAX_DATA_LEN] = {0};
static uint8_t s_sendPost = 0;
static uint8_t s_dataLen = 0;
static uint8_t s_currentData[4] = {0};

/**
 * @brief Comunication 串口驱动初始化。
 */
void Communication_RS485_1_USART_Init(void)
{
	GPIO_InitTypeDef GPIO_InitStructure;
	USART_InitTypeDef USART_InitStructure;
	NVIC_InitTypeDef NVIC_InitStructure;

	//打开引脚时钟,串口时钟
	RS485_Tx1_RX_CONFIG;
	RS485_Tx1_TX_CONFIG;
	RS485_Tx1_CLK_CONFIG;

	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;
	GPIO_InitStructure.GPIO_Pin = RS485_Tx1_TX_PIN | RS485_Tx1_RX_PIN;
	GPIO_Init(RS485_Tx1_TX_GPIO_PORT, &GPIO_InitStructure);

	GPIO_PinAFConfig(RS485_Tx1_TX_GPIO_PORT, RS485_Tx1_TX_PinSource, RS485_Tx1_GPIO_AF);
	GPIO_PinAFConfig(RS485_Tx1_RX_GPIO_PORT, RS485_Tx1_RX_PinSource, RS485_Tx1_GPIO_AF);

	//配置串口工作模式
	USART_InitStructure.USART_BaudRate = RS485_Tx1_UART_BAUD;
	USART_InitStructure.USART_WordLength = USART_WordLength_8b;
	USART_InitStructure.USART_StopBits = USART_StopBits_1;
	USART_InitStructure.USART_Parity = USART_Parity_No;
	USART_InitStructure.USART_HardwareFlowControl =
			USART_HardwareFlowControl_None;
	USART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;
	USART_Init(RS485_Tx1, &USART_InitStructure);
	{
		uint16_t mantissa;
		uint16_t fraction;

		float temp = (float) (RS485_Tx1_PERIPHERAL_SYSCLK * 1000000) / (RS485_Tx1_UART_BAUD * 16);
		mantissa = (uint16_t) temp;
		fraction = (uint16_t) ((temp - mantissa) * 16);
		mantissa <<= 4;
		mantissa += fraction;
		RS485_Tx1->BRR = mantissa;
	}
	USART_Cmd(RS485_Tx1, ENABLE);
	USART_ITConfig(RS485_Tx1, USART_IT_RXNE, ENABLE);

	// 配置中断向量管理器的RS485_Tx1_IRQn的中断
	NVIC_InitStructure.NVIC_IRQChannel = RS485_Tx1_IRQn;
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority=0x08; //抢占优先级 1
	NVIC_InitStructure.NVIC_IRQChannelSubPriority=0x00; //响应优先级 0
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
	NVIC_Init(&NVIC_InitStructure);
}

/**
 * @brief Comunication 串口驱动初始化。
 */
void Communication_RS485_2_USART_Init(void)
{
	GPIO_InitTypeDef GPIO_InitStructure;
	USART_InitTypeDef USART_InitStructure;
	NVIC_InitTypeDef NVIC_InitStructure;

	//打开引脚时钟,串口时钟
	RS485_Tx2_RX_CONFIG;
	RS485_Tx2_TX_CONFIG;
	RS485_Tx2_CLK_CONFIG;

	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;
	GPIO_InitStructure.GPIO_Pin = RS485_Tx2_TX_PIN | RS485_Tx2_RX_PIN;
	GPIO_Init(RS485_Tx2_TX_GPIO_PORT, &GPIO_InitStructure);

	GPIO_PinAFConfig(RS485_Tx2_TX_GPIO_PORT, RS485_Tx2_TX_PinSource, RS485_Tx2_GPIO_AF);
	GPIO_PinAFConfig(RS485_Tx2_RX_GPIO_PORT, RS485_Tx2_RX_PinSource, RS485_Tx2_GPIO_AF);

	//配置串口工作模式
	USART_InitStructure.USART_BaudRate = RS485_Tx2_UART_BAUD;
	USART_InitStructure.USART_WordLength = USART_WordLength_8b;
	USART_InitStructure.USART_StopBits = USART_StopBits_1;
	USART_InitStructure.USART_Parity = USART_Parity_No;
	USART_InitStructure.USART_HardwareFlowControl =
			USART_HardwareFlowControl_None;
	USART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;
	USART_Init(RS485_Tx2, &USART_InitStructure);
	{
		uint16_t mantissa;
		uint16_t fraction;

		float temp = (float) (RS485_Tx2_PERIPHERAL_SYSCLK * 1000000) / (RS485_Tx2_UART_BAUD * 16);
		mantissa = (uint16_t) temp;
		fraction = (uint16_t) ((temp - mantissa) * 16);
		mantissa <<= 4;
		mantissa += fraction;
		RS485_Tx2->BRR = mantissa;
	}
	USART_Cmd(RS485_Tx2, ENABLE);
	USART_ITConfig(RS485_Tx2, USART_IT_RXNE, ENABLE);

	// 配置中断向量管理器的RS485_Tx2_IRQn的中断
	NVIC_InitStructure.NVIC_IRQChannel = RS485_Tx2_IRQn;
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority=0x08; //抢占优先级 1
	NVIC_InitStructure.NVIC_IRQChannelSubPriority=0x00; //响应优先级 0
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
	NVIC_Init(&NVIC_InitStructure);
}

/**
 * @brief Comunication 串口驱动初始化。
 */
void Communication_RS485_3_USART_Init(void)
{
	GPIO_InitTypeDef GPIO_InitStructure;
	USART_InitTypeDef USART_InitStructure;
	NVIC_InitTypeDef NVIC_InitStructure;

	//打开引脚时钟,串口时钟
	RS485_Tx3_RX_CONFIG;
	RS485_Tx3_TX_CONFIG;
	RS485_Tx3_CLK_CONFIG;

	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;
	GPIO_InitStructure.GPIO_Pin = RS485_Tx3_TX_PIN | RS485_Tx3_RX_PIN;
	GPIO_Init(RS485_Tx3_TX_GPIO_PORT, &GPIO_InitStructure);

	GPIO_PinAFConfig(RS485_Tx3_TX_GPIO_PORT, RS485_Tx3_TX_PinSource, RS485_Tx3_GPIO_AF);
	GPIO_PinAFConfig(RS485_Tx3_RX_GPIO_PORT, RS485_Tx3_RX_PinSource, RS485_Tx3_GPIO_AF);

	//配置串口工作模式
	USART_InitStructure.USART_BaudRate = RS485_Tx3_UART_BAUD;
	USART_InitStructure.USART_WordLength = USART_WordLength_8b;
	USART_InitStructure.USART_StopBits = USART_StopBits_1;
	USART_InitStructure.USART_Parity = USART_Parity_No;
	USART_InitStructure.USART_HardwareFlowControl =
			USART_HardwareFlowControl_None;
	USART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;
	USART_Init(RS485_Tx3, &USART_InitStructure);
	{
		uint16_t mantissa;
		uint16_t fraction;

		float temp = (float) (RS485_Tx3_PERIPHERAL_SYSCLK * 1000000) / (RS485_Tx3_UART_BAUD * 16);
		mantissa = (uint16_t) temp;
		fraction = (uint16_t) ((temp - mantissa) * 16);
		mantissa <<= 4;
		mantissa += fraction;
		RS485_Tx3->BRR = mantissa;
	}
	USART_Cmd(RS485_Tx3, ENABLE);
	USART_ITConfig(RS485_Tx3, USART_IT_RXNE, ENABLE);

	// 配置中断向量管理器的RS485_Tx3_IRQn的中断
	NVIC_InitStructure.NVIC_IRQChannel = RS485_Tx3_IRQn;
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority=0x08; //抢占优先级 1
	NVIC_InitStructure.NVIC_IRQChannelSubPriority=0x00; //响应优先级 0
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
	NVIC_Init(&NVIC_InitStructure);
}

/**
 * @brief Comunication 串口驱动初始化。
 */
void Communication_RS485_4_USART_Init(void)
{
	GPIO_InitTypeDef GPIO_InitStructure;
	USART_InitTypeDef USART_InitStructure;
	NVIC_InitTypeDef NVIC_InitStructure;

	//打开引脚时钟,串口时钟
	RS485_Tx4_RX_CONFIG;
	RS485_Tx4_TX_CONFIG;
	RS485_Tx4_CLK_CONFIG;

	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;
	GPIO_InitStructure.GPIO_Pin = RS485_Tx4_TX_PIN | RS485_Tx4_RX_PIN;
	GPIO_Init(RS485_Tx4_TX_GPIO_PORT, &GPIO_InitStructure);

	GPIO_PinAFConfig(RS485_Tx4_TX_GPIO_PORT, RS485_Tx4_TX_PinSource, RS485_Tx4_GPIO_AF);
	GPIO_PinAFConfig(RS485_Tx4_RX_GPIO_PORT, RS485_Tx4_RX_PinSource, RS485_Tx4_GPIO_AF);

	//配置串口工作模式
	USART_InitStructure.USART_BaudRate = RS485_Tx4_UART_BAUD;
	USART_InitStructure.USART_WordLength = USART_WordLength_8b;
	USART_InitStructure.USART_StopBits = USART_StopBits_1;
	USART_InitStructure.USART_Parity = USART_Parity_No;
	USART_InitStructure.USART_HardwareFlowControl =
			USART_HardwareFlowControl_None;
	USART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;
	USART_Init(RS485_Tx4, &USART_InitStructure);
	{
		uint16_t mantissa;
		uint16_t fraction;

		float temp = (float) (RS485_Tx4_PERIPHERAL_SYSCLK * 1000000) / (RS485_Tx4_UART_BAUD * 16);
		mantissa = (uint16_t) temp;
		fraction = (uint16_t) ((temp - mantissa) * 16);
		mantissa <<= 4;
		mantissa += fraction;
		RS485_Tx4->BRR = mantissa;
	}
	USART_Cmd(RS485_Tx4, ENABLE);
	USART_ITConfig(RS485_Tx4, USART_IT_RXNE, ENABLE);

	// 配置中断向量管理器的RS485_Tx4_IRQn的中断
	NVIC_InitStructure.NVIC_IRQChannel = RS485_Tx4_IRQn;
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority=0x08; //抢占优先级 1
	NVIC_InitStructure.NVIC_IRQChannelSubPriority=0x00; //响应优先级 0
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
	NVIC_Init(&NVIC_InitStructure);
}

/**
 * @brief Comunication 485切换引脚初始化。
 */
void Communication_Switch_Init(void)
{
	GPIO_InitTypeDef GPIO_InitStructure;
	//配置RS485收发切换引脚
	RS485_Tx1_DE_RE_GPIO_CLK_CONFIG;
	RS485_Tx2_DE_RE_GPIO_CLK_CONFIG;
	RS485_Tx3_DE_RE_GPIO_CLK_CONFIG;
	RS485_Tx4_DE_RE_GPIO_CLK_CONFIG;

	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;

	GPIO_InitStructure.GPIO_Pin = RS485_Tx1_DE_RE_SWITCH_PIN;
	GPIO_Init(RS485_Tx1_DE_RE_SWITCH_PORT, &GPIO_InitStructure);

	GPIO_InitStructure.GPIO_Pin = RS485_Tx2_DE_RE_SWITCH_PIN;
	GPIO_Init(RS485_Tx2_DE_RE_SWITCH_PORT, &GPIO_InitStructure);

	GPIO_InitStructure.GPIO_Pin = RS485_Tx3_DE_RE_SWITCH_PIN;
	GPIO_Init(RS485_Tx3_DE_RE_SWITCH_PORT, &GPIO_InitStructure);

	GPIO_InitStructure.GPIO_Pin = RS485_Tx4_DE_RE_SWITCH_PIN;
	GPIO_Init(RS485_Tx4_DE_RE_SWITCH_PORT, &GPIO_InitStructure);

	Communication_RS485_SwitchToRx(RS485_INDEX_1);
	Communication_RS485_SwitchToRx(RS485_INDEX_2);
	Communication_RS485_SwitchToRx(RS485_INDEX_3);
	Communication_RS485_SwitchToRx(RS485_INDEX_4);
}


/**
 * @brief Comunication 驱动初始化。
 */
void Communication_Init(void)
{
	Communication_RS485_1_USART_Init();
	Communication_RS485_2_USART_Init();
	Communication_RS485_3_USART_Init();
	Communication_RS485_4_USART_Init();
	Communication_Switch_Init();
}

/**
 * @brief RS485 1(USART2_IRQHandler)中断服务程序。
 */
void RS485_1_Hnadle(void)
{
    // 接收中断处理
    if (Communication_IsRxInterruptTriggered(RS485_INDEX_1))
    {
    	USART_ClearITPendingBit(RS485_Tx1, USART_IT_RXNE);
    	uint16_t data;
    	data = USART_ReceiveData(RS485_Tx1);
    	char cmd = 0;
    	memcpy(&cmd,&data,sizeof(char));
    	TRACE_MARK("\n RS481_1 R: %x", cmd);

    	USART_ITConfig(RS485_Tx1, USART_IT_RXNE, ENABLE); // 使能接收中断
    }

    // 发送中断处理
    if (Communication_IsTxInterruptTriggered(RS485_INDEX_1))
    {
    	if(s_sendPost <= s_dataLen)
    	{
    		TRACE_MARK("\n RS481_1: %x", s_SendResult[s_sendPost]);
    		Communication_Write(RS485_INDEX_1, s_SendResult[s_sendPost++]);
    	}
    	else
    	{
    		Communication_DisableTxInterrupt(RS485_INDEX_1);
    		Communication_RS485_SwitchToRx(RS485_INDEX_1);
    		s_sendPost = 0;
    	}
    }
}

/**
 * @brief RS485 2(USART3_IRQHandler)中断服务程序。
 */
void RS485_2_Hnadle(void)
{
    // 接收中断处理
    if (Communication_IsRxInterruptTriggered(RS485_INDEX_2))
    {
    	USART_ClearITPendingBit(RS485_Tx2, USART_IT_RXNE);
    	uint16_t data;
    	data = USART_ReceiveData(RS485_Tx2);
    	char cmd = 0;
    	memcpy(&cmd,&data,sizeof(char));
    	TRACE_MARK("\n RS481_2 R: %x", cmd);

    	USART_ITConfig(RS485_Tx2, USART_IT_RXNE, ENABLE); // 使能接收中断
    }

    // 发送中断处理
    if (Communication_IsTxInterruptTriggered(RS485_INDEX_2))
    {
    	if(s_sendPost <= s_dataLen)
    	{
    		TRACE_MARK("\n RS481_2: %x", s_SendResult[s_sendPost]);
    		Communication_Write(RS485_INDEX_2, s_SendResult[s_sendPost++]);
    	}
    	else
    	{
    		Communication_DisableTxInterrupt(RS485_INDEX_2);
    		Communication_RS485_SwitchToRx(RS485_INDEX_2);
    		s_sendPost = 0;
    	}
    }
}

/**
 * @brief RS485 2(UART4_IRQHandler)中断服务程序。
 */
void RS485_3_Hnadle(void)
{
    // 接收中断处理
    if (Communication_IsRxInterruptTriggered(RS485_INDEX_3))
    {
    	USART_ClearITPendingBit(RS485_Tx3, USART_IT_RXNE);
    	uint16_t data;
    	data = USART_ReceiveData(RS485_Tx3);
    	char cmd = 0;
    	memcpy(&cmd,&data,sizeof(char));
    	TRACE_MARK("\n RS481_3 R: %x", cmd);

    	USART_ITConfig(RS485_Tx3, USART_IT_RXNE, ENABLE); // 使能接收中断
    }

    // 发送中断处理
    if (Communication_IsTxInterruptTriggered(RS485_INDEX_3))
    {
    	if(s_sendPost <= s_dataLen)
    	{
    		TRACE_MARK("\n RS481_3: %x", s_SendResult[s_sendPost]);
    		Communication_Write(RS485_INDEX_3, s_SendResult[s_sendPost++]);
    	}
    	else
    	{
    		Communication_DisableTxInterrupt(RS485_INDEX_3);
    		Communication_RS485_SwitchToRx(RS485_INDEX_3);
    		s_sendPost = 0;
    	}
    }
}

/**
 * @brief RS485 4(UART8_IRQHandler)中断服务程序。
 */
void RS485_4_Hnadle(void)
{
    // 接收中断处理
    if (Communication_IsRxInterruptTriggered(RS485_INDEX_4))
    {
    	USART_ClearITPendingBit(RS485_Tx4, USART_IT_RXNE);
    	uint16_t data;
    	data = USART_ReceiveData(RS485_Tx4);
    	char cmd = 0;
    	memcpy(&cmd,&data,sizeof(char));
    	TRACE_MARK("\n RS481_4 R: %x", cmd);

    	USART_ITConfig(RS485_Tx4, USART_IT_RXNE, ENABLE); // 使能接收中断
    }

    // 发送中断处理
    if (Communication_IsTxInterruptTriggered(RS485_INDEX_4))
    {

    	if(s_sendPost <= s_dataLen)
    	{
    		TRACE_MARK("\n RS481_4: %x", s_SendResult[s_sendPost]);
    		Communication_Write(RS485_INDEX_4, s_SendResult[s_sendPost++]);
    	}
    	else
    	{
    		Communication_DisableTxInterrupt(RS485_INDEX_4);
    		Communication_RS485_SwitchToRx(RS485_INDEX_4);
    		s_sendPost = 0;
    	}
    }
}

void Communication_Send(Uint8 index, char* Data, int len)
{
	memcpy(s_SendResult, Data, len);
	s_dataLen = len;
//	Printf("MaxL %d", len);
	Communication_RS485_SwitchToTx(index);
	Communication_EnableTxInterrupt(index);
}

/*远标YB28使用说明
 *
 *
 * a) 0x01：显示开关，数据 1 个字节：0=关，1=开（显示内容为上一次的内容）
		例：C5 01 01 02 显示开关打开
	b) 0x02：数字显示，数据 3 个字节，对应 3 个数据位的内容，内容定义如下：
		0~9：对应数字; 0x0A~0x0F：字母 A~F; 0x10：空白; 0x11：- ;
		例：C5 02 10 09 08 23 显示数字：98
	c) 0x03：标号显示，数据 3 个字节，每个字节的每个位对应一个标号，定义如下：
		第 1 个字节由 bit0 到 bit7 分别对应：K1,K2,K3,K4,K5,K6,K7,K8
		第 2 个字节由 bit0 到 bit7 分别对应：K9,K10,K11,K12,K13,K14,K15,数字 1 的 DP
		第 3 个字节由 bit0 到 bit7 分别对应：数字 2 的 DP，数字 3 的 DP
 	 	例：C5 03 F0 AA FE 9B 显示电池格(K7、K8、K10、K12、K14)、数字 1 数字 3 小数点、V、%
 标号：
 F: K1-[第1字节bit0]
 A：K2-[第1字节bit1]
 ℃：K3-[第1字节bit2]
 H：K4-[第1字节bit3]
 V：K5-[第1字节bit4]
 %：K6-[第1字节bit5]
 电池电量：
 K7/K8-[第1字节bit6,bit7]
 K9/K14-[第2字节bit0-bit5]
 电池外框：
 K15-[第2字节bit6]
 数字1小数点：第2字节bit7
 数字2小数点：第3字节bit0
 数字3小数点：第3字节bit1
 * */

/*
 * 数据校验CRC：数据和校验,取低位
 * 注意：数据校验不包括帧头0xC5
 * */
Uint8 Communication_CRC(char* data, Uint8 len)
{
	Uint8 crc = 0;
	Uint8 checkData[10] = {0};
	memcpy(checkData, data, len);
	for(Uint8 i = 1; i < len; i++) //去掉帧头校验
	{
		crc += checkData[i];
	}
	return (crc&0xFF);
}

/*
 * 打开LCD屏幕
 *
 * 固定指令C5 01 01 02
 * */
void Communication_TurnOnLCD(Uint8 index)
{
	Uint8 data[4] = {0};
	data[0] = HEAD;
	data[1] = CMD_SWITCH;
	data[2] = 1; //打开
//	data[3] = (data[0] + data[1] + data[2]);
	data[3] = Communication_CRC((char*)data, sizeof(data));
//	Printf("crc %x", data[3]);
	Communication_Send(index, (char*)data, sizeof(data));
}

/*
 * 关闭LCD屏幕
 *
 * 固定指令C5 01 00 01
 * */
void Communication_TurnOffLCD(Uint8 index)
{
	Uint8 data[4] = {0};
	data[0] = HEAD;
	data[1] = CMD_SWITCH;
	data[2] = 0; //关闭
	data[3] = Communication_CRC((char*)data, sizeof(data));
	Communication_Send(index, (char*)data, sizeof(data));
}

/*
 * LCD屏幕显示数字(只显示整数)
 *
 * 固定指令6个字节：C5 02 10 0n 0n crc (0-99)
 * 100: C5 02 01 00 00 03 (100)
 * */
void Communication_DisplayNumber(Uint8 index, Uint8 value)
{
	Uint8 data[6] = {0};
	data[0] = HEAD;
	data[1] = CMD_NUMBER;
	data[2] = (value%100)?0x10:0x01;//百位
	data[3] = (value/10) % 10; //十位
	data[4] = value % 10; //个位
	data[5] = Communication_CRC((char*)data, sizeof(data));
	Communication_Send(index, (char*)data, sizeof(data));
	if(index < 4)
	{
		s_currentData[index] = value;
	}
}

/*
 * 余量显示换算：8bit，一格代表13%
 * 88-100显示满格
 * 1-16显示1格
 * 注意：电池衰减方向-从右往左 bit0-K14, bit7-K7
 * */
Uint8 Communication_GetRemain(Uint8 value)
{
	Uint8 ret = 0xFF;
	for(Uint8 i = 104;i >13;i-=13)
	{
		if(value < i-13)
		{
			ret <<= 1;
		}
	}
//	Printf("bat %x - %d", ret&0xFF, value);
	return ret&0xFF;
}

/*
 * 位翻转：将电池电量8位进行翻转，高位变低位，低位变高位
 * 将0xA0->0x05 （1010 0000 -> 0000 0101）
 * */
Uint8 Communication_ReverseBits(Uint8 data) {
	Uint8 result = 0;
    for (int i = 0; i < 8; i++) {
        // 左移result腾出最低位，将data的最低位添加到result
        result = (result << 1) | (data & 1);
        data >>= 1; // 右移data处理下一位
    }
    return result;
}


/*
 * LCD屏幕显示标号(只显示百分号和电池余量)
 *
 * 固定指令6个字节：C5 02 10 0n 0n crc
 * */
void Communication_DisplaySymbleAndTip(Uint8 index, Uint8 value)
{
	Uint8 data[6] = {0};
	Uint8 bat = Communication_GetRemain(value);
	Uint8 rbat = Communication_ReverseBits(bat);
	data[0] = HEAD;
	data[1] = CMD_SYMBLE;
	data[2] = (1<<5) | ((bat&0x80)>>1) | ((bat&0x40)<<1);//显示%，K7, K8 (1<<5) | (rbat<<6)
	data[3] = (rbat>>2) |(1<<6); //显示余量K9-K14, K15外框,小数点不显示
	data[4] = 0;//小数点不显示
	data[5] = Communication_CRC((char*)data, sizeof(data));
	Communication_Send(index, (char*)data, sizeof(data));
}

Uint8 Communication_GetCurrentDisplay(Uint8 index)
{
	if(index < 4)
	{
		return s_currentData[index];
	}
	else
	{
		Printf("Erro Index %d", index);
		return 0;
	}

}
