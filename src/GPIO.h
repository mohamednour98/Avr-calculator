/*
 * GPIO.h
 *
 * Created: 03-Sep-18 11:01:45 PM
 *  Author: Karim
 */ 

#ifndef GPIO_H_
#define GPIO_H_

#include "GPIO_CFG.h"
#include <stdint.h>

typedef struct  
{
	uint8_t PORT; // Ex: 0xC => Port C
	uint8_t PORTNUM ;
	uint8_t DIR;  // Direction of the Pin
	uint8_t PU;  // Enable or Disable Pull-UP Resistor
	uint8_t OUTSTATE ;  // High or Low Output Pin

}PIN_CONFIG;

typedef enum {LOW = 0x00 , BOTHEDGES = 0x01 , FALLEDGE = 0X02 , RISEEDGE = 0x03} INT_TYPE ;
typedef enum {INTERRUPT2 = 0x00 , INTERRUPT0 = 0x01 , INTERRUPT1 = 0x02} INT_PIN ;
	
extern const PIN_CONFIG PIN_PARAM [USEDPINS];

uint8_t GPIO_INIT(void);
void SetPortInput(uint8_t PortID);
void SetPortOutput(uint8_t PortID);
void GPIO_PortWrite(uint8_t PortID, uint8_t Data);
void GPIO_PinWrite(uint8_t PIN_CONFIG_Index, uint8_t Data);
void GPIO_PortWriteMask(uint8_t PortID, uint8_t Data, uint8_t Mask);
uint8_t GPIO_ReadPort(uint8_t PortID);
uint8_t GPIO_ReadPin(uint8_t PIN_CONFIG_Index);

void EnableGlobalInterrupts(void);
void DisableGlobalInterrupts(void);
uint8_t GPIO_EnableInterrupt(INT_PIN intpin);
uint8_t GPIO_SetInterruptType(INT_PIN intpin, INT_TYPE inttype);
void GPIO_ClearInterrupt(INT_PIN intpin);

#endif /* GPIO_H_ */