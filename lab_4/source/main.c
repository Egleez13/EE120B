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

enum STATE_MACHINES{start, PB0_push, PB1_push, PB0_release, PB1_release} state;

void stateMachines() 
{
	switch (state) 
	{
		case start:
			state = PB0_release;
			break;

		case PB0_push:
                        state = (PORTA == 0x00) ? PB0_release : PB0_push;
                        break;
		
		case PB1_push:
                        state = (PORTA == 0x00) ? PB1_release : PB1_push;
                        break;

		case PB0_release:
			state = (PORTA == 0X01) ? PB1_push : PB0_release;
			break;

		case PB1_release: 
			state = (PORTA == 0x01) ? PB0_push : PB1_release;
			break;

		default:
		//		 
		break;
	}

	switch (state)
	{
		case start:
			PORTB = 0x00;
		
		case PB0_push:
                        PORTB = 0x01;
                        break;		

		case PB1_push:
                        PORTB = 0x02;
                        break;
				
		case PB0_release:
			PORTB = 0x00;
			break;
		
		case PB1_release:
			PORTB = 0x00;
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
	state = 0x00;

    /* Insert your solution below */
    while (1) {
	
	stateMachines();	
    }
    return 1;
}
