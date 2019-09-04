/*
 * IncFile1.h
 *
 * Created: 10/19/2018 6:42:05 PM
 *  Author: carnival
 */ 


#ifndef INCFILE1_H_
#define INCFILE1_H_

unsigned char ascii[4][4]={{'7','8','9','/'},
                                     {'4','5','6','*'},
                                     {'1','2','3','-'},
                                     {' ','0','=','+'} };

void KPD_INIT(void);
void KPD_MANAGE(void);
//void (*callBack)(int);
//typedef  void (*callBack)(int);


#endif /* INCFILE1_H_ */