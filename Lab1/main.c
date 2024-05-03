#include "stm32f4xx.h"                  
#include "stm32f4xx_conf.h"
#include "stm32f4xx_gpio.h"
#include "stm32f4xx_rcc.h"

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

void blinky_simple() {
    GPIOD->ODR = 0xC000;
    delay_ms(1000);
    GPIOD->ODR = 0x3000;  
    delay_ms(1000);
}

void test(){
    GPIOD->ODR = 0xC000;
    GPIOC->ODR = 0xC000;
    delay_ms(1000);
    GPIOD->ODR = 0x3000; 
    GPIOC->ODR = 0xC000; 
    delay_ms(1000); 
}

void blinky_spl(){
    GPIO_ResetBits(GPIOD, GPIO_Pin_12);
    GPIO_ResetBits(GPIOD, GPIO_Pin_13);
    GPIO_SetBits(GPIOD, GPIO_Pin_14);
    GPIO_SetBits(GPIOD, GPIO_Pin_15);
    delay_ms(1000);

    GPIO_ResetBits(GPIOD, GPIO_Pin_14);
    GPIO_ResetBits(GPIOD, GPIO_Pin_15);
    GPIO_SetBits(GPIOD, GPIO_Pin_12);
    GPIO_SetBits(GPIOD, GPIO_Pin_13);
    delay_ms(1000);
}


int main (void){
    SysTick_Config(SystemCoreClock/1000);
    RCC->AHB1ENR |= RCC_AHB1ENR_GPIODEN;
    RCC->AHB1ENR |= RCC_AHB1ENR_GPIOCEN;
    GPIOD->MODER  = 0x55000000;
  
    GPIOD->MODER = 0x140;
    GPIOC->MODER = 0x40000000;

    GPIOD->OTYPER = 0;
    GPIOD->OSPEEDR = 0;  

    GPIOD->OTYPER = 0;
    GPIOD->OSPEEDR = 0;  
  
    while(1){
        blinky_spl();
    }
}
