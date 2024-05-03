#include "accelerometer.h"
//read from the registr
uint8_t Read_Val_Reg(uint8_t reg){
    uint8_t val; 
    Touch_Read(reg, &val);
    return val;
}

void LIS3DSH_ReadAxes(LIS3DSH_t* Axes_Data){
    uint8_t buffer[6]; 
    buffer[0] = Read_Val_Reg(LIS3DSH_OUT_X_L_ADDR);
    buffer[1] = Read_Val_Reg(LIS3DSH_OUT_X_H_ADDR);
    buffer[2] = Read_Val_Reg(LIS3DSH_OUT_Y_L_ADDR);
    buffer[3] = Read_Val_Reg(LIS3DSH_OUT_Y_H_ADDR); 
    buffer[4] = Read_Val_Reg(LIS3DSH_OUT_Z_L_ADDR);
    buffer[5] = Read_Val_Reg(LIS3DSH_OUT_Z_H_ADDR); 
    Axes_Data->X = (int16_t)((buffer[1] << 8) + buffer[0]) * 0.06;
    Axes_Data->Y = (int16_t)((buffer[3] << 8) + buffer[2]) * 0.06; 
    Axes_Data->Z = (int16_t)((buffer[5] << 8) + buffer[4]) * 0.06;
}
