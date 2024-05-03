#include "stm32f4xx.h"
#include "spi.h"

#define LIS3DSH_WHO_AM_I_ADDR 0x0F
#define LIS3DSH_OUT_X_L_ADDR                0x28   // 00101000
#define LIS3DSH_OUT_X_H_ADDR                0x29  // 00101001
#define LIS3DSH_OUT_Y_L_ADDR                0x2A  // 00101010
#define LIS3DSH_OUT_Y_H_ADDR                0x2B  // 00101011
#define LIS3DSH_OUT_Z_L_ADDR                0x2C  // 00101100
#define LIS3DSH_OUT_Z_H_ADDR                0x2D  // 00101101

typedef struct {    
   	int16_t X;
    int16_t Y;    
	int16_t Z;
} LIS3DSH_t;

extern uint8_t Read_Val_Reg(uint8_t reg);
void LIS3DSH_ReadAxes(LIS3DSH_t* Axes_Data);
