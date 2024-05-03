#include "init.h"

void LEDInit() {
	GPIOA->MODER = 0x0;
    GPIOD->MODER  = 0x55000000;
    GPIOD->OTYPER = 0;
    GPIOD->OSPEEDR = 0;
}

void EXTIInit() {
    SYSCFG->EXTICR[0] |= SYSCFG_EXTICR1_EXTI0_PA;
    EXTI->FTSR |= EXTI_FTSR_TR0;
	EXTI->RTSR |= EXTI_RTSR_TR0;
    EXTI->PR = EXTI_PR_PR0;
    EXTI->IMR |= EXTI_IMR_MR0;
    NVIC_EnableIRQ(EXTI0_IRQn);
}
