/*
 * UART.h
 *
 *  Created on: Sep 8, 2018
 *      Author: karim
 */

#ifndef UART_H_
#define UART_H_

#include <stdint.h>
#include "UART_CFG.h"

/*
typedef struct
{
    uint16_t BaudRate;                  // Set Baud Rate
    union ENABLES
    {
        uint16_t BITFIELDS ;
        struct bits
        {
            uint8_t ENABLE : 1;			
            uint8_t ASsync : 1;			// Asynchronous or Synchronous
            uint8_t ND_Async : 1;		// Normal or Double Speed Asynchronous
            uint8_t MS_Sync : 1;		// Master or Slave Synchronous mode
            uint8_t DataBits : 2;       // Character Size
            uint8_t StopBits : 1;       // 1 or 2 Stop Bits
            uint8_t paritybit : 1;      // Enable Parity Bit
            uint8_t EvenOdd : 1;		// Even or Odd Parity Bit
            uint8_t TX_EN : 1;			// Transmitter Enable
            uint8_t RX_EN : 1;			// Receiver Enable
            uint8_t UDRI_E : 1;			// Data Register Empty Interrupt Enable
            uint8_t TXCI_E : 1;          // Transmitter Complete Interrupt Enable
            uint8_t RXCI_E : 1;          // Receiver Complete Interrupt Enable
        }BITS;
    }ENABLES;
} UART_CH_CFG;
*/

typedef struct
{
	uint32_t BaudRate;                  // Set Baud Rate
	uint8_t ENABLE;
	uint8_t ASsync;			// Asynchronous or Synchronous
	uint8_t ND_Async;		// Normal or Double Speed Asynchronous
	uint8_t MS_Sync;		// Master or Slave Synchronous mode
	uint8_t DataBits;       // Character Size
	uint8_t StopBits;       // 1 or 2 Stop Bits
	uint8_t paritybit;      // Enable Parity Bit
	uint8_t EvenOdd ;		// Even or Odd Parity Bit
	uint8_t TX_EN ;			// Transmitter Enable
	uint8_t RX_EN ;			// Receiver Enable
	uint8_t UDRI_E;			// Data Register Empty Interrupt Enable
	uint8_t TXCI_E;          // Transmitter Complete Interrupt Enable
	uint8_t RXCI_E;          // Receiver Complete Interrupt Enable
} UART_CH_CFG;

void UART_Init(void);
void UART_BaudSetup(uint32_t BaudRate);
void UART_Transmit(uint8_t *Data);
void UART_Recieve(uint8_t *Data);
void LED_Display(uint8_t Data[]);

#endif /* UART_H_ */
