#include <stm32f4xx_adc.h> 
void adc_init(void); 
u16 readADC1(u8 channel); 
void gpio_init(void); 

int main() { 
	unsigned int result; 
  	adc_init(); 
	do{ 
		result = readADC1(ADC_Channel_1); 
		if(((result - 0.76)/0.0025 + 25)<15){ 
			GPIOD->ODR = 0x4000; 
		} 
		else { 
			GPIOD->ODR = 0x8000; 
		} 
	} 
	while (1); 
} 

void gpio_init() { 
	RCC->AHB1ENR |= RCC_AHB1ENR_GPIODEN; 
	GPIOD->MODER = 0x55000000; 
	GPIOD->OTYPER = 0;
	GPIOD->OSPEEDR = 0; 
} 

void adc_init() { 
	ADC_InitTypeDef ADC_InitStructure; 
	ADC_CommonInitTypeDef adc_init; 
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_ADC1, ENABLE); 
	ADC_DeInit(); 
	ADC_StructInit(&ADC_InitStructure); 
	adc_init.ADC_Mode = ADC_Mode_Independent; 
	adc_init.ADC_Prescaler = ADC_Prescaler_Div2; 
	ADC_InitStructure.ADC_ScanConvMode = DISABLE; 
	ADC_InitStructure.ADC_ContinuousConvMode = DISABLE; 
	ADC_InitStructure.ADC_ExternalTrigConv = ADC_ExternalTrigConvEdge_None;
	ADC_InitStructure.ADC_DataAlign = ADC_DataAlign_Right; 
	ADC_InitStructure.ADC_Resolution = ADC_Resolution_12b; 
	ADC_CommonInit(&adc_init); 
	ADC_Init(ADC1, &ADC_InitStructure); 
	ADC_Cmd(ADC1, ENABLE); 
}

u16 readADC1(u8 channel) { 
	ADC_RegularChannelConfig(ADC1, channel, 1, ADC_SampleTime_3Cycles);
	ADC_SoftwareStartConv(ADC1); 
	while (ADC_GetFlagStatus(ADC1, ADC_FLAG_EOC) == RESET); 
	return ADC_GetConversionValue(ADC1); 
}
