#include <avr/io.h>
#include <avr/interrupt.h>

#define ACCELERATION 16 //can be increased for faster ramp up
#define MAX_DELAY 100
#define MIN_DELAY 8
#define RAMP (MAX_DELAY - MIN_DELAY)/ACCELERATION
#define FORWARD 1
#define REVERSE -1
#define ROT 200 //steps per rotation

const uint8_t phases[] = {
							0x01,
							0x02,
							0x04,
							0x08
						}
						
volatile uint8_t currentPhase = 0;
volatile int8_t direction = FORWARD;
volatile uint16_t stepCount = 0;

void initTimer(void)
{
	TCCR0A |= (1<<WGM01);
	TCCR0B |= (1<<CS00)|(1<<CS02); //set prescalar to 1024
	OCR0A = MAX_DELAY;	//default to slowest speed
	sei();
}

ISR (TIMER0_COMPA_vect)
{
	currentPhase += direction;
	currentPhase &= 0x07;
	PORTB = phases[currentPhase];
	stepCount++;
}

void step(uint16_t numSteps, uint8_t delay)
{
	OCR0A = delay;		//set output compare register to delay
	stepCount = 0;
	TIMSK0 |= (1<<OCIE0A);  //enable Timer0 interrupt
	while (!(stepCount == numSteps){;}  //wait
	TIMSK0 &= ~(1<<OCIE0A); //disable interrupt
}

void trapeziod(int16_t numSteps)
{
	uint8_t delay = MAX_DELAY;
	uint16_t stepsTaken = 0;
	
										// set direction
	
	if (numSteps > 0){
		direction = FORWARD;
	}
	else {
		direction = REVERSE;
		numSteps = -numSteps;
	}
	
										//  determine if enough steps for trapezoidal profile
	if (numSteps > (RAMP*2)){
										//accelerate
		while (stepsTaken < RAMP){
			step(1,delay);
			delay -= ACCELERATION;
			stepsTaken++;
		}

		delay = MIN_DELAY;
		step((numSteps - 2*RAMP),delay);		//CRUISE
		stepsTaken += (numSteps -2*RAMP);
		
		while (stepsTaken < numSteps){
			step(1,delay);
			delay += ACCELERATION;
			stepsTaken++;
		}
	}
		
	else {
		while (stepsTaken <= numSteps/2){
			step(1,delay);
			delay -= ACCELERATION;			//decelerate
			stepsTaken++;
		}
		delay += ACCELERATION;
		while (stepsTaken < numSteps){
			step(1,delay);
			delay += ACCELERATION;
			stepsTaken++;
		}
	}
}