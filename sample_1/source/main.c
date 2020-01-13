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
DDRA=0x00;
DDRB=0xFF;
PINA=0xFF;
PORTB=0x00;
unsigned char g_sensorA0 = 0x00; // B
unsigned char l_sensorA1 = 0x00; // A

    /* Insert your solution below */
    while (1) {
	if (g_sensorA0 == 0x00 && l_sensorA1 == 0x01)
	{
		PORTB = 0x01;
	}

	else {
		PORTB = 0x00;
	} 
    }
    return 1;
}
