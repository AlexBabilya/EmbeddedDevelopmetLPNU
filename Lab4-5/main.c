#include "accelerometer.h"
#include "lcd.h"
#include "spi.h"
#include <stdio.h> 
#include <stdlib.h>

uint16_t delay_c = 0; 
static char s[10];

void SysTick_Handler(void) {
    if(delay_c > 0)  
	    delay_c--;
}

void delay_ms(uint16_t delay_t) {
    delay_c = delay_t;
    while(delay_c){}
}

int main() {
	uint8_t accelWho = 0;
	LIS3DSH_t axes;
	SysTick_Config(SystemCoreClock / 1000);
	SPIInit();
	LCD_Init();

	while(1) { 
        LCD_refresh();
        sprintf(s, "Who: %d", 0); 
        LIS3DSH_ReadAxes(&axes);
            
        accelWho = Read_Val_Reg(LIS3DSH_WHO_AM_I_ADDR);
        sprintf(s, "Who: %d", accelWho); 
        LCD5110_write_string(s, 1, 1);		
        sprintf(s, "X: %d", axes.X);  
        LCD5110_write_string(s, 1, 2);
        sprintf(s, "Y: %d", axes.Y); 
        LCD5110_write_string(s, 1, 3);		
        sprintf(s, "Z: %d", axes.Z); 
        LCD5110_write_string(s, 1, 4);		
        delay_ms(100);
        LCD_clear();
	}
}
