/*
 * calc.c
 *
 * Created: 10/28/2018 3:11:39 PM
 *  Author: carnival
 */ 
#define F_CPU 16000000UL
#include "calc.h"
#include "string.h"
#include <avr/io.h>
#include <util/delay.h>
#include "UART.h"
extern unsigned char calcflag;

int A[50]; // this is a stack

int top=-1;

void push(char x){
	A[++top]=x;
}
void pop(void){
	if(isempty()==0){
		top--;

	}
	else {
		return ;
	}


}
int tops(void){

	return A[top];
}
int isempty(void){
	if (top==-1) return 1;
	else return 0;
}
////////////////////////////////////////////////////////
elmnt S[50]; // this is a stack

int top1=-1;

void push1(int x){
	S[++top1].number=x;
}
void pop1(void){
	if(isempty1()==0){
		top1--;

	}
	else {
		return ;
	}


}
int tops1(void){

	return S[top1].number;
}
int isempty1(void){
	if (top1==-1) return 1;
	else return 0;
}
char isoperand(unsigned char element){
	if(element ==45 || element ==42 ||element ==43 ||element ==47 ){
		return 1;
	}
	else if(element >=48 && element <= 57)
{return 0;}
	else{
		return 2;
	}
}
char higherpiriority(unsigned char topstack , unsigned char noperator){

	if(topstack ==42 || topstack ==47  ){
		return 1;
	}
	else if((topstack ==43 || topstack ==45 ) && ((noperator ==42 || noperator ==47) ) ){
		return 0;
	}
	else {
		return 1;
	}

}
char temp[10]={};
void changingtopostfix(char *arr,unsigned char arr_size){
	unsigned char i;

	unsigned char s=0;
unsigned char element[6]={};

for(i=0;i<arr_size;i++){

	if(isoperand(arr[i])==0){

		element[s]=arr[i];
		s++;
		if(isoperand(arr[i+1])==1 || i==(arr_size-1)){
			elements[numberofelemets].number=atoi(element);
			elements[numberofelemets].isopernd=0;
			s=0;
			numberofelemets++;
			memset(element,' ',6);
		}

	}
	else if(isoperand(arr[i])==1) {
		while(!isempty() && higherpiriority(tops(),arr[i])){



			elements[numberofelemets].number=tops();
			elements[numberofelemets].isopernd=1;
			numberofelemets++;
			pop();

		}
		push(arr[i]);
	}

}

while(!isempty() ){


	elements[numberofelemets].number=tops();
	elements[numberofelemets].isopernd=1;

	numberofelemets++;

	pop();
}
for(i=0;i<numberofelemets;i++){
	if(elements[i].isopernd==0)
	printf("as:%d\n",elements[i].number);

}
}

void arr_allocator(unsigned char ar[]){
	unsigned char i=0;
	while(!isempty()){
		
		ar[i]=(unsigned char)tops();
		pop();
		i++;
		d=i;
	}
	arr_reverse( ar,i-1);
	
}
void arr_reverse(unsigned char ar[],unsigned char i){
	unsigned char index,temp;
	for(index=0;index<=(i/2);index++){
		temp=ar[index];
		ar[index]=ar[i-index];
		ar[i-index]=temp;
		
	}
	
	
}
void evaluation(){
	 int  i=0,op1,op2;
	elmnt element;
	while(numberofelemets>0 ){
element=elements[i];
		if(element.isopernd==0){

			push1(element.number);

		}
		else {
			op2=tops1();

			pop1();
			op1=tops1();

			pop1();
			switch(element.number){

				case '+' :
				push1(op1+op2);
				break;

				case '-' :
				push1(op1-op2);
				break;

				case '/' :
				push1(op1/op2);
				break;

				case '*' :
				push1(op1*op2);
				break;

			}
		}
			i++;
			numberofelemets--;
	}
}




void calculate_manage(void){
	if( calcflag==1){
		
		lcd_writedata('=');
		arr_allocator(arr);
		calculate(arr);
		
	
		calcflag=0;
		
	}else {
		
		return ;
	}
	
}
void calculate(unsigned char ar[]){
	
		
		d=strlen(ar);
		
		changingtopostfix(ar,d);
		//Uart_Tx(ar);
		evaluation();
		
		
		itoa(tops1(),result,10);
		while(!isempty1())
		{pop1();}
		lcd_dispString(result);
		memset(arr,'\0',32);
		

	
}