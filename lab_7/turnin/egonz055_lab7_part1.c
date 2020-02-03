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
#include "io.c"


enum States{start, wait, plus, plus_on, minus, minus_on, reset} state;

volatile unsigned char TimerFlag = 0;

unsigned long _avr_timer_M = 1;

unsigned long _avr_timer_cntcurr = 0;

unsigned char current_num = 0;

unsigned char current_inputA = 0;

unsigned short counter;

void TimerOn() {
	TCCR1B = 0x0B;
	OCR1A = 125;
	TIMSK1 = 0x02;
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
void TimerSet(unsigned long M) {
	_avr_timer_M = M;
	_avr_timer_cntcurr = _avr_timer_M;
}

void Tick() {
	switch(state) {
	case start:
		state = wait;
		LCD_WriteData('0');
	break;

	case wait:
		if (current_inputA == 0x03) {
			state = reset;
			}
		else if (current_inputA == 0x02) {
			state = minus;
			}
		else if (current_inputA == 0x01) {
			state = plus;
			}
		else {
			state = wait;
			}
	break;

	case minus:
		if (current_inputA == 0x03) {
			state = reset;
			}
		else if (current_inputA == 0x02) {
			state = minus_on;
			}
		else {
			state = wait;
			}
	break;

	case plus:
		if (current_inputA == 0x03) {
			state = reset;
			}
		else if (current_inputA == 0x01) {
			state = plus_on;
			}
		else {
			state = wait;
			}
	break;

	case minus_on:
		if (current_inputA == 0x03) {
			state = reset;
			}
		else if (current_inputA == 0x00) {
			state = wait;
			}
		else if (current_inputA == 0x02) {
		counter++;
		}
	break;

	case plus_on:
		if (current_inputA == 0x03) {
			state = reset;
			}
		else if (current_inputA == 0x00) {
			state = wait;
			}
		else if (current_inputA == 0x01) {
		counter++;
		}
	break;

	case reset:
		if (current_inputA == 0x03) {
			state = reset;
			}
		else {
			state = wait;
			}
		break;
		default:
		
		break;
		}

	switch (state) {
	case wait:
		counter = 0;
	break;

	case minus:
		if (current_num > 0) {
		current_num--;
		LCD_ClearScreen();
		LCD_WriteData(current_num + '0');
	}
	break;

	case plus:
		if (current_num < 9) {
		current_num++;
		LCD_ClearScreen();
		LCD_WriteData(current_num + '0');
		}
	break;

	case minus_on:
		if (counter >= 10) {
		if (current_num > 0) {
		current_num--;
		LCD_ClearScreen();
		LCD_WriteData(current_num + '0');
		counter = 0;
		}
	}
	break;
	
	case plus_on:
		if (counter >= 10) {
		if (current_num < 9) {
		current_num++;
		LCD_ClearScreen();
		LCD_WriteData(current_num + '0');
		counter = 0;
		}
		}
	break;

	case reset:
		current_num = 0;
		LCD_ClearScreen();
		LCD_WriteData(current_num + '0');
	break;
	
	default:
	break;

		}
}

int main(void) {
	DDRA = 0; PORTA = 0xFF;
	DDRC = 0xFF; PORTC = 0x00;
	DDRD = 0xFF; PORTD = 0x00;
	state = start;
	current_num = 0;
	LCD_init();

	TimerSet(100);
	TimerOn();

	while (1) {
		current_inputA = ~PINA & 0x03;
		Tick();
		while (!TimerFlag) {};	
		TimerFlag = 0;
}
}
