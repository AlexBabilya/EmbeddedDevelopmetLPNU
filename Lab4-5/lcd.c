#include "lcd.h"

void LCD_GPIO_Config() {
    GPIO_InitTypeDef GPIOB_Init; 
    GPIO_InitTypeDef GPIOC_Init;
    __HAL_RCC_GPIOB_CLK_ENABLE(); 
    __HAL_RCC_GPIOC_CLK_ENABLE(); 
    GPIOB_Init.Pin = GPIO_PIN_8; //out
    GPIOB_Init.Speed = GPIO_SPEED_FREQ_MEDIUM;
    GPIOB_Init.Mode = GPIO_MODE_OUTPUT_PP; 
    GPIOB_Init.Pull = GPIO_NOPULL;
    GPIOC_Init.Pin = GPIO_PIN_6|GPIO_PIN_7|GPIO_PIN_8|GPIO_PIN_9; //out
    GPIOC_Init.Speed = GPIO_SPEED_FREQ_MEDIUM; 
    GPIOC_Init.Pull = GPIO_NOPULL;
    GPIOC_Init.Mode = GPIO_MODE_OUTPUT_PP; 
    HAL_GPIO_Init(GPIOB,&GPIOB_Init); 
    HAL_GPIO_Init(GPIOC,&GPIOC_Init);
}
//sets
void LCD_CS_Set(GPIO_PinState pinState) {
    HAL_GPIO_WritePin(GPIOC, GPIO_PIN_9, pinState);
}

void LCD_RST_Set(GPIO_PinState pinState) { 
	HAL_GPIO_WritePin(GPIOC, GPIO_PIN_8, pinState);
}

void LCD_DC_Set(GPIO_PinState pinState) {
    HAL_GPIO_WritePin(GPIOC, GPIO_PIN_7, pinState);
}

void LCD_MO_Set(GPIO_PinState pinState) {
    HAL_GPIO_WritePin(GPIOC, GPIO_PIN_6, pinState);
}

void LCD_SCK_Set(GPIO_PinState pinState) { 
	HAL_GPIO_WritePin(GPIOB, GPIO_PIN_8, pinState);
}

void LCD_write_byte(uint8_t dat, uint8_t mode) {
    unsigned char i;
    LCD_CS_Set(0); 
    LCD_DC_Set(mode);
    for(i = 0; i < 8; i++) {  
	    LCD_MO_Set(dat & 0x80);
        dat = dat << 1;  
	    LCD_SCK_Set(0);
        LCD_SCK_Set(1); 
    }
    LCD_CS_Set(1);
}

void LCD_Init() { 
    LCD_GPIO_Config();
    LCD_DC_Set(1);
    LCD_MO_Set(1); 
    LCD_SCK_Set(1);
    LCD_CS_Set(1); 
    LCD_RST_Set(0);
    LCD_RST_Set(1); 
    LCD_write_byte(0x21,0); 
    LCD_write_byte(0xc6,0);
    LCD_write_byte(0x06,0);
    LCD_write_byte(0x13,0); 
    LCD_write_byte(0x20,0);
    LCD_write_byte(0x0c,0);
}

uint8_t LCD_buffer[504];
 
void LCD_refresh() {
    int i, j; 
    LCD_set_XY(0,0);  
	
    for(i = 0; i < 6; i++) {
        for(j = 0; j < 84; j++) {      
			LCD_write_byte(LCD_buffer[(i * 84) + j], 1);
        }  
	}
}

void LCD_drawPicture(void) {
    int i, j; 
	for(i = 0; i < 6; i++) {    
	    for(j = 0; j < 84; j++) {
			LCD_buffer[(i * 84) + j] |= lcd_image_mas[(i * 84) + j];    
		}
    }
}

void LCD_set_XY(uint8_t x,uint8_t y) {
    unsigned char X; 
    X = x * 6;
    LCD_write_byte(0x40|y,0); 
    LCD_write_byte(0x80|X,0);
}

void LCD5110_write_char(unsigned char c) {
	unsigned char line;
	unsigned char ch = 0;

	c = c - 32;

	for(line=0;line<6;line++) {
		ch = font6_8[c][line];
		LCD_write_byte(ch,1);
		
	}
}

void LCD5110_write_string(char *str, uint8_t x, uint8_t y) {
	LCD_set_XY(x, y);
	while(*str){    
		LCD5110_write_char(*str++);
	}
}

void LCD_clear(void) {
	int i;
	for(i = 0; i < 504; i++){
        LCD_write_byte(0x00, 1);
        LCD_buffer[i] = 0;
    }
}

void LCD_Hello_World(void){
	LCD5110_write_string("Hello", 5, 1);	
	LCD5110_write_string("World", 1, 6);		
}
