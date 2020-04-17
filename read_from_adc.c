#include <lpc214x.h>

unsigned int adc(int no,int ch)
{
  // adc(1,4) for temp sensor LM35, digital value will increase as temp increases
	// adc(1,3) for LDR - digival value will reduce as the light increases
	// adc(1,2) for trimpot - digital value changes as the pot rotation
	unsigned int val;
	PINSEL0 |=  0x0F300000;   
	/* Select the P0_13 AD1.4 for ADC function */
  /* Select the P0_12 AD1.3 for ADC function */
	/* Select the P0_10 AD1.2 for ADC function */
  switch (no)        //select adc
    {
        case 0: AD0CR   = 0x00200600 | (1<<ch); //select channel
                AD0CR  |= (1<<24) ;            //start conversion
                while ( ( AD0GDR &  ( 1U << 31 ) ) == 0);
                val = AD0GDR;
                break;
 
        case 1: AD1CR = 0x00200600  | ( 1 << ch );       //select channel
                AD1CR |=  ( 1 << 24 ) ;                              //start conversion
                while ( ( AD1GDR & (1U << 31) ) == 0);
                val = AD1GDR;
                break;
    }
    val = (val  >>  6) & 0x03FF;         // bit 6:15 is 10 bit AD value
    return  val;
}

int readTemp(void)
{	
	int adc_output;
	PINSEL1 |=  1 << 24;  //  AS AD0.2 ( "01" -> bit24,bit25 of PINSEL1)
	AD0CR= (1 << 2 | 1 << 21 | 1 << 24) ;
	/* set the Bit 21 - Make ADC operational  
     set the Bit 1  - Select the channel AD0.1, Bit0 to Bit5 – for AD0.0toAD0.5
     set 001 on bits 26 25 24 - Issue SOC signal */
	while ( (AD0GDR & (unsigned long) 1 << 31) == 0);
  // Check for the conversion to complete, by reading Bit31 of  GDR
	adc_output = (AD0GDR >> 6 ) & 0x3FF ;
	// read the Digital output from GDR, after aligning the result to LSB  (Bit0) and masking other bits to Zero
	return adc_output;
}


int readLDR(void)
{
	int adc_output;
	PINSEL1 |=  1 << 24;  // P0.28 AS AD0.1 ( "01" -> bit24,bit25 of PINSEL1)
	AD0CR= (1 << 1 | 1 << 21 | 1 << 24) ;
	/* set the Bit 21 - Make ADC operational  
     set the Bit 1  - Select the channel AD0.1, Bit0 to Bit5 – for AD0.0toAD0.5
     set 001 on bits 26 25 24 - Issue SOC signal */
	while ( (AD0GDR & (unsigned long) 1 << 31) == 0);
  // Check for the conversion to complete, by reading Bit31 of  GDR
	adc_output = (AD0GDR >> 6 ) & 0x3FF ;
	// read the Digital output from GDR, after aligning the result to LSB  (Bit0) and masking other bits to Zero
	return adc_output;
}

