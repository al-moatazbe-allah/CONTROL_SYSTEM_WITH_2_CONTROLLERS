/*
 * button.h
 *
 * Created: 8/13/2023 2:56:57 PM
 *  Author: dell
 */ 


#ifndef BUTTON_H_
#define BUTTON_H_
#include "DIO.h"

void button_set(u_int8 port,u_int8 bit);
void button_pull_up(u_int8 port, u_int8 bit);
void button_puul_down(u_int8 port , u_int8 bit);
u_int8 button_read(u_int8 port,u_int8 bit);
#endif /* BUTTON_H_ */