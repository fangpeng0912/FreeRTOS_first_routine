#ifndef _RS232Rx_CANTx_CANRx_RS232Tx_H_
#define _RS232Rx_CANTx_CANRx_RS232Tx_H_

#include "stm32f10x.h"
#include "stm32f10x_gpio.h"
#include "stm32f10x_rcc.h"
#include "misc.h"
#include "stm32f10x_usart.h"
#include "stdio.h"

#define USART1_PORT GPIOA
#define USART1_TX_PIN GPIO_Pin_9
#define USART1_RX_PIN GPIO_Pin_10

#define USART_REC_LEN 200
extern unsigned char USART1_receive[USART_REC_LEN];

#define ENTER_STATE 0x4000
#define NEWLINE_STATE 0x8000
extern uint16_t USART_RX_STA;    //接收状态标记，亦用作接收计数

void USART1_Init(void);
int fputc(int ch, FILE *file);

#endif
