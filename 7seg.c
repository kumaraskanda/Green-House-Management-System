#include "7seg.h"

		
char buf[6];
void delay_milli(unsigned int j)
{
	unsigned int x,i;
	for(i=0;i<j;i++)
	{
	for(x=0;x<10000;x++);
	}
}
unsigned char dot()
{
	
	switch(buf[2])
	{
		case '0': return 0x40;
		case '1': return 0x79;
		case '2': return 0x24;
		case '3': return 0x30;
		case '4': return 0x19;
		case '5': return 0x12;
		case '6': return 0x02;
		case '7': return 0x78;
		case '8': return 0x00;
		case '9': return 0x10;
	}
	return 0xff;
}	
	
unsigned char get(unsigned char alpha)
{
	switch(alpha)
	{
		case '0': return 0xc0;
		case '1': return 0xf9;
		case '2': return 0xa4;
		case '3': return 0xb0;
		case '4': return 0x99;
		case '5': return 0x92;
		case '6': return 0x82;
		case '7': return 0xf8;
		case '8': return 0x80;
		case '9': return 0x90;
		case 'f': return 0x8e;
		case 'i': return 0xf9;
		case 'r': return 0xce;
		case 'e': return 0x86;
		case 'h': return 0x89;
		case 'l': return 0xc7;
		case 'p': return 0x8c;
		case ' ': return 0xff;
		case '.': return dot();
		default:break;
	}
	return 0xff;
}
void seg(char *buf)
{
	unsigned char i,j;
	unsigned char segment,temp=0;
	
	for(i=0;i<5;i++)
	{
		segment=get(*(buf+i));
		for(j=0;j<8;j++)
		{
			temp=segment &0x80;
			if(temp==0x80)
				IOSET0|=1<<19;
			else
				IOCLR0|=1<<19;
			
			IOSET0|=1<<20;
			delay_milli(1);
			IOCLR0|=1<<20;
			segment=segment<<1;
		}
	}
			IOSET0|=1<<30;
			delay_milli(1);
			IOCLR0|=1<<30;
			return;
		}

void seg1(char *buf)
{
	unsigned char i,j;
	unsigned char segment,temp=0;
	
	for(i=0;i<6;i++)
	{
		if(i==2)
		{
			segment=dot();
			i+=1;
		}
		else
			segment =get(*(buf+i));
			
		for(j=0;j<8;j++)
		{
			temp=segment &0x80;
			if(temp==0x80)
				IOSET0|=1<<19;
			else
				IOCLR0|=1<<19;
			
			IOSET0|=1<<20;
			delay_milli(1);
			IOCLR0|=1<<20;
			segment=segment<<1;
		}
	}
			IOSET0|=1<<30;
			delay_milli(1);
			IOCLR0|=1<<30;
			return;
		}

void dispInt(long int num)
{
	char buf[6];
	sprintf(buf,"%05lu",num);
	seg(&buf[0]);
	delay_milli(500);
}
void dispFloat(float num)
{
	long int n =num;
	float n1;
	char buf1[3];
	sprintf(buf,"%03lu",n);
	strcat(buf,".");
	n1 = num -n;
	n1 = n1*100;
	sprintf(buf1,"%02f",n1);
	strcat(buf,buf1);
	seg1(&buf[0]);
	delay_milli(500);
}


