#ifndef DIS_MAGR_H
#define DIS_MAGR_H
#include "DIS_MAGR.h"
#include "lcd_4bit.h"



typedef enum
{
	wrt_num = 1,
	wrt_symbol,
	wrt_DEL,
	CLR
}StatFlag_t;

void Disp_Init(void);

void Disp_wrt_num(unsigned char data);
void Disp_wrt_operator(unsigned char data);
void Disp_wrt_DEL(void);

void lcd_actiondone(void);

void Disp_MGR(void);

#endif