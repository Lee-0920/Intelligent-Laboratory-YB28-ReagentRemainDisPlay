#ifndef SRC_COMMUNICATION_H_
#define SRC_COMMUNICATION_H_

#include "stm32f4xx.h"
#include "Common/Types.h"

//RS485串口1配置 USART2
#define RS485_Tx1_PERIPHERAL_SYSCLK       45            //串口使用的时钟频率，APB1 为45M，APB2为90M
#define RS485_Tx1_IRQn                    USART2_IRQn
#define RS485_Tx1_CLK_CONFIG              RCC_APB1PeriphClockCmd(RCC_APB1Periph_USART2, ENABLE)
#define RS485_Tx1_RX_CONFIG               RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOD, ENABLE)
#define RS485_Tx1_TX_CONFIG               RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOD, ENABLE)
#define RS485_Tx1                         USART2
#define RS485_Tx1_GPIO_AF                 GPIO_AF_USART2
#define RS485_Tx1_TX_PIN                  GPIO_Pin_5
#define RS485_Tx1_TX_PinSource            GPIO_PinSource5
#define RS485_Tx1_TX_GPIO_PORT            GPIOD
#define RS485_Tx1_RX_PIN                  GPIO_Pin_6
#define RS485_Tx1_RX_PinSource            GPIO_PinSource6
#define RS485_Tx1_RX_GPIO_PORT            GPIOD
#define RS485_Tx1_UART_BAUD               19200

#define RS485_Tx1_DE_RE_SWITCH_PORT          GPIOD
#define RS485_Tx1_DE_RE_SWITCH_PIN           GPIO_Pin_4
#define RS485_Tx1_DE_RE_GPIO_CLK_CONFIG      RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOD, ENABLE)

//RS485串口2配置 USART3
#define RS485_Tx2_PERIPHERAL_SYSCLK       45            //串口使用的时钟频率，APB1 为45M，APB2为90M
#define RS485_Tx2_IRQn                    USART3_IRQn
#define RS485_Tx2_CLK_CONFIG              RCC_APB1PeriphClockCmd(RCC_APB1Periph_USART3, ENABLE)
#define RS485_Tx2_RX_CONFIG               RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOD, ENABLE)
#define RS485_Tx2_TX_CONFIG               RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOD, ENABLE)
#define RS485_Tx2                         USART3
#define RS485_Tx2_GPIO_AF                 GPIO_AF_USART3
#define RS485_Tx2_TX_PIN                  GPIO_Pin_8
#define RS485_Tx2_TX_PinSource            GPIO_PinSource8
#define RS485_Tx2_TX_GPIO_PORT            GPIOD
#define RS485_Tx2_RX_PIN                  GPIO_Pin_9
#define RS485_Tx2_RX_PinSource            GPIO_PinSource9
#define RS485_Tx2_RX_GPIO_PORT            GPIOD
#define RS485_Tx2_UART_BAUD               19200

#define RS485_Tx2_DE_RE_SWITCH_PORT          GPIOD
#define RS485_Tx2_DE_RE_SWITCH_PIN           GPIO_Pin_10
#define RS485_Tx2_DE_RE_GPIO_CLK_CONFIG      RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOD, ENABLE)

//RS485串口3配置 UART4
#define RS485_Tx3_PERIPHERAL_SYSCLK       45            //串口使用的时钟频率，APB1 为45M，APB2为90M
#define RS485_Tx3_IRQn                    UART4_IRQn
#define RS485_Tx3_CLK_CONFIG              RCC_APB1PeriphClockCmd(RCC_APB1Periph_UART4, ENABLE)
#define RS485_Tx3_RX_CONFIG               RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOE, ENABLE)
#define RS485_Tx3_TX_CONFIG               RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOE, ENABLE)
#define RS485_Tx3                         UART4
#define RS485_Tx3_GPIO_AF                 GPIO_AF_UART4
#define RS485_Tx3_TX_PIN                  GPIO_Pin_10
#define RS485_Tx3_TX_PinSource            GPIO_PinSource10
#define RS485_Tx3_TX_GPIO_PORT            GPIOC
#define RS485_Tx3_RX_PIN                  GPIO_Pin_11
#define RS485_Tx3_RX_PinSource            GPIO_PinSource11
#define RS485_Tx3_RX_GPIO_PORT            GPIOC
#define RS485_Tx3_UART_BAUD               19200

#define RS485_Tx3_DE_RE_SWITCH_PORT          GPIOC
#define RS485_Tx3_DE_RE_SWITCH_PIN           GPIO_Pin_12
#define RS485_Tx3_DE_RE_GPIO_CLK_CONFIG      RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOC, ENABLE)

//RS485串口4配置 UART8
#define RS485_Tx4_PERIPHERAL_SYSCLK       45            //串口使用的时钟频率，APB1 为45M，APB2为90M
#define RS485_Tx4_IRQn                    UART8_IRQn
#define RS485_Tx4_CLK_CONFIG              RCC_APB1PeriphClockCmd(RCC_APB1Periph_UART8, ENABLE)
#define RS485_Tx4_RX_CONFIG               RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOE, ENABLE)
#define RS485_Tx4_TX_CONFIG               RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOE, ENABLE)
#define RS485_Tx4                         UART8
#define RS485_Tx4_GPIO_AF                 GPIO_AF_UART8
#define RS485_Tx4_TX_PIN                  GPIO_Pin_1
#define RS485_Tx4_TX_PinSource            GPIO_PinSource1
#define RS485_Tx4_TX_GPIO_PORT            GPIOE
#define RS485_Tx4_RX_PIN                  GPIO_Pin_0
#define RS485_Tx4_RX_PinSource            GPIO_PinSource0
#define RS485_Tx4_RX_GPIO_PORT            GPIOE
#define RS485_Tx4_UART_BAUD               19200

#define RS485_Tx4_DE_RE_SWITCH_PORT          GPIOB
#define RS485_Tx4_DE_RE_SWITCH_PIN           GPIO_Pin_9
#define RS485_Tx4_DE_RE_GPIO_CLK_CONFIG      RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOB, ENABLE)

#define HEAD 			 0xC5 	//数据帧头固定格式
/********命令表**********/
#define CMD_SWITCH 			 0x01   ///<显示开关 紧跟1位字节数据 0=关 1=开(显示内容为上一次内容)
#define CMD_NUMBER  		 0x02   ///<数字显示 紧跟3位字节数据 数据0~9对应数字; 0x0A-0x0F对应字母A-F; 0x10 空白; 0x11 '-'
#define CMD_SYMBLE   	     0x03   ///<标号显示 紧跟3位字节数据 (第1字节bit0-bit7对应K1-K8)
														      //(第2字节bit0-bit7对应K9-K15，以及数字1小数点)
															  //(第3字节bit0-bit7对应数字2、数字3小数点)

#define RS485_INDEX_1          0  //对应USART2
#define RS485_INDEX_2          2  //对应USART3
#define RS485_INDEX_3          1  //对应UART4
#define RS485_INDEX_4          3  //对应UART8


void Communication_Init(void);
void Communication_Send(Uint8 index, char* Data, int len);
void Communication_TurnOnLCD(Uint8 index);
void Communication_TurnOffLCD(Uint8 index);
void Communication_DisplayNumber(Uint8 index, Uint8 value);
void Communication_DisplaySymbleAndTip(Uint8 index, Uint8 value);
Uint8 Communication_GetCurrentDisplay(Uint8 index);

static inline void Communication_Write(Uint8 index, unsigned char data)
{
	if(RS485_INDEX_1 == index)
	{
		USART_SendData(RS485_Tx1, data);
	}
	else if(RS485_INDEX_2 == index)
	{
		USART_SendData(RS485_Tx2, data);
	}
	else if(RS485_INDEX_3 == index)
	{
		USART_SendData(RS485_Tx3, data);
	}
	else
	{
		USART_SendData(RS485_Tx4, data);
	}
}

static inline bool Communication_IsTxInterruptTriggered(Uint8 index)
{
	if(RS485_INDEX_1 == index)
	{
		return (USART_GetITStatus(RS485_Tx1, USART_IT_TXE));
	}
	else if(RS485_INDEX_2 == index)
	{
		return (USART_GetITStatus(RS485_Tx2, USART_IT_TXE));
	}
	else if(RS485_INDEX_3 == index)
	{
		return (USART_GetITStatus(RS485_Tx3, USART_IT_TXE));
	}
	else
	{
		return (USART_GetITStatus(RS485_Tx4, USART_IT_TXE));
	}
}

static inline bool Communication_IsRxInterruptTriggered(Uint8 index)
{
    if(RS485_INDEX_1 == index)
	{
		return (USART_GetITStatus(RS485_Tx1, USART_IT_RXNE));
	}
	else if(RS485_INDEX_2 == index)
	{
		return (USART_GetITStatus(RS485_Tx2, USART_IT_RXNE));
	}
	else if(RS485_INDEX_3 == index)
	{
		return (USART_GetITStatus(RS485_Tx3, USART_IT_RXNE));
	}
	else
	{
		return (USART_GetITStatus(RS485_Tx4, USART_IT_RXNE));
	}
}

static inline bool Communication_IsTxInterruptEnabled(Uint8 index)
{
    if(RS485_INDEX_1 == index)
   	{
   		return ((RS485_Tx1->CR1) & USART_CR1_RXNEIE);
   	}
   	else if(RS485_INDEX_2 == index)
   	{
   		return ((RS485_Tx2->CR1) & USART_CR1_RXNEIE);
   	}
   	else if(RS485_INDEX_3 == index)
   	{
   		return ((RS485_Tx3->CR1) & USART_CR1_RXNEIE);
   	}
   	else
   	{
   		return ((RS485_Tx4->CR1) & USART_CR1_RXNEIE);
   	}
}

static inline void Communication_EnableTxInterrupt(Uint8 index)
{
    if(RS485_INDEX_1 == index)
	{
    	USART_ITConfig(RS485_Tx1, USART_IT_TXE, ENABLE);
	}
	else if(RS485_INDEX_2 == index)
	{
		USART_ITConfig(RS485_Tx2, USART_IT_TXE, ENABLE);
	}
	else if(RS485_INDEX_3 == index)
	{
		USART_ITConfig(RS485_Tx3, USART_IT_TXE, ENABLE);
	}
	else
	{
		USART_ITConfig(RS485_Tx4, USART_IT_TXE, ENABLE);
	}
}

static inline void Communication_DisableTxInterrupt(Uint8 index)
{
    if(RS485_INDEX_1 == index)
   	{
    	USART_ITConfig(RS485_Tx1, USART_IT_TXE, DISABLE);
   	}
   	else if(RS485_INDEX_2 == index)
   	{
   		USART_ITConfig(RS485_Tx2, USART_IT_TXE, DISABLE);
   	}
   	else if(RS485_INDEX_3 == index)
   	{
   		USART_ITConfig(RS485_Tx3, USART_IT_TXE, DISABLE);
   	}
   	else
   	{
   		USART_ITConfig(RS485_Tx4, USART_IT_TXE, DISABLE);
   	}
}

static void Communication_RS485_SwitchToTx(Uint8 index)
{
    if(RS485_INDEX_1 == index)
	{
    	RS485_Tx1_DE_RE_SWITCH_PORT->BSRRL |= RS485_Tx1_DE_RE_SWITCH_PIN;
	}
	else if(RS485_INDEX_2 == index)
	{
		RS485_Tx2_DE_RE_SWITCH_PORT->BSRRL |= RS485_Tx2_DE_RE_SWITCH_PIN;
	}
	else if(RS485_INDEX_3 == index)
	{
		RS485_Tx3_DE_RE_SWITCH_PORT->BSRRL |= RS485_Tx3_DE_RE_SWITCH_PIN;
	}
	else
	{
		RS485_Tx4_DE_RE_SWITCH_PORT->BSRRL |= RS485_Tx4_DE_RE_SWITCH_PIN;
	}
}

static inline void Communication_RS485_SwitchToRx(Uint8 index)
{
    if(RS485_INDEX_1 == index)
   	{
    	RS485_Tx1_DE_RE_SWITCH_PORT->BSRRH |= RS485_Tx1_DE_RE_SWITCH_PIN;
   	}
   	else if(RS485_INDEX_2 == index)
   	{
   		RS485_Tx2_DE_RE_SWITCH_PORT->BSRRH |= RS485_Tx2_DE_RE_SWITCH_PIN;
   	}
   	else if(RS485_INDEX_3 == index)
   	{
   		RS485_Tx3_DE_RE_SWITCH_PORT->BSRRH |= RS485_Tx3_DE_RE_SWITCH_PIN;
   	}
   	else
   	{
   		RS485_Tx4_DE_RE_SWITCH_PORT->BSRRH |= RS485_Tx4_DE_RE_SWITCH_PIN;
   	}
}

#endif
