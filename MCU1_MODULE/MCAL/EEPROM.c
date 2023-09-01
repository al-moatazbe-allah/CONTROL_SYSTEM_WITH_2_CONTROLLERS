/*
 * EPPROM.c
 *
 * Created: 8/20/2023 1:04:16 PM
 *  Author: dell
 */ 

#include "EEPROM.h"

void EEPROM_SET_ADD(u_int16 add)
{
	EEARL =(char)add;
	EEARH=(char)(add>>8);
}
void EEPROM_WRITE(u_int8 data,u_int16 add)
{
	EEPROM_SET_ADD(add);
EEDR=data;
sei();
SET_BIT(EECR,EEMWE);
SET_BIT(EECR,EEWE);
while(READ_BIT(EECR,EEWE));
cli();
}
u_int8 EEPROM_READ(u_int16 add)
{
	EEPROM_SET_ADD(add);
	u_int8 value;
	SET_BIT(EECR,0);
	return 	EEDR;
}