/*
 * HardwareFlag.c
 *
 *  Created on: 2020年4月10日
 *      Author: Administrator
 */

#include "stm32f4xx.h"
#include <HardwareType.h>
#include "Tracer/Trace.h"

static float s_refVoltage = 3.3;

#define ADDR_0_PORT          		GPIOE
#define ADDR_0_PIN           		GPIO_Pin_3
#define ADDR_0_GPIO_CLK_CONFIG      RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOE, ENABLE)

#define ADDR_1_PORT          		GPIOE
#define ADDR_1_PIN           		GPIO_Pin_4
#define ADDR_1_GPIO_CLK_CONFIG      RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOE, ENABLE)

#define ADDR_2_PORT          		GPIOE
#define ADDR_2_PIN           		GPIO_Pin_5
#define ADDR_2_GPIO_CLK_CONFIG      RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOE, ENABLE)

#define ADDR_3_PORT          		GPIOE
#define ADDR_3_PIN           		GPIO_Pin_6
#define ADDR_3_GPIO_CLK_CONFIG      RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOE, ENABLE)
/**
 * @brief 硬件板卡类型标记初始化
 */
void HardwareType_Init(void)
{
    GPIO_InitTypeDef GPIO_InitStructure;
    ADDR_0_GPIO_CLK_CONFIG;
    ADDR_1_GPIO_CLK_CONFIG;
    ADDR_2_GPIO_CLK_CONFIG;
	ADDR_3_GPIO_CLK_CONFIG;

    GPIO_InitStructure.GPIO_Pin = ADDR_0_PIN;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN;
    GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
    GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_DOWN;
    GPIO_Init(ADDR_0_PORT, &GPIO_InitStructure);

    GPIO_InitStructure.GPIO_Pin = ADDR_1_PIN;
    GPIO_Init(ADDR_1_PORT, &GPIO_InitStructure);

    GPIO_InitStructure.GPIO_Pin = ADDR_2_PIN;
    GPIO_Init(ADDR_2_PORT, &GPIO_InitStructure);

	GPIO_InitStructure.GPIO_Pin = ADDR_3_PIN;
	GPIO_Init(ADDR_3_PORT, &GPIO_InitStructure);

	Uint8 value = 0;
	if(GPIO_ReadInputDataBit(ADDR_0_PORT,ADDR_0_PIN))
	{
		value += 1 << 0;
	}
	if(GPIO_ReadInputDataBit(ADDR_1_PORT,ADDR_1_PIN))
	{
		value += 1 << 1;
	}
	if(GPIO_ReadInputDataBit(ADDR_2_PORT,ADDR_2_PIN))
	{
		value += 1 << 2;
	}
	if(GPIO_ReadInputDataBit(ADDR_3_PORT,ADDR_3_PIN))
	{
		value += 1 << 3;
	}

	Printf("\n***************************************************************");
	Printf("\nAddr [%d]", value);
	Printf("\n***************************************************************");
}

/**
 * @brief 读取硬件版本标记
 * @return 标记值
 */
Uint8 HardwareType_GetAddr(void)
{
    Uint8 value = 0;
	if(GPIO_ReadInputDataBit(ADDR_0_PORT,ADDR_0_PIN))
	{
		value += 1 << 0;
	}
	if(GPIO_ReadInputDataBit(ADDR_1_PORT,ADDR_1_PIN))
	{
		value += 1 << 1;
	}
	if(GPIO_ReadInputDataBit(ADDR_2_PORT,ADDR_2_PIN))
	{
		value += 1 << 2;
	}
	if(GPIO_ReadInputDataBit(ADDR_3_PORT,ADDR_3_PIN))
	{
		value += 1 << 3;
	}

    return value;
}

