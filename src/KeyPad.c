/*
 * CFile1.c
 *
 * Created: 10/19/2018 7:18:09 PM
 *  Author: amr-m
 */ 
#include "KeyPad.h"
#include "GPIO.h"
#include <util/delay.h>
#include <string.h>
#include "lcd_4bit.h"
#include <avr/io.h>
#include "DIS_MAGR.h"



#define R1 0
#define R2 1
#define R3 2
#define R4 3
#define C1 4
#define C2 5
#define C3 6
#define C4 7
//#define notPressed 0
//#define Pressed 1
extern void (*Kpd_NewDataPtr)(char NewData);

										 
void KPD_INIT(void)
{
  GPIO_PortWrite(0x0c,0xff);
}
void KPD_MANAGE(void)
{
	 uint8_t  row,col,x1=0,x2=0,x3=0,x4=0;
	 int i = 0;
	 uint8_t state=0;
	static RowState = 0;
	//GPIO_PinWrite(i,0);
	
	unsigned char input = 0x00;
	unsigned char Output;
	
		
		GPIO_PinWrite(R1,0x00);
		GPIO_PinWrite(R2,0x00);
		GPIO_PinWrite(R3,0x00);
		GPIO_PinWrite(R4,0x00);
		
	
/*	Output=(~(1<<i) & 0x0f);
	// 0b 0000 0001 1111 1011
	GPIO_PinWrite(0,Output&1);
	GPIO_PinWrite(1,Output&2);
	GPIO_PinWrite(2,Output&4);
	GPIO_PinWrite(3,Output&8);
	*/
	input = GPIO_ReadPort(0x0c);
	input = input & (0xf0);
	input = ((~input) >> 4) & 0x0f;
	
	/*input = GPIO_ReadPort(0x0c);
	input = input & (0xf0);
	Output = input | (~(1<<i) & 0x0f);
	
	
	GPIO_PortWrite(0x0c,Output);
	input = GPIO_ReadPort(0x0c);
	input = input & (0xf0);
	input = ((~input) >> 4) & 0x0f;*/
	DDRA = 0xff;
	
	
		if(input!=0){
	if(RowState==0){
		
	row=0;
	GPIO_PinWrite(R1,0x00);
	GPIO_PinWrite(R2,0xff);
	GPIO_PinWrite(R3,0xff);
	GPIO_PinWrite(R4,0xff);
	x1=GPIO_ReadPin(C1);
	x2=GPIO_ReadPin(C2);
	x3=GPIO_ReadPin(C3);
	x4=GPIO_ReadPin(C4);
	col=(x1|(x2<<1)|(x3<<2)|(x4<<3) ) & 0x0F;
	if(col != 0x0F ) {
		 if (col == 0x0E){ Kpd_NewDataPtr(ascii[row][0]);  }  /* key in column 0 */
		else if (col == 0x0D){ Kpd_NewDataPtr(ascii[row][1]) ;} /* key in column 1 */
		 else if (col == 0x0B){ Kpd_NewDataPtr(ascii[row][2])  ;} /* key in column 2 */
		 else if (col == 0x07){ Kpd_NewDataPtr(ascii[row][3]) ;}/* key in column 3 */
		RowState=1;
		
				}
	}
		
		if(RowState==0){
			
	row=1;
	GPIO_PinWrite(R2,0x00);
	GPIO_PinWrite(R1,0xff);
	GPIO_PinWrite(R3,0xff);
	GPIO_PinWrite(R4,0xff);
	x1=GPIO_ReadPin(C1);
	x2=GPIO_ReadPin(C2);
	x3=GPIO_ReadPin(C3);
	x4=GPIO_ReadPin(C4);
	col=(x1|(x2<<1)|(x3<<2)|(x4<<3) ) & 0x0F;
	if(col != 0x0F ) {
	if (col == 0x0E){ Kpd_NewDataPtr(ascii[row][0]); }  /* key in column 0 */
    if (col == 0x0D){ Kpd_NewDataPtr(ascii[row][1]) ;} /* key in column 1 */
    if (col == 0x0B){ Kpd_NewDataPtr(ascii[row][2])  ;} /* key in column 2 */
    if (col == 0x07){ Kpd_NewDataPtr(ascii[row][3]) ;}/* key in column 3 */
		RowState=1;
		
				}
		}
		
		
		if(RowState==0){
	row=2;

	GPIO_PinWrite(R1,0xff);
	GPIO_PinWrite(R2,0xff);
	GPIO_PinWrite(R3,0x00);
	GPIO_PinWrite(R4,0xff);
	x1=GPIO_ReadPin(C1);
	x2=GPIO_ReadPin(C2);
	x3=GPIO_ReadPin(C3);
	x4=GPIO_ReadPin(C4);
	col=(x1|(x2<<1)|(x3<<2)|(x4<<3) ) & 0x0F;
	if(col != 0x0F ) {
	if (col == 0x0E){ Kpd_NewDataPtr(ascii[row][0]);}  /* key in column 0 */
    if (col == 0x0D){ Kpd_NewDataPtr(ascii[row][1]) ;} /* key in column 1 */
	if (col == 0x0B){ Kpd_NewDataPtr(ascii[row][2])  ;} /* key in column 2 */	
    if (col == 0x07){ Kpd_NewDataPtr(ascii[row][3]) ;}/* key in column 3 */
		RowState=1;
	
				}
	}
		
if(RowState==0){
	row=3;
	GPIO_PinWrite(R1,0xff);
	GPIO_PinWrite(R2,0xff);
	GPIO_PinWrite(R3,0xff);
	GPIO_PinWrite(R4,0x00);
	x1=GPIO_ReadPin(C1);
	x2=GPIO_ReadPin(C2);
	x3=GPIO_ReadPin(C3);
	x4=GPIO_ReadPin(C4);
	col=(x1|(x2<<1)|(x3<<2)|(x4<<3) ) & 0x0F;
	if(col != 0x0F ) {
	if (col == 0x0E){ Kpd_NewDataPtr(ascii[row][0]);}  /* key in column 0 */
    if (col == 0x0D){ Kpd_NewDataPtr(ascii[row][1]) ;} /* key in column 1 */
		 if (col == 0x0B){ Kpd_NewDataPtr(ascii[row][2])  ;} /* key in column 2 */
		 if (col == 0x07){ Kpd_NewDataPtr(ascii[row][3]) ;}/* key in column 3 */
		RowState=1;
		
		
					}
}





		 }
		 
		 if(input==0 && RowState==1){
			
			 RowState=0;
		 }
	}


	
	
	
	/*switch(i)
	{
		
		case 0:
		{
			if(RowState == 0)
			{
				if(input != 0)
				{
					PORTA = input;
					Kpd_NewDataPtr(ascii[i,input/2]);
					RowState = 1;
				}
			
			}
			else
			{
				
				if(input == 0)
				{
					
					i++;
					RowState = 0;
				}
				
			}
			break;
		}
		
		
		
		
		
	}
	*/
		
		 

	
	
