/*
 * ADC.c
 *
 * Created: 8/31/2023 3:00:38 PM
 *  Author: dell
 */ 
#include "ADC.h"
#define F_CPU 8000000UL

void ADC_INIT()
{
	ADCSRA|=(1<<ADEN)|(1<<ADPS1)|(1<<ADPS2);
	ADMUX|=(1<<REF0);
}
u_int16 ADC_READ()
{
	 u_int16 read_val;
	 
	 SET_BIT(ADCSRA,ADSC);
	 while(IS_BIT_CLR(ADCSRA,ADIF));//stay in your position till ADIF become 1
	 SET_BIT(ADCSRA,ADIF); // clear ADIF
	 read_val=(ADCL);
	 read_val|=(ADCH<<8);
	 return read_val ;
	
}
