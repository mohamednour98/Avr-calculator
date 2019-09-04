#include <stdint.h>
#include <stdlib.h>
#include "DIS_MAGR.h"
#include "lcd_4bit.h"
#include "UART.h"
#include <avr/io.h>
#include <avr/delay.h>
#include "calc.h"

extern unsigned char A[50];

extern unsigned char arr[32];
extern unsigned char result[6];
uint8_t CallBckFunFlag = 0 ;
uint8_t StatFlag = 0;
unsigned char calcflag=0;
/*
	StatFlag = 1 => Disp_wrt_num()
	StatFlag = 2 => Disp_wrt_operator()
	StatFlag = 3 => Disp_wrt_DEL()
*/

 volatile uint8_t Cursor_Pos_X ;
 volatile uint8_t Cursor_Pos_Y ;
 
volatile unsigned char  data = NULL;
volatile unsigned char  Data = NULL;

volatile uint8_t RepeatedOper ;
extern void (*Kpd_NewDataPtr)(char NewData);

extern void (*callBackptr)(void)=lcd_actiondone;

void display_function(unsigned char Dataa)
{
	switch (Dataa){
		case '0':
		case '1':
		case '2':
		case '3':
		case '4':
		case '5':
		case '6':
		case '7':
		case '8':
		case '9':
		{
			Disp_wrt_num(Dataa);
			Uart_Tx("asd");
			
			break;
		}
		case '+':
		case '-':
		case '*':
		case '/':
		{
			Disp_wrt_operator(Dataa);
			break;
		}
		case ' ':
		{
			Disp_wrt_DEL();
			break;
		}
		case '=':
		{
			calcflag=1;
			
			//PORTA=tops();
		//lcd_dispString(arr);			
		}
		
	}
}

void Disp_Init(void)
{
	Cursor_Pos_X = 0;
	Cursor_Pos_Y = 0;
	RepeatedOper = 0;
}

void Disp_wrt_num(unsigned char data)
{
	Data = data;
	RepeatedOper = 0;
	StatFlag = wrt_num;
	
}

void Disp_wrt_operator(unsigned char data)
{
	Data = data;
	RepeatedOper++;
	StatFlag = wrt_symbol;
}

void Disp_wrt_DEL(void)
{
	StatFlag = wrt_DEL;
}

void Disp_Clear(void)
{
	StatFlag = CLR;
}

void lcd_actiondone(void)
{
	CallBckFunFlag = 1;
}


void Disp_MGR(void)
{
	static uint8_t delete=0;
	if (CallBckFunFlag==0)
	{
		if (StatFlag == wrt_num)
		{
			if(Cursor_Pos_X==15)
			{
				Cursor_Pos_X=0;
				Cursor_Pos_Y++;
				lcd_gotoxy(Cursor_Pos_Y,Cursor_Pos_X);
				
			}
			else
			{
				
				
				++Cursor_Pos_X;
			}
			push(Data);
			lcd_dispnumber(Data);
			StatFlag=0;
		}

		else if (StatFlag == wrt_symbol)
		{
			if (RepeatedOper == 1)
			{
				if(Cursor_Pos_X==15)
				{
					Cursor_Pos_X=0;
					Cursor_Pos_Y++;
					lcd_gotoxy(Cursor_Pos_Y,Cursor_Pos_X);
					
				}
				else
				{
					
					
					++Cursor_Pos_X;
				}
				
				
				lcd_dispnumber(Data);
				push(Data);
				
				StatFlag=0;
				

			}else if (RepeatedOper >= 2)
			
			{
				lcd_writecmd(0x10);
				push(Data);
				lcd_dispnumber(Data);
				StatFlag=0;
			}
			
				
			
		}
		
		else if (StatFlag == CLR)
		{
			lcd_clrScreen();
			
			Cursor_Pos_X=0;
			Cursor_Pos_Y=0;
			lcd_gotoxy(Cursor_Pos_Y,Cursor_Pos_X);
			
			StatFlag=0;
		}
			
		else if (StatFlag == wrt_DEL)
		{
			
			
			if(Cursor_Pos_Y==1 && Cursor_Pos_X==0)
			{
				
				Cursor_Pos_X=15;
				Cursor_Pos_Y=0;
				lcd_gotoxy(Cursor_Pos_Y,Cursor_Pos_X);
			}
			else
			{
				Cursor_Pos_X--;
				
					lcd_writecmd(0x10);
			}
			if(Cursor_Pos_X >15){
				Cursor_Pos_X=0;
			}
			pop();
			StatFlag=0;	
				if(Cursor_Pos_X==0){lcd_writecmd(0x01);}
		}
			
		
	}else {
		CallBckFunFlag=0;
		
	}		
	
		 
}
void Uart_Tx(unsigned char x[])
{
	static uint8_t i=0;
	while(x[i]!='\0'){
		while(!(UCSRA&(1<<UDRE)));
		UDR=x[i];
		i++;
	}		
}