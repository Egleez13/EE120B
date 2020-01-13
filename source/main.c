/*	Author: egonz055
 *  Partner(s) Name: 
 *
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

//PA0 = garage door sensor (INPUT)
//PA1 = light sensor (INPUT)
//PB0 = LED (OUTPUT)

int main(void) {
    /* Insert DDR and PORT initializations */
	DDRA = 0x00;
	PORTA = 0xFF;

	DDRB = 0xFF;
	PORTB = 0x00;

	unsigned char temporaryValA = 0x00; //Hold A value
	unsigned char temporaryValB = 0x00; //Hold B value


    /* Insert your solution below */
	while(1) {
	temporaryValA = PORTA;
	
	if (PORTA = 0x00) {
	

    }
    return 1;
}
