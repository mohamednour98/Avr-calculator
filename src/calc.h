/*
 * calc.h
 *
 * Created: 10/28/2018 3:11:53 PM
 *  Author: carnival
 */ 


#ifndef CALC_H_
#define CALC_H_
unsigned char arr[32];
char result[10];
char numberofelemets=0;

unsigned char d;



typedef struct elnt {

	int number;

	char isopernd;

}elmnt;

elmnt elements[32];
void calculate_manage(void);
void arr_allocator(unsigned char ar[]);
void arr_reverse(unsigned char ar[],unsigned char i);
void push(char x);
void pop(void);

void calc_manage(void);



#endif /* CALC_H_ */