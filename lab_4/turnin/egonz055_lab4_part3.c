/*	Author: egonz055
 *  Partner(s) Name: Leo
 *	Lab Section:
 *	Assignment: Lab #  Exercise #
 *	Exercise Description: [optional - include for your own benefit]
 *
 *	I acknowledge all content contained herein, excluding template or example
 *	code, is my own original work.
 */
#include <avr/io.h>
#ifdef _SIMULATE_
#include "simAVRHeader.h"
#endif

enum STATE_MACHINES3 {start, wait_state, push_POUND, push_Y, X_state, open_state } state;

void stateMachines() 
{
	switch (state) 
	{
		case start:
			state = wait_state;
			break;

		case wait_state:
                        PORTB = 0;
			if (PORTA == 0x04) 
			{
				state = push_POUND;
			}
			else 
			{
				state = wait_state;
			}
			break;
				
		case push_POUND:
			if (PORTA == 0x00)
			{
				state = X_state;
			}
			else 
			{
				state = push_POUND;
			}
                        break;

		case X_state:
			if (PORTA == 0x02)
			{
				state = push_Y;
			}
			else if (PORTA == 0x00)
			{
				state = X_state;
			}
			else 
			{
				state = wait_state;
			}
                        break;

		case push_Y:
                        state = wait_state;
                        break;


		//case  reset: 
		//	if (PORTA == 0x03) 
		//	{
		//		state = reset;
		//	}
		//	else 
		//	{
		//		state = wait_state;
		//	}
		//	break;

		default:
			//		 
			break;
	}

	switch (state)
	{
		//case start:
		
		//	break;

		//case wait_state:

		//	break;

		//case reset:
		//	PORTC = 0;
		//	break;

		case push_Y:
			PORTB = 0x01;
			break;

		default:
			//
			break;
	}
}
	
int main(void) {
    /* Insert DDR and PORT initializations */
	DDRA = 0x00;
	DDRB = 0xFF;

	PORTA = 0xFF;
	PORTB = 0x00;

	PORTB = 0x00;
	state = 0X00;

    /* Insert your solution below */
    while (1) {
	state = start;
	stateMachines();	
    }
    return 1;
}
