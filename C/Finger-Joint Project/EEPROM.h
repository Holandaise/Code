/*

   Written by Adam Montgomery 5/7/15
   Custom EEPROM library for internal 
   EEPROM on AVR
   No need to init_EEPROM to read data

*/

#include <avr/io.h>

#define WRITE (1<<EEPM1)
#define ERASE (1<<EEPM0)
#define ERSWR ~(1<<EEPM1)|~(1<<EEPM0)

void init_EEPROM(unsigned char);
uint8_t read_EEPROM(char,char);
void write_EEPROM(char, char);

void init_EEPROM(unsigned char mode)
{
	switch(mode)
	{
		case 0:
		EECR &= ~(1<<EEPM1)|~(1<<EEPM0);	//Erase and write
		break;
		case 1:
		EECR |= 1<<EEPM0;					//Erase
		break;
		case 2:
		EECR |= 1<<EEPM1;					//Write
		break;
		default:
		EECR |= 1<<EEPM1;					//DEFAULT to write
	}
}

uint8_t read_EEPROM(char addr)
{
	while (EECR & (1<<EEPE));
	EEARL = addr;
	EECR |= 1<<EERE;
	return EEDR;
}

void write_EEPROM(char addr, unsigned char data)
{
	while (EECR & (1<<EEPE));			//wait for previous write to complete
	
	
	EEARL = addr;						//set address in address register
	
	EEDR = data;						//put data in data register
	
	EECR |= (1<<EEMPE);		            //Master write enable
	EECR |= (1<<EEPE);					//Write enable
}