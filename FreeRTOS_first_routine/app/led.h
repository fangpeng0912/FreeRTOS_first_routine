#ifndef _LED_H_
#define _LED_H_

#include "stm32f10x_gpio.h"
#include "stm32f10x_rcc.h"
#include "stm32f10x.h"
#include "bitBand.h"

#define LED_PORT GPIOA
#define LED_PIN GPIO_Pin_0 | GPIO_Pin_1
#define GPIOA_ODR_Addr (GPIOA_BASE+12) //0x4001080C
#define led0 BitBandAlias(GPIOA_ODR_Addr, 0)
#define led1 BitBandAlias(GPIOA_ODR_Addr, 1)

void LED_Init(void);

#endif
