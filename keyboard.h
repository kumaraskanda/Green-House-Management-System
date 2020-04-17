#ifndef _keyboard_H_
#define _keyboard_H_
#include <lpc214x.h>
#include <stdio.h>

#define COL0 (IO1PIN & 1 <<28)
#define COL1 (IO1PIN & 1 <<27)
#define COL2 (IO1PIN & 1 <<26)
void delay_ms_(unsigned int j);	
unsigned int key_select(void);

#endif

