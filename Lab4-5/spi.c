#include "spi.h"

SPI_HandleTypeDef SPIInitStruct;

short SPIInit(void) { // Initialization
    GPIO_InitTypeDef GPIOInitStruct;
    __HAL_RCC_GPIOA_CLK_ENABLE();
    __HAL_RCC_GPIOE_CLK_ENABLE(); 

   
    memset(&GPIOInitStruct, 0, sizeof(GPIO_InitTypeDef));
    GPIOInitStruct.Pin = GPIO_PIN_5 | GPIO_PIN_6 | GPIO_PIN_7;
    GPIOInitStruct.Mode = GPIO_MODE_AF_PP;
    GPIOInitStruct.Pull = GPIO_NOPULL;
    GPIOInitStruct.Speed = GPIO_SPEED_FREQ_LOW;
    GPIOInitStruct.Alternate = GPIO_AF5_SPI1; 
    HAL_GPIO_Init(GPIOA, &GPIOInitStruct); 

    memset(&GPIOInitStruct, 0, sizeof(GPIO_InitTypeDef));
    GPIOInitStruct.Pin = GPIO_PIN_3;
    GPIOInitStruct.Mode = GPIO_MODE_OUTPUT_PP;
    GPIOInitStruct.Pull = GPIO_NOPULL;
    GPIOInitStruct.Speed = GPIO_SPEED_FREQ_LOW;
    HAL_GPIO_Init(GPIOE, &GPIOInitStruct);

    __HAL_RCC_SPI1_CLK_ENABLE(); 

    // Initialization spi
    SPIInitStruct.Instance = SPI2; //
    SPIInitStruct.Init.Mode = SPI_MODE_MASTER;
    SPIInitStruct.Init.Direction = SPI_DIRECTION_2LINES;
    SPIInitStruct.Init.DataSize = SPI_DATASIZE_16BIT;
    SPIInitStruct.Init.CLKPolarity = SPI_POLARITY_LOW; //CPOL = 0
    SPIInitStruct.Init.CLKPhase = SPI_PHASE_2EDGE; //CPHA = 1
    SPIInitStruct.Init.NSS = SPI_NSS_SOFT;
    SPIInitStruct.Init.BaudRatePrescaler = SPI_BAUDRATEPRESCALER_4;
    SPIInitStruct.Init.FirstBit = SPI_FIRSTBIT_LSB; //
    SPIInitStruct.Init.TIMode = SPI_TIMODE_DISABLE;
    SPIInitStruct.Init.CRCCalculation = SPI_CRCCALCULATION_DISABLE;
    SPIInitStruct.Init.CRCPolynomial = 10;

    if (HAL_SPI_Init(&SPIInitStruct) != HAL_OK)
        return 1;
    return 0;
}

void Touch_Read(uint8_t reg, uint8_t* val) {
    Set_State_CS(GPIO_PIN_RESET);
    reg = reg | 0x80;
    HAL_SPI_TransmitReceive(&SPIInitStruct, &reg, val, 1, 500);

    reg = 0;
    HAL_SPI_TransmitReceive(&SPIInitStruct, &reg, val, 1, 500);
    Set_State_CS(GPIO_PIN_SET);
}

void Touch_Write(uint8_t reg, uint8_t val) {
    uint8_t data[1];
    Set_State_CS(GPIO_PIN_RESET);

    HAL_SPI_TransmitReceive(&SPIInitStruct, &reg, data, 1, 500);

    HAL_SPI_TransmitReceive(&SPIInitStruct, &val, data, 1, 500);
    Set_State_CS(GPIO_PIN_SET);
}

void Set_State_CS(GPIO_PinState pinState) {
    HAL_GPIO_WritePin(GPIOE, GPIO_PIN_3, pinState);
}

