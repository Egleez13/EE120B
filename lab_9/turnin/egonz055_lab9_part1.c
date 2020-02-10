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

enum states {start, wait, note_C, note_D, note_E} state;

unsigned char var1 = 0x00;

void set_PWM(double freuqeuncy) {
	static double current_frequency;
		if (frequency != current_frequency) {
			if (!frequency) {
				TCCR3B &= 0x08;
				}
			else {
				TCCR3B |= 0x03;
			}
		if (frequency < 0.954) 
		{	
			OCR3A = 0xFFFF;
		}
		else if (frequency > 31250)
		{
			OCR3A = 0x0000;
		}
		else {
			OCR3A = (short) (8000000 / (128 * frequency)) - 1;}
		TCNT3 = 0;
		current_frequency = frequency;
		}
	}

void PWM_on() {
	TCCR3A = (1 << COM3A0);
	TCCR3B = (1 << WGM32) | (1 << CS31) | (1 << CS30);
	set_PWM(0);
}

void PWM_off() {
	TCCR3A = 0x00;
	TCCR3B = 0x00;
}

void tick() {
	switch (state) {
		case start:
			state = wait;
		break;

		case wait:
			if (var1 == 0x04) 
			{
				state = note_C;
			}
			else if (var1 == 0x02) 
			{
				state = note_D;
			}
			else if (var1 == 0x01)
			{
				state = state_E;
			}
			else {
				state = wait;
			}
		break;

		case note_C:
			if (var == 0x04)
			{
				state = note_C;
			}
			else {
				state = wait;
			}	
		break;
		
		case note_D:
			if (var == 0x02)
                        {
                                state = note_D;
                        }
                        else {
                                state = wait;
                        }
                break;

		case note_E:
			if (var == 0x01)
                        {
                                state = note_E;
                        }
                        else {
                                state = wait;
                        }
		break;
	
		default:
			state = wait;
		break;
}

	switch (state) {
		case start:
	
		break;
	
		case wait:
			set_PWM(0);
		break;

		case note_C:
			set_PWM(261.63);
		break;

		case note_D:
			set_PWM(293.66);
		break;

		case note_E:
			set_PWM(329.63);
		break;		

		default:
			set_PWM(0);
		break;
	}		
}
	
int main(void) {
    /* Insert DDR and PORT initializations */
	DDRA = 0x00;
	PORTA = 0xFF;
	
	DDRB = 0x08;
	PORTB = 0x00;

	PWM_on();
    /* Insert your solution below */
    while (1) {
	var1 = ~PINA & 0x07;
	tick();
    }
    return 1;
}
