#define F_CPU 8000000UL
#include <avr/io.h>
#include <util/delay.h>

int main(){
	DDRB |= 0x01;
	while(1){
		PORTB ^= 1<<PINB0;
		_delay_ms(1000);
	}
	return 0;
}