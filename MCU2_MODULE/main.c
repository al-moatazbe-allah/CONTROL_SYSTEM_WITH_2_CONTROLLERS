/*
 * main.c
 *
 * Created: 8/31/2023 12:43:17 AM
 *  Author: dell
 */ 

#include "SERVO.h"
#include "UART.h"
#include "DCMOTOR.h"
#include "LED.h"
#include "DELAYM.h"
#include "ADC.h"
#include "DIO.h"
#define F_CPU 8000000UL
enum states{NORM_MODE ='N',NORM_YELLOW ='Y',NORM_RED_WORK='R',NORM_RED_NOT_WORK='I',EMERGENCY='E',ABNORM='G'};
u_int8 UART_RECIEVE=0;
u_int16 analog_read=0;
float duty_cycle=0;
#define GREEN 4
#define YELLOW 5
#define RED 6
#define BUZZER 7
int main(void)
{
		
	UART_INIT(9600);
	DC_INIT();
	SERVO_INIT();
	set_led('b',GREEN);
	set_led('b',YELLOW);
	set_led('b',RED);
	DIO_set_bit_direction('c',BUZZER,1);
	ADC_INIT();
    while(1)
    {
         UART_RECIEVE=UART_REV();
		 analog_read=ADC_READ();
		 duty_cycle=((analog_read)/1024.0)*100;
		 if(UART_RECIEVE==NORM_MODE)
		 {
			 UART_SEN(duty_cycle);
			 off_led('b',YELLOW);
			 off_led('b',RED);
			on_led('b',GREEN);
			MOVE_SERVO(0);
			DC_MOVE(duty_cycle,'F');
			DIO_CLR_Bit('c',BUZZER);
		 }
		else if(UART_RECIEVE==NORM_RED_NOT_WORK)
		{
			UART_SEN(0);
				 off_led('b',YELLOW);
				 on_led('b',RED);
				 off_led('b',GREEN);
				 MOVE_SERVO(0);
			DC_MOVE(0,'F');
			DIO_CLR_Bit('c',BUZZER);
		}
		else if(UART_RECIEVE==NORM_RED_WORK)
		{
			UART_SEN(duty_cycle);	
			off_led('b',YELLOW);
			on_led('b',RED);
			off_led('b',GREEN);
			MOVE_SERVO(0);
		DC_MOVE(duty_cycle,'F');
		DIO_CLR_Bit('c',BUZZER);
		}
		else if (UART_RECIEVE==NORM_YELLOW)
		{
			UART_SEN(duty_cycle);
				on_led('b',YELLOW);
				off_led('b',RED);
				off_led('b',GREEN);
				MOVE_SERVO(0);
				DC_MOVE(duty_cycle,'F');
				DIO_CLR_Bit('c',BUZZER);
		}
		else if(UART_RECIEVE==EMERGENCY)
		{
			UART_SEN(0);
			off_led('b',YELLOW);
			on_led('b',RED);
			off_led('b',GREEN);
			MOVE_SERVO(0);
			DC_MOVE(0,'F');
			DIO_Set_Bit('c',BUZZER);
		}
		else if(UART_RECIEVE==ABNORM)
		{
			UART_SEN(0);
				off_led('b',YELLOW);
				on_led('b',RED);
				off_led('b',GREEN);
				DC_MOVE(0,'F');
				T1_FPWM_ICRT(10);
				DIO_Set_Bit('c',BUZZER);	
		}
}
}
