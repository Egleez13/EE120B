/*	Author: egonz055
 *  Partner(s) Name: 
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

int main(void) {
    /* Insert DDR and PORT initializations */
	DDRA = 0x00;
	DDRB = 0xFF; 
	
	PORTA = 0xFF;
	PORTB = 0X00;

	unsigned char counter  = 0x00;
	
	
	while (1){
	counter = 4;

	if (PINA & 0x01)
	{
		counter--;
	}

	if (PINA & 0x02)
        {
                counter--;
        }
	
	if (PINA & 0x04)
        {
                counter--;
        }
	
	if (PINA & 0x08)
        {
                counter--;
        }
	
	if (counter == 0)
	{
		counter = counter | 0x80;
	}
	
	PORTC = counter;
	}
	
		

    return 1;
}
