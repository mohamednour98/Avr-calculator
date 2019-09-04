/*
 * UART.C
 *
 *  Created on: Sep 8, 2018
 *      Author: karim
 */

#include "UART.h"
#include "GPIO.h"
#include "GPIO_CFG.h"

#define  F_CPU   8000000UL
#include <util/delay.h>

extern uint64_t CPUCLCK;

typedef volatile uint8_t* const REGPTR;

#define UART_BASE_ADDRESS                   0x2C

#define UBRRH_UCSRC							*((REGPTR)(0x40))							
#define UDR									*((REGPTR)(UART_BASE_ADDRESS - 0x00))   // USART I/O Data Register
#define UCSRA								*((REGPTR)(UART_BASE_ADDRESS - 0x01))   // USART Control and Status Register A
#define UCSRB								*((REGPTR)(UART_BASE_ADDRESS - 0x02))   // USART Control and Status Register B
#define UBRRL								*((REGPTR)(UART_BASE_ADDRESS - 0x03))	 // USART Baud Rate Register Low Byte

/* UCSRA Bit offsets */
#define MPCM								0x0										 // Multi-processor Communication Mode
#define U2X									0x1										 // Double the USART Transmission Speed
#define PE									0x2										 // Parity Error
#define DOR									0x3										 // Data OverRun
#define FE									0x4										 // Frame Error
#define UDRE								0x5										 // USART Data Register Empty
#define TXC									0x6										 // USART Transmit Complete
#define RXC									0x7										 // USART Receive Complete

/* UCSRB Bit offsets */
#define TXB8								0x0										 // Transmit Data Bit 8
#define RXB8								0x1										 // Receive Data Bit 8
#define UCSZ2								0x2										 // Character Size
#define TXEN								0x3										 // Transmitter Enable
#define RXEN								0x4										 // Receiver Enable
#define UDRIE								0x5										 // USART Data Register Empty Interrupt Enable
#define TXCIE								0x6										 // TX Complete Interrupt Enable
#define RXCIE								0x7										 // RX Complete Interrupt Enable

/* UCSRC Bit offsets */
#define UCPOL								0x0										 // Clock Polarity
#define UCSZ								0x1										 // Character Size
#define USBS								0x3										 // Stop Bit Select
#define UPM									0x4										 // Parity Mode
#define UMSEL								0x6										 // USART Mode Select
#define URSEL								0x7										 // Register Select

/* UBRRH Bit offsets */
#define URSEL								0x7										 // Register Select

void UBRRH(uint8_t BITS, uint8_t OFFSET)
{
	UBRRH_UCSRC &= ~(1 << URSEL);
	UBRRH_UCSRC |= (BITS << OFFSET);
}		            


void UCSRC(uint8_t BITS, uint8_t OFFSET)
{
	UBRRH_UCSRC |= (1 << URSEL) ;
	UBRRH_UCSRC |= (BITS << OFFSET);
}					


static uint8_t Init_States[NUM_OFUSED_CHANNELS] = {0};

extern UART_CH_CFG CONFIGURATION[NUM_OFUSED_CHANNELS];


void UART_BaudSetup(uint32_t BaudRate)
{
	volatile uint32_t temp ;
	if (((UCSRA << U2X) & 1) == 0)
	{
		temp = (CPUCLCK / (16 * BaudRate)) - 1;
	}
	else
	{
		temp = (CPUCLCK / (8 * BaudRate)) - 1;
	}
	
	UBRRL = temp;
	
	UBRRH((temp >> 8),0);
}

void UART_Init(void)
{
    volatile UART_CH_CFG* PTR;
    volatile uint8_t ERROR = 0, index = 0, temp=0;

    for(index ; index < NUM_OFUSED_CHANNELS && ERROR != 1 ; index++)
    {
        PTR = & CONFIGURATION[index];
        if((PTR ->  ENABLE == 1) && (PTR ->  DataBits >= 0) && (PTR ->  DataBits <= 3) && (PTR ->  StopBits >= 0) && (PTR ->  StopBits <= 1))
        {
			UCSRC(PTR ->  ASsync,UMSEL) ;
			UCSRA |= ((PTR ->  ND_Async) << U2X) ;
			
			UART_BaudSetup(PTR ->BaudRate);
			
			UCSRC( (PTR ->  DataBits), UCSZ);
			UCSRC( (PTR ->  StopBits), USBS);
			temp = UPM + 1;
			UCSRC( (PTR ->  paritybit), temp );
			UCSRC( (PTR ->  EvenOdd), UPM );
			
			UCSRB = ((PTR ->  RXCI_E) << RXCIE) | ((PTR ->  TXCI_E) << TXCIE)|
					((PTR ->  UDRI_E) << UDRIE) | ((PTR ->  RX_EN) << RXEN)|
					((PTR ->  TX_EN) << TXEN);
        }
        else {ERROR = 1; Init_States[0] = 1;}
    }
}

void UART_Transmit(uint8_t *Data)
{
	while(*Data != '\0')
	{
		if (( (UCSRA>>UDRE) & 1) == 1)
		{	
			UDR = *Data; 
			
			++Data;
		}
	}
	UCSRA &= ~(1 << TXC);
}

void UART_Recieve(uint8_t *Data)
{
	while(!(UCSRA&(1<<RXC))==0)
	{
		*Data = UDR;
		Data++;
	}
}

/*
void LED_Display(uint8_t Data[])
{
	volatile uint8_t index = 0;
	for(index=0 ; index < NUM_OF_CHARS ; index++)
		{
			_delay_ms(1000);
			GPIO_PortWrite(0x0A, Data[index]);
		}
}*/

