/*
 * GPIO.c
 *
 * Created: 03-Sept-18 11:01:26 PM
 *  Author: Karim
 */ 

#include "GPIO.h"
#include "GPIO_CFG.h"

typedef volatile uint8_t* const REGPTR ;
#define GPIO_BASE_ADDR 0x3b
#define PORT_OFFSET 0
#define DDR_OFFSET 1u
#define PIN_OFFSET 2u

uint8_t PERIPH_ADDR(uint8_t PORTID)			{return ((PORTID - 0x0a) * 0x03);}

#define PORT(PORTID)				*((REGPTR) ((GPIO_BASE_ADDR - PERIPH_ADDR(PORTID)) - PORT_OFFSET))
#define DDR(PORTID)					*((REGPTR) ((GPIO_BASE_ADDR - PERIPH_ADDR(PORTID)) - DDR_OFFSET))
#define PIN(PORTID)					*((REGPTR) ((GPIO_BASE_ADDR - PERIPH_ADDR(PORTID)) - PIN_OFFSET))

#define S_REG 						*((REGPTR) (0x5F))
#define MCUCRREG 					*((REGPTR) (0x55))
#define GICRREG						*((REGPTR) (0x5B))
#define MCUCSRREG					*((REGPTR) (0x54))
#define GIFRREG						*((REGPTR) (0x5A))

#define MCUCSRREG_INT2_PINNUM 6u
#define SREG_INT_PINNUM 7u

uint8_t init_states[USEDPINS] = {0};
	
volatile uint8_t temp;

uint8_t GPIO_INIT(void)
{
	uint8_t index;
	uint8_t ERROR = 0;
	
	const PIN_CONFIG* PTR;
	
	for (index = 0 ; index < USEDPINS && ERROR != 1 ; index++)
	{
		PTR = & PIN_PARAM[index];
		
		if ((PTR-> PORT >= 0x0A) && (PTR-> PORT <= 0x0f) && (PTR-> PORTNUM >= 0x00) && (PTR-> PORTNUM <= 0x07))
		{
			if((PTR ->  DIR) == 0x00)
			{
				DDR(PTR->  PORT) |= (PTR-> DIR & (1 << PTR-> PORTNUM));
				PORT(PTR->  PORT) |= (PTR-> PU & (1 << PTR-> PORTNUM));
			} 
			else if((PTR ->  DIR) == 0xff)
			{
				DDR(PTR->  PORT) |= (PTR-> DIR & (1 << PTR-> PORTNUM));
				PORT(PTR->  PORT) |= (PTR-> OUTSTATE & (1 << PTR-> PORTNUM));  
			}
			else
			{
				ERROR = 1 ;
			}
			init_states[index] = 1 ;
		}
			
		else
		{
			ERROR = 1; 
		}
	}
	
	return ERROR;
}

void SetPortInput(uint8_t PortID)
{
	DDR(PortID) = 0x00;
}

void SetPortOutput(uint8_t PortID)
{
	DDR(PortID) = 0xff;
}

void GPIO_PortWrite(uint8_t PortID, uint8_t Data)
{
	PORT(PortID) = Data;
}

void GPIO_PinWrite(uint8_t PIN_CONFIG_Index, uint8_t Data)
{
	if (PIN_CONFIG_Index < USEDPINS)
	{
		const PIN_CONFIG* PTR;
		
		PTR = & PIN_PARAM[PIN_CONFIG_Index];
		
    	if ((PTR-> DIR == 0xff) && (init_states[PIN_CONFIG_Index] == 1))
    	{
			if ((Data == 0xff) || (Data == 1))
			{
				PORT(PTR -> PORT) |= (0xff & (1 << (PTR-> PORTNUM)));
			}
			else if ((Data == 0x00) || (Data == 0))
			{
				PORT(PTR -> PORT) &= ~(1 << (PTR-> PORTNUM));
			}  
    	}
	}
}

void GPIO_PortWriteMask(uint8_t PortID, uint8_t Data, uint8_t Mask)
{
	if ((Data == 0xff) || (Data == 1))
	{
		PORT(PortID) |= (0xff & Mask);
	}
	else if ((Data == 0x00) || (Data == 0))
	{
		PORT(PortID) &= ~(0xff & Mask);
	}
}

uint8_t GPIO_ReadPort(uint8_t PortID)
{
	temp = PIN(PortID);
	return temp;
}

uint8_t GPIO_ReadPin(uint8_t PIN_CONFIG_Index)
{
	if (PIN_CONFIG_Index < USEDPINS)
	{
  		const PIN_CONFIG* PTR;
		 
		PTR = & PIN_PARAM[PIN_CONFIG_Index];
		temp = PIN(PTR -> PORT);
		return ((temp >> (PTR -> PORTNUM)) & 1) ;
    } 
}

void EnableGlobalInterrupts(void)
{
	S_REG |= (1 << SREG_INT_PINNUM) ;
}

void DisableGlobalInterrupts(void)
{
	S_REG &= ~(1 << SREG_INT_PINNUM) ;
}

uint8_t GPIO_EnableInterrupt(INT_PIN intpin)
{
	if (( (S_REG >> SREG_INT_PINNUM) | 1) == 1)
	{
    	GICRREG |= (1 << (intpin + 5));
		return 0 ;
      
    } else{return 1; }
}

uint8_t GPIO_SetInterruptType(INT_PIN intpin, INT_TYPE inttype)
{
	uint8_t ERROR = 0;
	if (intpin != 0)
	{
		if (( (S_REG >> SREG_INT_PINNUM ) | 1) == 1)
		{
			MCUCRREG |= (inttype << ((intpin-1) * 2)) ;;
        
		} else{ERROR = 1;}
	}
	else
	{
		if (inttype > 0x2)
		{
			MCUCSRREG |= ( inttype & (1 << MCUCSRREG_INT2_PINNUM) );
		} 
		else
		{
			ERROR = 1 ;
		}
	}
	return ERROR;
}

void GPIO_ClearInterrupt(INT_PIN intpin)
{
	GIFRREG |= (1 << (intpin + 5));
 }