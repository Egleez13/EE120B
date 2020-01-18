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
	DDRC = 0xFF; 
	
	PORTA = 0xFF;
	PORTC = 0X00;

	unsigned char temp_var1 = 0x00;
	
	
	while (1){
		
	temp_var1 = PORTA; 

	if (temp_var1 == 0x01)
	{
		PORTB = 0x01;
	}
	
	else 
	{
		PORTB = 0x00;
	}

	}
}

	return 1;
}
