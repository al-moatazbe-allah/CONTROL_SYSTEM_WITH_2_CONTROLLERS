/*
 * main.c
 *
 * Created: 8/30/2023 7:13:12 PM
 *  Author: dell
 */ 


#include "UART.h"
#include "DCMOTOR.h"
#include "DELAYM.h"
#include "ADC.h"
#include "INT.h"
#include "EEPROM.h"
#define E2U 0x30
#define F_CPU 8000000UL
u_int16 analog_read=0;
u_int16 emergency_flag=0;
u_int8 interrupt_flag=0;
u_int8 temp=0;
float duty_cycle=0;
u_int8 abnormal_flag=0;
u_int8 motor_speed;
u_int8 temperature_sensor_read();
enum states{NORM_MODE ='N',NORM_YELLOW ='Y',NORM_RED_WORK='R', NORM_RED_NOT_WORK='I', EMERGENCY='E',ABNORM='G'};
int main(void)
{	delay_ms(4);
	sei();
	EXTERNAL_1();
	T1A_CTC(15600);
	DC_INIT();
	ADC_INIT();
	UART_INIT(9600);
	u_int8 e2p_ret=EEPROM_READ(0x32);
	EEPROM_WRITE(e2p_ret,0x33);
	if (e2p_ret==ABNORM)
	{
		DC_MOVE(100,'f');
		UART_SEN(ABNORM);
		EEPROM_WRITE(0xff,0x32);
		delay_ms(5000);
	}
    while(1)
    {
		temp=temperature_sensor_read();
		if (temp<=20)
		{
			DC_MOVE(0,'F');
			UART_SEN(NORM_MODE);
			EEPROM_WRITE(NORM_MODE,E2U);
		}
		else if (temp>20 && temp<40)
		{
			duty_cycle=((temp-20)/20.0)*100;
			DC_MOVE(duty_cycle,'F');
			UART_SEN(NORM_YELLOW);
			EEPROM_WRITE(NORM_YELLOW,E2U);
			
		}
		else if (temp>=40 &&temp<=50 && interrupt_flag==0)
		{
		DC_MOVE(100,'F');
		UART_SEN(NORM_RED_WORK);
		EEPROM_WRITE(NORM_RED_WORK,E2U);	
		}
		else if (temp>=40 &&temp<=50 && interrupt_flag==1)
		{
				DC_MOVE(100,'F');
				UART_SEN(NORM_RED_NOT_WORK);
				EEPROM_WRITE(NORM_RED_NOT_WORK,E2U);
		}
		else if (temp>50 &&abnormal_flag==0 )
		{
			DC_MOVE(100,'F');
			UART_SEN(EMERGENCY);
			EEPROM_WRITE(EMERGENCY,E2U);
		}
		else if (temp>50 &&abnormal_flag==1 )
		{
			DC_MOVE(100,'F');
			UART_SEN(ABNORM);
			EEPROM_WRITE(ABNORM,0x32);		
			WDT();
		}
  
    }
	motor_speed=UART_REV();
}
ISR(T1_CMP)
{
	if (temp>50)
	{
		emergency_flag++;
	}
	else if (temp<=50)
	{
		emergency_flag=0;
		abnormal_flag=0;
	}
	if (emergency_flag>=14)
	{
		abnormal_flag=1;
	}
}
ISR(ext_0)
{
	if (temp>40 &&temp<50)
	{
		interrupt_flag=1;
	}
}
u_int8 temperature_sensor_read()
{
	
	     u_int8 temp=ADC_READ()*0.25;
		 return temp;
} 