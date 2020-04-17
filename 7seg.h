#ifndef _7seg_H_
#define _7seg_H_


#include <LPC214X.H>
#include <stdio.h>
#include <string.h>
void delay_milli(unsigned int j);
unsigned char dot(void);
unsigned char get(unsigned char alpha);
void seg(char *buf);
void seg1(char *buf);
void dispInt(long int num);
void dispFloat(float num);


#endif

