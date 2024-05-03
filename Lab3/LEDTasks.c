#include "LEDTasks.h"
#include <stm32f4xx.h>

void greenLEDTask() {
    osEvent evt;
    while(1) {
        evt = osSignalWait(0x0001,osWaitForever);
        if(evt.status == osEventSignal) {
            GPIOD->ODR = 0x1000;
            osDelay(2000);
        }
        osThreadYield();
    }
}

void orangeLEDTask() {
    osEvent evt;
    while(1) {
        evt = osSignalWait(0x0001,osWaitForever);
        if(evt.status == osEventSignal) {
            GPIOD->ODR = 0x2000;
            osDelay(2000);
        }
        osThreadYield();
    }
}

void redLEDTask() {
    while(1) {
        GPIOD->ODR = 0x4000;
        osDelay(1000);
    }
}

void blueLEDTask() {
    while(1) {
        GPIOD->ODR = 0x8000;
        osDelay(1000);
    }
}
