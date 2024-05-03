#include "stm32f4xx.h"
#include "stm32f4xx_exti.h"

#include <misc.h>

void exti_init_test(void);


static uint32_t led_switch = 0;
uint16_t threshold = 0;
uint16_t delay_c = 0; 
uint16_t delay = 1000;

void SysTick_Handler(void){
    if(delay_c > 0)
        delay_c--;
}

void delay_ms(uint16_t delay_t){
    delay_c = delay_t;
    while(delay_c){}
}

int main (void){
    SysTick_Config(SystemCoreClock/1000); 
    RCC->AHB1ENR |= RCC_AHB1ENR_GPIOAEN;
    RCC->AHB1ENR |= RCC_AHB1ENR_GPIODEN;
    RCC->AHB1ENR |= RCC_AHB1ENR_GPIOCEN;
  
    GPIOA->MODER = 0x0;

    GPIOD->MODER  = 0x55000000;
    GPIOD->OTYPER = 0;
    GPIOD->OSPEEDR = 0;
    
    exti_init_test();
    
    while(1) {
    GPIOD->ODR = 0x1000;
    delay_ms(delay);
    GPIOD->ODR = 0x0000;
    delay_ms(delay);
    }
}

void exti_init_test() {
    //SYSCFG->EXTICR[0] |= SYSCFG_EXTICR1_EXTI0_PA;
    SYSCFG->EXTICR[3] |= SYSCFG_EXTICR4_EXTI12_PC;
   
    EXTI->FTSR |= EXTI_FTSR_TR0;
    EXTI->RTSR |= EXTI_RTSR_TR0;
    EXTI->PR = EXTI_PR_PR0;
 
    EXTI->IMR |= EXTI_IMR_MR0;
 
    NVIC_EnableIRQ(EXTI3_IRQn);
}

void EXTI15_10_IRQHandler() {
    delay_ms(10);
    if (EXTI->PR & EXTI_PR_PR12) {
        if (!led_switch) {
            if (threshold)
                delay *= 1.1;
            else {
                delay *= 0.9;
                if (delay < 500) threshold = 1;
            }
            EXTI->PR = EXTI_PR_PR12;
        }
    }
}

void EXTI_IRQHandler() {
    if (EXTI->PR & EXTI_PR_PR0) {
        if (!led_switch) {
            if (threshold)
                delay *= 1.1;
            else {
                delay *= 0.9;
                if (delay < 500) threshold = 1;
           }
           EXTI->PR = EXTI_PR_PR0;
   
        }
    }
}
