/*
 * LED.c
 *
 * Created: 8/13/2023 2:07:49 PM
 *  Author: dell
 */ 
#include "LED.h"
void set_led(u_int8 port, u_int8 bit)
{
	DIO_set_bit_direction(port,bit,1);
}
void on_led(u_int8 port,u_int8 bit)
{
DIO_Set_Bit(port,bit);	
}

void off_led(u_int8 port ,u_int8 bit)
{
	DIO_CLR_Bit(port,bit);
}
void toggle_led(u_int8 port,u_int8 bit)
{
	DIO_toggle_bit(port,bit);
}