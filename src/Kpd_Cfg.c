/*
 * CFile1.c
 *
 * Created: 10/26/2018 9:45:39 PM
 *  Author: carnival
 */ 
void  display_function(unsigned char Data);
void (*Kpd_NewDataPtr)(unsigned char NewData) =  display_function;