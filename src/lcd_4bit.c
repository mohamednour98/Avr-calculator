/*
 * lcd_4bit.c
 *
 * Created: 10/19/2018 7:30:00 PM
 *  Author: carnival
 */ 

#define F_CPU 16000000UL
#include"lcd_4bit.h"
#include <avr/io.h>
#include <util/delay.h>
#include "lcd_config.h"
#include "GPIO.h"
#include "stdlib.h"
#include <avr/delay.h>

 /////////////////////////////////////////////////////////////////////
//	lcd enable triggering function to make lcd aware about command or
//   data changes.
////////////////////////////////////////////////////////////////////
unsigned char *ptr;
unsigned char num;
unsigned char position = 0x80;
uint8_t init_state=0,clrScreen_state=0,dispstr_state=0,gotoxy_state=0,dispnum_state=0;


void (*callBackptr)(void);


void enableTrigger(void)
{

	GPIO_PinWrite(Enable,0x00);
	
	_delay_us(50);

	GPIO_PinWrite(Enable,0xff);
	


}

///////////////////////////////////////////////////////////////////////////////////////
// LCD initialization API : set portB from pinB.4 to pinB.7 as o/p for data and commands 
//							 and pinB.0 to pinB.2 o/p for control pins 
//////////////////////////////////////////////////////////////////////////////////////
void lcd_init(void)
{

	init_state=1;

		
}


void lcd_writecmd(unsigned char cmd)
{

	

	GPIO_PinWrite(8,0x00); // to enable command mode 
	GPIO_PinWrite(9,0x00); // write signal to lcd 

	/* PORTB &=0x0f;
	PORTB |=high_nibble;// to send high nibble command  */
	
	GPIO_PinWrite(11,gpio_sender(cmd&16));
	
	//Uart_Tx(gpio_sender(cmd&16));
	GPIO_PinWrite(12,gpio_sender(cmd&32));
	GPIO_PinWrite(13,gpio_sender(cmd&64));
	GPIO_PinWrite(14,gpio_sender(cmd&128));
	
	_delay_us(50);
	enableTrigger(); // triggre lcd enable 
	
_delay_us(50);
	GPIO_PinWrite(11,gpio_sender(cmd&1));
	GPIO_PinWrite(12,gpio_sender(cmd&2));
	GPIO_PinWrite(13,gpio_sender(cmd&4));
	GPIO_PinWrite(14,gpio_sender(cmd&8));
	_delay_us(50);
	enableTrigger();
	
_delay_us(50);
}

void lcd_writedata (unsigned char data)
{

	//Uart_Tx(data);
	GPIO_PinWrite(RS,0xff); //  enable data mode 
	GPIO_PinWrite(RW,0x00); // activate lcd write 

	GPIO_PinWrite(11,gpio_sender(data&16));
	GPIO_PinWrite(12,gpio_sender(data&32));
	GPIO_PinWrite(13,gpio_sender(data&64));
	GPIO_PinWrite(14,gpio_sender(data&128));
	
	
	_delay_us(50);
	enableTrigger(); // triggre lcd enable 
	_delay_us(50);
	GPIO_PinWrite(11,gpio_sender(data&1));
	GPIO_PinWrite(12,gpio_sender(data&2));
	GPIO_PinWrite(13,gpio_sender(data&4));
	GPIO_PinWrite(14,gpio_sender(data&8));
	_delay_us(50);
	enableTrigger();
	
	_delay_us(40);
	

}


void lcd_gotoxy(unsigned char y , unsigned char x )
{
	
	 
	switch(y)
	{
		case 0:

			position=position+x;
					
		break;

		case 1:

			position=0xc0;
			position=position+x;

		break;

		
	
	
	}
	
	// lcd_sendCommand(position); 	by task

gotoxy_state=1;
}


void lcd_clrScreen(void)
{

	
clrScreen_state=1;

}


void lcd_dispString(unsigned char * disp)
{
dispstr_state=1;
ptr=disp;

}
void lcd_dispnumber(unsigned char numm ){
	
	
	dispnum_state=1;
	num=numm;
}


unsigned char  gpio_sender(unsigned char pin){
	
	if(pin ==0){
		return 0x00;
	}
	else {
		return 0xff;
	}
}
void lcd_manage(void){
	
	
		 static uint8_t state=0; // unintialized
		 static uint8_t counts=0;
		 uint8_t tempstr=0;
		
		switch(state )
		{
			case uninitialized: 
			if(init_state==1){
				state=initialize_in_prog ;
					counts=0;
				break;
				
			}
			
			case initialize_in_prog:
			switch(counts){
				
				case 1:
				
				lcd_writecmd(0x33); 
				
				break;
				case 2:
				lcd_writecmd(0x32);
				
				break;
				case 3:
				lcd_writecmd(0x28);
				
				
				break;
				case 4:
				lcd_writecmd(0x0f);
				
				
				break;
				
			}
			if(counts>7){
				
				
				
				state=ready;
			}
			break;
		
			
		
		case ready:
		
		if(clrScreen_state==1){
			
			lcd_writecmd(0x01);
			callBackptr();
			clrScreen_state=0;
			break;
		}
		else if(dispstr_state==1){
			
			state=str_in_prog; 
			
			
			
		}
		else if(dispnum_state==1){
			
			 lcd_writedata(num);
			callBackptr();
			
			dispnum_state=0;
			break;
		}
		else if(gotoxy_state==1){
			
			lcd_writecmd(position);
			callBackptr();
			gotoxy_state=0;
			break;
			
		}
		else {
			break;
		}
		case str_in_prog: 
		
		while(* ptr!= '\0')
		{
			
				lcd_writedata(* ptr); // ??
				ptr++;
				tempstr=1;
				break;
			
		}
		if(tempstr==0){
			callBackptr();
			state=ready;
			dispstr_state=0;
		}
		break;
		
	}


	counts++;
}
	
