#include "stm32f4xx.h"
#include "cmsis_os.h"
#include "LEDTasks.h"
#include "init.h"
#include <misc.h>

void EXTI0_IRQHandler(void);
int counter = 0;
static uint32_t led_switch = 0;

void TimerTasks_Callback(void const *arg);

osThreadId tid_redLEDTask;
osThreadId tid_blueLEDTask;
osThreadId tid_greenLEDTask;
osThreadId tid_orangeLEDTask;

osTimerId  tid_TimerTasks;

void greenLEDTaskUNI() {
   	while(1) 
		if (counter%2) {
		    GPIOD->ODR = 0x1000;
	        osDelay(1000);
		} else {
		    GPIOD->ODR = 0x0000;
		}
	}
}

osThreadDef(redLEDTask,osPriorityNormal,1,0);
osThreadDef(blueLEDTask,osPriorityNormal,1,0);
osThreadDef(greenLEDTaskUNI, osPriorityNormal, 1, 0);
osThreadDef(orangeLEDTask, osPriorityNormal, 1, 0);

osTimerDef (TimerTasks, TimerTasks_Callback);

int main() {
   	RCC->AHB1ENR |= RCC_AHB1ENR_GPIOAEN;
    RCC->AHB1ENR |= RCC_AHB1ENR_GPIODEN;
    RCC->APB2ENR |= RCC_APB2ENR_SYSCFGEN;
    LEDInit();
	EXTIInit();
    osKernelInitialize(); 

    tid_TimerTasks = osTimerCreate(osTimer(TimerTasks), osTimerPeriodic, &tim);
    if (tid_TimerTasks != NULL)  {
        if (osTimerStart (tid_TimerTasks, 20) != osOK) {
			return 0;
        } 
    }
	else return 0;
    tid_redLEDTask = osThreadCreate (osThread(redLEDTask), NULL);
    tid_blueLEDTask = osThreadCreate (osThread(blueLEDTask), NULL);*/
	tid_greenLEDTask = osThreadCreate(osThread(greenLEDTaskUNI), NULL);
    tid_orangeLEDTask = osThreadCreate(osThread(orangeLEDTask), NULL);
  
	osKernelStart();
}

void TimerTasks_Callback(void const *arg) {
    osSignalSet(tid_greenLEDTask, 1);
    osSignalSet(tid_orangeLEDTask, 1);
}

void EXTI0_IRQHandler() {
    if (EXTI->PR & EXTI_PR_PR0) {
        if (!led_switch){
			osThreadTerminate(tid_greenLEDTask);
			counter += 1;
			EXTI->PR = EXTI_PR_PR0;
			}			
		}
}

