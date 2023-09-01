/*
 * timers.c
 *
 * Created: 8/21/2023 4:01:54 PM
 *  Author: dell
 */
#include "timers.h" 
void T0_NM()
{
   TCCR0=(1<<CS00)|(1<<CS02);
}
void T0_CTC(u_int8 compare)
{	
	SET_BIT(MYDDRB,3);
	OCR0=compare;
	TCCR0=(1<<CS00)|(1<<CS02)|(1<<WGM01)|(1<<COM00);
}
void T0_FPWMNI(float duty_cycle)
{
	SET_BIT(MYDDRB,3);
	OCR0=((256)*duty_cycle/100);
	TCCR0=(1<<CS00)|(1<<CS02)|(1<<WGM00)|(1<<WGM01)|(1<<COM01);
}
void T0_PCPWMNI(float duty_cycle)
{
	SET_BIT(MYDDRB,3); 
	OCR0=((510)*duty_cycle/100)/2;
	TCCR0=(1<<CS00)|(1<<CS02)|(1<<WGM00)|(1<<COM01);
}
void T0_FPWMI(float duty_cycle)
{
	SET_BIT(MYDDRB,3);
	OCR0=(255-(duty_cycle*255)/100);
	TCCR0=(1<<CS00)|(1<<CS02)|(1<<WGM00)|(1<<WGM01)|(1<<COM01)|(1<<COM00);
}
void T0_PCPWMI(float duty_cycle)
{
	SET_BIT(MYDDRB,3);
	OCR0=(510-(duty_cycle*510)/100)/2;
	TCCR0=(1<<CS00)|(1<<CS02)|(1<<WGM00)|(1<<COM01)|(1<<COM00);
}


void T1_NM()
{
	
		
}
void T1A_CTC(u_int16 compare)
{
	OCR1AH=(u_int8)(compare>>8);
	OCR1AL=(u_int8)compare;
	TCNT1L=0;
	TCNT1H=0;
	TCCR1A=(1<<FOC1A);
	TCCR1B=(1<<WGM12)|(1<<CS12);
	SET_BIT(TIMSK,OCIE1A);
}
void T1_FPWM_ICRT(float duty_cycle)
{
	u_int16 *OCR1A=(u_int16*)0x4A;
	u_int16 *ICR1=(u_int16*)0x46;
	TCCR1B|=(1<<WGM13)|(1<<WGM12);
	TCCR1A|=(1<<WGM11);
	*ICR1=(19999);
	*OCR1A=(duty_cycle/100)*(float)19999;
	SET_BIT(TCCR1B,CS11);
	SET_BIT(TCCR1A,COM1A1);
}
void T1_PCPWM(float duty_cycle)
{
	
}
void T2_NM_DF_OSC()
{
	SET_BIT(ASSR,AS2);
	TCCR2=(1<<CS20)|(1<<CS22);
	sei();
	SET_BIT(TIMSK,TOIE2);
}
void T2_CTC(u_int8 compare)
{
	SET_BIT(MYDDRD,7);
	OCR0=compare;
	TCCR2=(1<<CS20)|(1<<CS22)|(1<<WGM21)|(1<<COM20);
}
void T2_FPWMNI(float duty_cycle)
{
	SET_BIT(MYDDRD,7);
	OCR0=((256)*duty_cycle/100);
	TCCR2=(1<<CS20)|(1<<CS22)|(1<<WGM20)|(1<<WGM21)|(1<<COM21);
}
void T2_PCPWMNI(float duty_cycle)
{
	SET_BIT(MYDDRD,7);
	OCR0=((510)*duty_cycle/100)/2;
	TCCR2=(1<<CS20)|(1<<CS22)|(1<<WGM20)|(1<<COM21);
}
void T2_FPWMI(float duty_cycle)
{
	SET_BIT(MYDDRD,7);
	OCR0=(255-(duty_cycle*255)/100);
	TCCR2=(1<<CS20)|(1<<CS22)|(1<<WGM20)|(1<<WGM21)|(1<<COM21)|(1<<COM20);
}
void T2_PCPWMI(float duty_cycle)
{
	SET_BIT(MYDDRD,7);
	OCR0=(510-(duty_cycle*510)/100)/2;
	TCCR2=(1<<CS20)|(1<<CS22)|(1<<WGM20)|(1<<COM21)|(1<<COM20);
}

void ICU()
{
	
}
void WDT()
{
	//reset the controller as fast as we can
	CLR_BIT(WDTCR,WDTOE);
	SET_BIT(WDTCR,WDE);
	CLR_BIT(WDTCR,WDP0);
	CLR_BIT(WDTCR,WDP1);
	CLR_BIT(WDTCR,WDP2);
}
void WDT_STOP()
{
	SET_BIT(WDTCR,WDTOE);
	SET_BIT(WDTCR,WDE);
	CLR_BIT(WDTCR,WDE);
}
