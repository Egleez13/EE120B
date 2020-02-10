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

enum states {start, wait, initiate, hold} state; //start idle run wait

unsigned char var1 = 0x00; //tmpa
unsigned char input1 = 0x00; //toggle
double frequencies[] = {261.63, 293.66, 329.63, 349.23, 392, 440, 493.88, 523.25};
unsigned char frequency_index = 0; //freq_at

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
			if (input1) 
			{
				state = initiate;
			}
			else {
				state = wait;
			}
		break;

		case initiate:
			if (var1 == 0x04) 
			{
				input1 = 0;
				state = hold;
			}
		break;
		
		case hold:
		
		break;

		default:
			state = wait;
		break;
}

	switch (state) {
		case start:
	
		break;
	
		case wait:
			if (var1 == 0x04)
			{
				input1 = 1;
				state = hold;
			}
			set_PWM(0);
		break;

		case initiate:
			if (var1 == 0x04) 
			{
				input1 = 0;
				state = hold;
			}
			else if (var1 == 0x02 && frequency_index < 7) 
			{
				frequency_index = frequency_index + 1;
				state = hold;
			}
			else if (var1 == 0x01 && frequency_index > 0) 
			{
				frequency_index = frequency_index - 1;
				state = hold;
			}
			set_PWM(frequencies[frequency_index]);
		break;

		case hold:
			if (var1 == 0x00) {
				if (input1) {
					state = initiate;
				}
				else 
				{
					state = wait;
				}
			}
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
