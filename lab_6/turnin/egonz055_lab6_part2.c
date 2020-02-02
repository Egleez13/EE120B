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
#include <avr/interrupt.h>
#ifdef _SIMULATE_
#include "simAVRHeader.h"
#endif

#define A0 (~PINA&0x01)

volatile unsigned char TimerFlag = 0;
unsigned long _avr_timer_M = 1;
unsigned long _avr_timer_cntcurr = 0;



void TimerOn() {
	TCCR1B = 0x0B;
	OCR1A = 125;
	TIMSK1 = 0x02;
	TCNT1 = 0;

	_avr_timer_cntcurr = _avr_timer_M;

	SREG |= 0x80;
}

void TimerOff() {
	TCCR1B = 0x00;
}

void TimerISR() {
	TimerFlag = 1;
}

ISR(TIMER1_COMPA_vect) {
	_avr_timer_cntcurr--;
	if (_avr_timer_cntcurr == 0) {
		TimerISR();
		_avr_timer_cntcurr = _avr_timer_M;
	}
}

enum states {start, wait, stateOne, stateTwo, stateThree, reset} state; 

void Tick() {
	PORTB = ~PINB;
	PINA =	~PORTA;

	switch (state) { //transitions
		case start:
		state = wait;
		break;
		
		case wait:
			if ((A0) && (PORTB == 0x06))
			{
				state = stateOne;
			}
			if ((A0) && (PORTB == 0x02))
			{
				state = stateTwo;
			}
			if ((A0) && (PORTB == 0x04))
			{
				state = stateThree;
			}
		break;
		
		case stateOne:
			state = reset;
		break;

		case stateTwo:
			state = reset;
		break;

		case stateThree:
			state = reset;
		break;
		
		case reset:
			state = start;
		break;

		default:
		state = start;
		break;
	}

	switch (state){ //actions
		case start:
			PORTB = 0x07;
		break;
		
		case wait:
			PORTB = 0x01;
			PORTB = 0x02;
			PORTB = 0x04;

		case stateOne:
			PORTB = 0x01;
		break;

		case stateTwo:
			PORTB = 0x02;
		break;

		case stateThree:
			PORTB = 0x04;
		break;

		default:
			state = start;
		break;
	}

}

void TimerSet(unsigned long M) {
	_avr_timer_M = M;
	_avr_timer_cntcurr = _avr_timer_M;
}

int main(void)
{
	DDRA = 0x00; PORTA = 0xFF;
	DDRB = 0xFF; PORTB = 0x00;

	state = start;

	TimerSet(300);
	TimerOn();

	while(1)
	{
		Tick();
		while(!TimerFlag){}
		TimerFlag = 0;
	}
}

//add wait state for each one and add a reset
//
