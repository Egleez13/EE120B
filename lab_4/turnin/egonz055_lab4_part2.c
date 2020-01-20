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

enum STATE_MACHINES2 {start, wait_state, increment_ON, increment_OFF, decrement_ON, decrement_OFF, reset} state;

void stateMachines() 
{
	switch (state) 
	{
		case start:
			state = wait_state;
			break;

		case wait_state:
                        if (PORTA == 0x03) 
			{	state = reset;
			}
			else if (PORTA = 0x02) 
			{
				state = decrement_ON;
			}
			else if (PORTA = 0X01) 
			{
				state = increment_ON;
			}
			else if 
			{
				state = wait_state;
			}
                        break;
				
		case increment_OFF:
                        if (PORTA == 0x00) 
			{
				state = wait_state;
			}
                        else if (PORTA == 0x03) 
			{
				state = reset;
			}
                        else 
			{
				state = increment_OFF;
			}
                        break;

		case decrement_OFF:
			if (PORTA == 0x00) 
			{
				state = wait_state;
			}
			else if (PORTA = 0x03) 
			{
				state = reset;
			}
			else 
			{
				state = decrement_OFF;
			}
                        break;

		case increment_ON:
                        if (PORTA == 0x03) 
			{
				state = reset;
			}
                        else 
			{
				state = increment_OFF;
			}
                        break;


		case decrement_ON:
			if (PORTA == 0x03) 
			{
				state = rest;
			}
			else 
			{
				state = decrement_OFF;
			}
			break;

		case reset: 
			if (PORTA == 0x03) 
			{
				state = reset;
			}
			else 
			{
				state = wait_state;
			}
			break;

		default:
			//		 
			break;
	}

	switch (state)
	{
		case start:
		
			break;

		case wait_state:

			break;

		case increment_OFF:

                        break;
		
		case decrement_OFF:

                        break;

		case increment_ON:
                        if (PORTC < 9) 
			{
				PORTC = PORTC + 1;
			}
                        break;

		case decrement_ON:
			if (PORTC > 0) 
			{
				PORTC = PORTC - 1;
			}
			break;

		case reset:
			PORTC = 0;
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
