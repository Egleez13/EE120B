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

int main(void) {
    /* Insert DDR and PORT initializations */
	DDRA = 0x00;
	DDRB = 0x00;
	DDRC = 0xFF; 
	
	PORTA = 0x00;
	PORTB = 0x00;
	PORTC = 0x00;


	//unsigned char PenA0 = 0x00;
        //unsigned char PenA1 = 0x00;
        //unsigned char PenA2 = 0x00;
        //unsigned char PenA3 = 0x00;
        //unsigned char PenA4 = 0x00;
        //unsigned char PenA5 = 0x00;
        //unsigned char PenA6 = 0x00;
        //unsigned char PenA7 = 0x00;

	unsigned short counter = 0x00;	

    /* Insert your solution below */
    while (1) {
	counter = 0;
	counter = 
	


    }
    return 1;
}
