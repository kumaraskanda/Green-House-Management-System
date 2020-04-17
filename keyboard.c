#include <string.h>
#include "keyboard.h"
char lookup_table[4][3]={{'1', '2', '3'},
                                  {'1', '2', '3'}, 
                                  {'1', '2', '3'},
																	{'1', '2', '3'}
																};
unsigned char rowsel=0,colsel=0;	
char msg1[3];
unsigned int key_select(void)
{
	
	unsigned int i;
	int num;
	
  IO0DIR |= 0x1E000000; // to set P0.25 to P0.28 as o/ps 	
	for(i=0;i<2;i++){
	 while(1){
	//check for keypress in row0,make row0 '0',row1=row2=row3='1'
		rowsel=0;IO0SET = 0X7E000000;IO0CLR = 1 << 25;
		if(COL0==0){colsel=0;break;};if(COL1==0){colsel=1;break;};
		if(COL2==0){colsel=2;break;};
	//check for keypress in row1,make row1 '0'
		rowsel=1;IO0SET = 0X7E000000;IO0CLR = 1 << 26;
		if(COL0==0){colsel=0;break;};if(COL1==0){colsel=1;break;};
		if(COL2==0){colsel=2;break;};
	//check for keypress in row2,make row2 '0'
		rowsel=2;IO0SET = 0X7E000000;IO0CLR = 1 << 27;//make row2 '0'
		if(COL0==0){colsel=0;break;};if(COL1==0){colsel=1;break;};
		if(COL2==0){colsel=2;break;};
	//check for keypress in row3,make row3 '0'
		rowsel=3;IO0SET = 0X7E000000;IO0CLR = 1 << 28;//make row3 '0'
		if(COL0==0){colsel=0;break;};if(COL1==0){colsel=1;break;};
		if(COL2==0){colsel=2;break;};
	  };
	delay_ms_(50);//allow for key debouncing
	while(COL0==0 || COL1==0 || COL2==0);//wait for key release
	delay_ms_(50);//allow for key debouncing
  IO0SET |= 0X1E000000; //disable all the rows
//send to serial port(check on the terminal)
	IO0SET = 0X7E000000;IO0CLR = lookup_table[rowsel][colsel] << 25;
  //U0THR = lookup_table[rowsel][colsel];
		msg1[i] = lookup_table[rowsel][colsel];
	}
	msg1[i] = '\0';
	//printf("%s\n",msg1);
	num = atoi(msg1);
	return num;

}

void delay_ms_(unsigned int j)
{
  unsigned int x,i;
	for(i=0;i<j;i++)
	{
    for(x=0; x<10000; x++);    
	}
}


