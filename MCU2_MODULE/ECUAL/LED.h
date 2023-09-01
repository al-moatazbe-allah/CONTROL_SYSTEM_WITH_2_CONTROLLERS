/*
 * LED.h
 *
 * Created: 8/13/2023 2:08:22 PM
 *  Author: dell
 */ 


#ifndef LED_H_
#define LED_H_
#include "DIO.h"
void set_led(u_int8 port, u_int8 bit);
void on_led(u_int8 port,u_int8 bit);
void off_led(u_int8 port ,u_int8 bit);
void toggle_led(u_int8 port,u_int8 bit);
#endif /* LED_H_ */