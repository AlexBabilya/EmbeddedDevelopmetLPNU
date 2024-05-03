#include "global.h"
#include <string.h>

short SPIInit(void);
void Touch_Read (uint8_t reg, uint8_t* val);
void Touch_Write (uint8_t reg, uint8_t val);
void Set_State_CS(GPIO_PinState pinState);