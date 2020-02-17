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
#include <avr/interrupt.h>

enum three_states {time_start, input_0, input_1, input_2} t_state;
enum blink_states {blink_start, turnoff, input_3} b_state;
enum output_state {start, writing} output_state;

unsigned char var1 = 0x00; 

unsigned char varBlink = 0x00;

volatile unsigned char TimerFlag = 0;
unsigned long _avr_timer_M = 1;
unsigned long _avr_timer_cntcurr = 0;

void TimerOn() {
	
	TCCR1B = 0x0B;// bit3 = 0: CTC mode (clear timer on compare)
	
	OCR1A = 125;	// Timer interrupt will be generated when TCNT1==OCR1A
	
	TIMSK1 = 0x02; // bit1: OCIE1A -- enables compare match interrupt

	TCNT1=0;

	_avr_timer_cntcurr = _avr_timer_M;
	
	SREG |= 0x80; // 0x80: 1000000
}
void TimerOff() {
	TCCR1B = 0x00; // bit3bit1bit0=000: timer off
}
void TimerISR() {
	TimerFlag = 1;
}
ISR(TIMER1_COMPA_vect) {
	_avr_timer_cntcurr--; // Count down to 0 rather than up to TOP
	if (_avr_timer_cntcurr == 0) { // results in a more efficient compare
		TimerISR(); // Call the ISR that the user uses
		_avr_timer_cntcurr = _avr_timer_M;
	}
	
}

void TimerSet(unsigned long M) {
	_avr_timer_M = M;
	_avr_timer_cntcurr = _avr_timer_M;
}

void tick_LED() {
	switch (t_state) {
		
		case time_start: 
			t_state = input_0; 
		break;
		
		case input_0: 
			t_state = input_1; 
		break;
		
		case input_1: 
			t_state = input_2; 
		break;
		
		case input_2: 
			t_state = input_0; 
		break;
		
		default: 
		break;
	}
	switch (t_state) {
		
		case time_start: 
		break;
		
		case input_0: 
			var1 = 0x01; 
		break;
		
		case input_1: 
			var1 = 0x02; 
		break;
		
		case input_2: 
			var1 = 0x04; 
		break;
		
		default: 
		break;
	}
}
void tick_blink() {
	switch (b_state) {
		
		case blink_start: 
			b_state = turnoff; 
		break;
		
		case turnoff: 
			b_state = input_3; 
		break;
		
		case input_3: 
			b_state = turnoff; 
		break;
		
		default: 
		break;
	}
	switch (b_state) {
		
		case blink_start: 
		break;
		
		case turnoff: 
		varBlink = 0x00; 
		break;
		
		case input_3: 
		varBlink = 0x08; 
		break;
		
		default: 
		break;
	}
}
void output_Tick() {
	switch (output_state) {
		
		case start: 
			output_state = writing; 
		break;
		
		case writing: 
		break;
		
		default: 
		break;
	}
	switch (output_state) {
		
		case start: 
		break;
		
		case writing:
			PORTB = varBlink | var1;
		break;
		
		default: break;
	}
}
int main(void)
{
	DDRB = 0xFF; PORTB = 0x00;
	
	unsigned long t_elapsedTime = 0;
	unsigned long b_elapsedTime = 0;
	
	const unsigned long timerPeriod = 100;
	
	TimerSet(100);
	TimerOn();
	
	t_state = start;
	b_state = blink_start;
	
	while (1)
	{
		if (t_elapsedTime >= 1000) 
		{
			tick_LED();
			t_elapsedTime = 0;
		}
		if (b_elapsedTime >= 1000) 
		{
			tick_blink();
			b_elapsedTime = 0;
		}
		
		output_Tick();
		
		while (!TimerFlag) {}	// Wait 1 sec
		TimerFlag = 0;
		
		b_elapsedTime = timerPeriod + 1;
		t_elapsedTime = timerPeriod + 1;
	}
}
