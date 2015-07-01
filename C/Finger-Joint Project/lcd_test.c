#include <avr/io.h>
#include "lcd.h"

int main(){
	initLCD();
	DDRC |= 0xFF;
	DDRD |= 0x03;
	char string[]="Hello World!";

	for(int x=0; x<11; x++){
		sendChar(string[x]);
	}
	
	while (1){
	}
	return 0;
}
