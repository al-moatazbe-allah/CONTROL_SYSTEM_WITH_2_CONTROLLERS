/*
 * SERVO.c
 *
 * Created: 8/30/2023 1:47:27 AM
 *  Author: dell
 */ 
#include "SERVO.h"

void SERVO_INIT()
{
	DIO_set_bit_direction('d',5,1);
}
void MOVE_SERVO(float degree)
{
	float duty_cycle=0;
	if (degree>0)
	{
		duty_cycle=7.5+(degree/90.0)*2.5;
	}
	else if(degree<=0)
	{
		duty_cycle=7.5-(degree/90.0)*2.5;
	}
	T1_FPWM_ICRT(duty_cycle);
}