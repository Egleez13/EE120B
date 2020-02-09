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

unsigned short num1;
unsigned char num2;
unsigned char num3;

void ADC_init() {
	ADCSRA |= (1 << ADEN) | (1 << ADSC) (1 << ADATE);
}

int main(void) {
    /* Insert DDR and PORT initializations */
	DDRA = 0x00; PORTA = 0x00;
	DDRB = 0xFF; PORTB = 0X00;
	DDRD = 0X03; PORTD = 0x00;

	ADC_init();
	
    while (1) {
	num1 = ADC;
	num2 = (char)num1;
	if (num2 >= 86) { //OR 64, NOT SURE
		PORTB = 0x01;
    	}
	else {
		PORTB = 0x00;
	}
}
    return 1;
}
