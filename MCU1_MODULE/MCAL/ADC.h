/*
 * ADC.h
 *
 * Created: 8/31/2023 3:00:56 PM
 *  Author: dell
 */ 


#ifndef ADC_H_
#define ADC_H_
#include "STD.h"

enum SFIOR_C{PSR10=0,PSR2,PUD,ACME,RES2,ADTS2,ADTS1,ADTS0 };
enum ADMUX_C{MUX0=0,MUX1,MUX2,MUX3,MUX4,ADLAR,REF0,REF1};
enum ADCSRA_C{ADPS0=0,ADPS1,ADPS2,ADIE,ADIF,ADATE,ADSC,ADEN};	

void ADC_INIT();
u_int16 ADC_READ();

#endif /* ADC_H_ */