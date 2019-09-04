/*
 * UART.c
 *
 * Created: 9/11/2018 7:55:25 AM
 * Author : carnival
*/ 
#include <stdint.h>



#include <avr/io.h>
#include "FreeRTOS.h"
#include "task.h"
#include "FreeRTOSConfig.h"
//#ifndef F_CPU
#define F_CPU 16000000UL
const uint64_t CPUCLCK = F_CPU;
//#endif
#include "GPIO.h"




#include "semphr.h"
#include "lcd_4bit.h"
#include <avr/delay.h>
#include "queue.h"
#include "lcd_4bit.h"
#include "DIS_MAGR.h"
#include "UART.h"
#include "KeyPad.h"
void Uart_Tx(unsigned char x[]);

void LcdTask(void *p)
{
		portTickType xLastWakeTime;
		const portTickType xPeriod =2;

		xLastWakeTime=xTaskGetTickCount();

		
		
		while(1){
			vTaskDelayUntil( &xLastWakeTime, xPeriod );
			lcd_manage();
		}			
	
}
void KpdTask(void *p)
{
	portTickType xLastWakeTime;
	const portTickType xPeriod =10;

	xLastWakeTime=xTaskGetTickCount();

	
	
	while(1){
		vTaskDelayUntil( &xLastWakeTime, xPeriod );
		KPD_MANAGE();
		
	}
}

void DspTask(void* p)
{
	portTickType xLastWakeTime;
	const portTickType xPeriod =5;

	xLastWakeTime=xTaskGetTickCount();

	
	
	while(1){
		vTaskDelayUntil( &xLastWakeTime, xPeriod );
		Disp_MGR();
		
	}
}

void CalcTask(void* p)
{
	portTickType xLastWakeTime;
	const portTickType xPeriod =20;

	xLastWakeTime=xTaskGetTickCount();

	
	
	while(1){
		vTaskDelayUntil( &xLastWakeTime, xPeriod );
		calculate_manage();
		
	}
}


int main(void)
{
	
	xTaskCreate(LcdTask,NULL,configMINIMAL_STACK_SIZE,NULL,1,NULL);
	xTaskCreate(DspTask,NULL,configMINIMAL_STACK_SIZE,NULL,2,NULL);
	xTaskCreate(KpdTask,NULL,configMINIMAL_STACK_SIZE,NULL,3,NULL);
   xTaskCreate(CalcTask,NULL,configMINIMAL_STACK_SIZE,NULL,4,NULL);
		GPIO_INIT();
	lcd_init();
	KPD_INIT();
	Disp_Init();
	UART_Init();
	

	
	
	vTaskStartScheduler();
	while(1)
	{
		
	}

}

/*void task(void*pvParameter ){
	portTickType xLastWakeTime;
	const portTickType xPeriod =2;

	xLastWakeTime=xTaskGetTickCount();

	
	
	while(1){
		vTaskDelayUntil( &xLastWakeTime, xPeriod );
		lcd_manage();
		//Uart_Tx(x);
		
	}
		
}
void test(void*pvParameter ){
	portTickType xLastWakeTime;
	const portTickType xPeriod =200;

	xLastWakeTime=xTaskGetTickCount();

	
	
	while(1){
		vTaskDelayUntil( &xLastWakeTime, xPeriod );
		lcd_dispString("mostafa");
		 
	}
}

*/






