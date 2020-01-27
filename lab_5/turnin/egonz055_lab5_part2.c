#include <avr/io.h>
#ifdef _SIMULATE_
#include "simAVRHeader.h"
#endif

enum states {start, hold, add_HIGH, add_LOW, minus_HIGH, minus_LOW, reset} state;

void SM_function(){
	switch(state) {
		case start:
			state = hold;
			break;

		case hold:
			if (PORTA == 0x03)
			{
				state = reset;
			}
			else if (PORTA == 0x02) 
			{	
				state = minus_HIGH;
			}
			else if (PORTA == 0x01)
			{
				state = plus_HIGH;
			}
			else {
				state = hold;
			}
			break;

		case minus_LOW:
			if (PORTA == 0x00) 
			{
				state = hold;
			}
			else if (PORTA == 0x03) 
			{
				state = reset;
			}
			else {
				state = minus_LOW;
			}
			break;

		case minus_ON: 
			if (PORTA == 0x03)
			{
				state = reset;
			}
			else {
				state - minus_LOW;
			}
			break;

		case plus_LOW:
			if (PORTA == 0x00) 
			{
				state = hold;
			}
			else if (PORT == 0x03)
			{
				state = reset;
			}
			else {
				state - plus_LOW;
			}
			break;
		
		case plus_ON:
			if (PORTA == 0x03)
			{
				state = reset;
			}
			else {
			state = plus_ON;
			}
			break;

		case reset:
			if (PORTA == 0x03)
			{
				state = reset;
			}
			else {
				state = hold;
			}
			break;

		default:
			
			break;
}

	switch (state) {
		case hold:
		
			break;

		case minus_HIGH:
			if (PORTC > 0) 
			{
				PORTC = PORTC - 1;
			}
			break;
		
		case minus_LOW:
			PORTC = PORTC; //
			break;

		case plus_HIGH:
			if (PORTC < 9)
			{
				PORTC = PORTC + 1;
			}
			break;

		case plus_OFF:
			PORTC = PORTC; //
			break;

		case reset:
			PORTC = 0x00;
			break;
		
		default:

			break;
}
}

int main(void) {
/* Insert DDR and PORT initializations */

DDRA = 0x00;
DDRC = 0xFF;

PORTA = 0x00;
PORTC = 0x07;

state = start;

while(1) {
	SM_function();
}
return 0;
}

