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

	unsigned char PenA0 = 0x00;
	unsigned char PenA1 = 0x00;
	unsigned char PenA2 = 0x00;
	unsigned char PenA3 = 0x00;

	unsigned char counter  = 0x00;
	
	
	while (1){
	PenA0 = PINA & 0X01;
	PenA1 = PINA & 0X02;
	PenA2 = PINA & 0X04;
	PenA3 = PINA & 0X08;
	//PenA7 = PINA & 0X80;

	counter = 4;

	if (PenA0 == 0x01)
	{
		counter--;
	}

	if (PenA1 == 0x02)
        {
                counter--;
        }
	
	if (PenA2 == 0x04)
        {
                counter--;
        }
	
	if (PenA3 == 0x08)
        {
                counter--;
        }
	
	PORTC = counter;

}


		

	PORTC = counter;
	}	
	
	
		

    return 1;
}
