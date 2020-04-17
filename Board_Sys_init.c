#include <lpc214x.h>

void SystemInit(void)
{
   PLL0CON = 0x01; 
   PLL0CFG = 0x24; 
   PLL0FEED = 0xAA; 
   PLL0FEED = 0x55; 
   while( !( PLL0STAT & 0x00000400 ))
   { ; }
   PLL0CON = 0x03;
   PLL0FEED = 0xAA;  // lock the PLL registers after setting the required PLL
   PLL0FEED = 0x55;
   VPBDIV = 0x01;      // PCLK is same as CCLK i.e 60Mhz  
}

void delay(int cnt)
{
	T0MR0 = 1000;//14926; // some arbitrary count for delay
	T0MCR = 0x0004; // set Tiimer 0 Stop after Match
	while(cnt--)
	{
		T0TC = 0X00;
	  T0TCR = 1; // start the timer (enbale)
		while(!(T0TC == T0MR0)){};// wait for the match
	  T0TCR = 2;// stop the timer		
	}
}


void Board_Init(void)
{
	
	IO0DIR |= 1 << 11; // RELAY IS CONNECTED TO P0.21
	IO0DIR |= 1U << 31 | 0x00FF0000 ; // to set P0.16 to P0.23 as o/ps ,
  IO1DIR |= 1U << 25;	              // to set P1.25 as o/p used for EN
                                    // make D7 Led (P0.31) on off for testing		
}
