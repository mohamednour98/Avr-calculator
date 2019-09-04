/*
 * UART_CFG.c
 *
 *  Created on: Sep 10, 2018
 *      Author: Karim
 */

#include "UART.h"
#include "UART_CFG.h"

/*
 * ASsync =>	0: Asynchronous
				1: Synchronous

 * ND_Async =>	0: Normal Speed Asynchronous
				1: Double Speed Asynchronous
				
 * Data Bits => 0: 5bits 
				1: 6bits
				2: 7bits
				3: 8bits
				 
 * Stop Bits => 0: 1bit
				1: 2bits
				
 * even/odd =>  0: Even Parity
				1: Odd Parity
 */	

UART_CH_CFG CONFIGURATION[NUM_OFUSED_CHANNELS] = {
/* BaudRate	 ENABLE   ASsync   ND_Async   MS_Sync   data bits	stop bits	parity bit	even/odd	TXEN	RXEN	UDRIE	TXCIE	RXCIE */
{   9600	,   1  ,    0	 ,     0    ,    0	  ,    3	  ,		0	  ,      0	   ,    0	  ,   1	  ,   1   ,	  0	   ,   0   ,   0   }
																																			   };

