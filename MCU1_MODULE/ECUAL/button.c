/*
 * button.c
 *
 * Created: 8/13/2023 2:57:24 PM
 *  Author: dell
 */
#include "button.h"

 
void button_set(u_int8 port,u_int8 bit){
	DIO_set_bit_direction(port,bit,0);
}
void button_pull_up(u_int8 port, u_int8 bit){
	DIO_Set_Bit(port,bit);
}
void button_puul_down(u_int8 port , u_int8 bit){
	DIO_CLR_Bit(port,bit);
}
u_int8 button_read(u_int8 port,u_int8 bit){
	u_int8 value;
	value=DIO_get_bit(port,bit);
	return value;
}
