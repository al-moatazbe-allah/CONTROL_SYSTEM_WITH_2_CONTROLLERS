/*
 * EEPROM.h
 *
 * Created: 8/20/2023 1:04:45 PM
 *  Author: dell
 */ 


#ifndef EEPROM_H_
#define EEPROM_H_
#include "STD.h"
#include "INT.h"
#define EERE 0
#define EEWE 1
#define	EEMWE 2
#define EERIE 3
void EEPROM_SET_ADD(u_int16 add);
void EEPROM_WRITE(u_int8 data ,u_int16 add);
u_int8 EEPROM_READ(u_int16 add);
#endif /* EEPROM_H_ */