#ifndef GLOBAL_H
#define GLOBAL_H
#endif
#include "stm32f4xx.h"
#include "stm32f4xx_hal.h"
#include "stm32f4xx_hal_gpio.h"
#include "stm32f4xx_hal_spi.h"
#include "stm32f4xx_hal_rcc.h"

extern uint16_t delay_c; 
extern void SysTick_Handler(void);
extern void delay_ms(uint16_t delay_t);