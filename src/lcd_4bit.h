
#ifndef _LCD_4BIT_H

	#define _LCD_4BIT_H
unsigned char *ptr;
unsigned char num;
unsigned char position = 0x80;
uint8_t init_state=0,clrScreen_state=0,dispstr_state=0,gotoxy_state=0,dispnum_state=0;

void enableTrigger(void);
void lcd_writecmd(unsigned char cmd);
void lcd_dispnumber(unsigned char data);
void lcd_init(void);
void lcd_gotoxy(unsigned char x , unsigned char y );
void lcd_clrScreen(void);
void lcd_dispString(unsigned char * disp);
void lcd_manage(void);
unsigned char gpio_sender(unsigned char pin);

#define uninitialized 0
#define initialize_in_prog 1
#define ready 2
#define str_in_prog 3


#endif  

