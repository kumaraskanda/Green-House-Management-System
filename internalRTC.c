/*
Data Acquisition System / Green House Monitoring
Used LDR,LM35,Relay,LED,LCD,Internal RTC,GPIO,PWM,Timer0 & Timer1,UART0
*/

#include <lpc214x.h>
#include <stdio.h>
#include "LCD.H"
#include "7seg.h"
#include "keyboard.h"
#define SW1 (IOPIN1 & 1<<21)
#define SW2 (IOPIN1 & 1<<22)
#define uint16_t unsigned int
typedef struct
{
	unsigned char sec;
  unsigned char min;
  unsigned char hour;
  unsigned char weekDay;
  unsigned char date;
  unsigned char month;
  unsigned int year;  
}rtc_t;

void SystemInit(void);//initialize CCLK and PCLK
void Board_Init(void);//initialize GPIO
void uart_init(void); 
void RTC_Init(void);
void timer1_Init(void);// generates interrupt every 1sec
void delay(int cnt);
void RTC_SetDateTime(rtc_t *rtc);
void RTC_GetDateTime(rtc_t *rtc);
void runDCMotor(unsigned int direction,unsigned int speed);
unsigned int adc(int no,int ch);// to read LDR(AD1.3),LM35(AD1.5)
void serialPrint(unsigned val);//print int on serialport
void serialPrintStr(char * buf);//print string on serialport
void temp_action(unsigned int temp,unsigned int num);
void light_action(unsigned int light);


rtc_t rtc; // declare a variable to store date,time



int main() 
{
    unsigned char msg[100];
	  unsigned int light_i,temp,temp1,num;
		unsigned int a[2],i=0,b[2];
  
 // initialize the peripherals & the board GPIO
	
    Board_Init();
    SystemInit();
    uart_init();
	  RTC_Init();
	  timer1_Init(); 
	  LCD_Reset();
		LCD_Init();

	// set date & time to 7thApril 2020,10:00:00am 
	
		rtc.hour = 17;rtc.min =  00;rtc.sec =  00;//10:00:00am
    rtc.date = 14;rtc.month = 04;rtc.year = 2020;//07th April 2020
    RTC_SetDateTime(&rtc);  // comment this line after first use
		printf("Enter the temperature at which the fan should be rotating at full speed(in Centigrade)\n");
		num = key_select();
		printf("The set temp is: %d\n",num);
		delay(2000);
		a[0]=a[1]=0;
		b[0]=b[1]=0;
	  while(1)
    {
      RTC_GetDateTime(&rtc);//get current date & time stamp
			printf("time:%2d:%2d:%2d  Date:%2d/%2d/%4d\n",rtc.hour,rtc.min,rtc.sec,rtc.date,rtc.month,rtc.year);
			sprintf((char *)msg,"time:%2d:%2d:%2d  Date:%2d/%2d/%2d \x0d\xa",(uint16_t)rtc.hour,(uint16_t)rtc.min,(uint16_t)rtc.sec,(uint16_t)rtc.date,(uint16_t)rtc.month,(uint16_t)rtc.year);
			// use the time stored in the variable rtc for date & time stamping
			LCD_CmdWrite(0x80); LCD_DisplayString((char*)msg);
			delay(2000);
			
		  //Light Measurement
			light_i = adc(1,3);//readLDR();
			//FORMULA OR LOOK UP TABLE
			sprintf((char *)msg,"light:%4d \x0d\xa",(uint16_t)light_i);
			printf("light is : %d\n",light_i);
			if(light_i > b[0] || light_i > b[1])
				b[i%2] = light_i;
			LCD_CmdWrite(0xC0); LCD_DisplayString((char*)msg);
			delay(2000);
			
			//Temperature Measurement
			temp    = adc(1,4);//readTemp();
			temp1 = (temp*5*100)/10240;				//conversion to Celsius
			if(temp1 > a[0] || temp1 > a[1])
				a[i%2] = temp1;
			printf("temp is : %d C\n",temp1);
			sprintf((char *)msg,"temperature:%4d \x0d\xa",(uint16_t)temp1);
			LCD_CmdWrite(0x94); LCD_DisplayString((char*)msg);
			delay(2000);
							
			// to control Relay on/off based on Light intensity
			light_action(light_i);
			
			// to control DC Motor Speed based on Temperature
			temp_action(temp1,num);
			delay(2000);
			
			if(i>2){
				//printing in uart for display and debugging for now
				//the same can be sent to 7seg with hardware available
				//use the function displayint for displaying on 7 segment display
				printf("Press Switch 1 - Display Max temp, Switch 2 - Display Max light intensity\n");
				delay(2000);
				if(!SW1){
					if(a[0] > a[1]){
							printf("max temp is : %d\n",a[0]);
							delay(2000);
				}
					else{
							printf("max temp is : %d\n",a[1]);
							delay(2000);
					}
				}
				if(!SW2){
					if(b[0] > b[1]){
							printf("max light is : %d\n",b[0]);
							delay(2000);
				}
					else{
							printf("max light is : %d\n",b[1]);
							delay(2000);
				}
				}
			}
			i++;
			delay(2000);
			
    }
}







