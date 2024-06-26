#include "stm32f4xx.h"                  // Deviceheader
#include "unicode.h"
#include "IconsDef.h"
#define  ADDRESS         0x08010000

#ifdef COMPILE_UNICODE_GRAPHIC
extern ICON_PARAMS_T  Icon_params;   
#else
ICON_PARAMS_T  Icon_params;
#endif

const unsigned char O_char_table[] 
__attribute__((section(".ARM.__at_0x08100000"))) = {
    0x80, 0xFC, 0x06, 0x03, 0x03, 0x01, 0x01, 0x03, 0x1E, 0xF0, 0x00, 0x00,
    0x1F, 0x30, 0x60, 0xC0, 0x80, 0x80, 0xC0, 0x60, 0x38, 0x0F, 0x00, 0x00
};

const unsigned char B_char_table[]
__attribute__((section(".ARM.__at_0x08200000"))) = {
    0xFF, 0x01, 0x01, 0x01, 0x01, 0x01, 0x01, 0x03, 0x06, 0x8C, 0x98, 0xF0,
    0xFF, 0xC0, 0x80, 0x80, 0x80, 0x80, 0x81, 0x81, 0x81, 0xE3, 0x3E, 0x00
};

const unsigned char Logo_char_table[]
__attribute__((section(".ARM.__at_0x08550000"))) = {
    0xC0, 0xC0, 0xE0, 0xA0, 0x30, 0x10, 0xD8, 0xEE, 0xC2, 0x0E, 0x38, 0xE0,
    0x00, 0x00, 0x00, 0x01, 0x06, 0x1C, 0x30, 0x60, 0x38, 0x0C, 0x06, 0x01
};

const unsigned char Image_char_table[]
__attribute__((section(".ARM.__at_0x00000000"))) = {
    0xC0, 0xC0, 0xE0, 0xA0, 0x30, 0x10, 0xD8, 0xEE, 0xC2, 0x0E, 0x38, 0xE0,
    0x00, 0x00, 0x00, 0x01, 0x06, 0x1C, 0x30, 0x60, 0x38, 0x0C, 0x06, 0x01
};


int main () {
    unsigned char my_buff[16] = {0};
 
    while (1);
}
