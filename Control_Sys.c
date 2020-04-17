#include <lpc214x.h>

#define RELAY_ON (IO0SET = 1 << 11)
#define RELAY_OFF (IO0CLR = 1 << 11)

void runDCMotor(unsigned int direction,unsigned int speed)
{
	//P0.28 pin is used to control direction of motor
	if(direction==1)
		IO0CLR = 1U << 28;
	else
		IO0SET = 1U << 28;
	
	// assume it is connected to PWM6 (P0.9)
	PINSEL0 |= 2U << 18; //0X00000008;   // 10
	PWMMR0 = 10000;
	PWMMR1 = 10000;
	PWMMR6 = 10000 * speed / 100;
	PWMMCR = 0X02;
	PWMPCR = 1u << 14 | 1<<9;//0X00000800;//
	PWMTCR = 0X09; //1001;
	PWMLER = 0X43; //01000001	
}

void light_action(unsigned int light_i)
{
	if(light_i > 300) 
		RELAY_ON;
	else
		RELAY_OFF;
}

void temp_action(unsigned int temp,unsigned int num)
{
	if(temp > num)
		runDCMotor(1,100);
	else if((temp > 15 ) && (temp <=num))
		runDCMotor(1,60);
	else
		runDCMotor(1,0);
}
