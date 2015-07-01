//	"LCD.h"
#ifndef LCD
#define LCD

#define RS 0
#define RW 1
#define E  2

#define CLEAR 0x01
#define HOME  0x02

void initLCD(void);
void sendChar(char character);
void sendCom(unsigned char command);

void sendCom(unsigned char command){
	PORTC = (1<<E);
	PORTB = command;
	asm volatile ("nop");
	asm volatile ("nop");
	PORTC &= ~(1<<E);
}

void sendChar(char character){
	PORTC = (1<<E)|(1<<RS);
	PORTB = character;
	asm volatile ("nop");
	asm volatile ("nop");
	PORTC &= ~(1<<E);
}

void initLCD(){
	sendCom(0x0F);
//	sendCom(0x00);
}

#endif
