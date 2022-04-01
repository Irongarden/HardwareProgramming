/*
 * _7seg.c
 *
 * Created: 01-04-2022 08:52:06
 *  Author: mathias
 */ 

#include <stdint.h>
#include <avr/io.h>
#include <stdio.h>
#include "../include/seg7.h"
#include <avr/interrupt.h>


#define SI PB2
#define SCK PB1
#define RCK PB0
#define D1 PF0
#define D2 PF1
#define D3 PF2
#define D4 PF3

uint8_t segment = 0;
uint8_t digits[4] = {8,8,8,8};
static char segValues[] = {0x3, 0x9F, 0x25, 0xD, 0x99, 0x49, 0x41, 0x1F, 0x1, 0x19, 0xFF};


void init_display(){
	// Set PF0-PF3 to output (digits)
	DDRF |= _BV(D1) | _BV(D2) | _BV(D3) | _BV(D4);
	
	
	
	// Set SI to output
	DDRB |= _BV(SI);
	
	// Set SCK to output
	
	DDRB |= _BV(SCK);
	
	// Set RCK to output
	
	DDRB |= _BV(RCK);
	
	
	// Initializes Timer and interrupt
	setrefreshrate();
}

void printint_4u(uint16_t value){
	digits[3] = value%10;
	value = value/10;
	digits[2] = value%10;
	value = value/10;
	digits[1] = value%10;
	value = value/10;
	digits[0] = value%10;
}

void setrefreshrate()
{
	// Set timer toggle on compare match
	TCCR4A |= _BV(COM4A0);
	
	// Set prescaler 8
	TCCR4B |= _BV(CS41);
	
	// Set to Clear timer on compare match (CTC mode)
	TCCR4B |= _BV(WGM42);
	
	// Enable Timer interrupt
	TIMSK4 |= _BV(OCIE4A);
	
	// Set timer frequency 60Hz/digit (16000000 / (2*240*8))-1 = 4165.6
	OCR4A = 4166;
}

void cleardisplay(){
	// Turn off digit displays
	PORTF |= _BV(D1) | _BV(D2) | _BV(D3)| _BV(D4);
}

uint8_t getValue(uint8_t val){
	
}

ISR(TIMER4_COMPA_vect){	
	for(uint8_t i =0; i<8;i++){
		uint8_t val = digits[segment];
		
		if (segment == 0 && val == 0){
			val = 10;
		}
		else if (segment == 1 && val == 0){
			if (digits[segment - 1] == 0) {
				val = 10;
			}
		} else if ( segment == 2 && val == 0){
			if (digits[segment -1] == 0 && digits[segment -2] == 0){
				val = 10;
			}
		}
		
	
		// Convert digit to display code.
		if(segValues[val]>>i & 1){
			PORTB |=_BV(SI);
			}else{
			PORTB &= ~_BV(SI);
		}
		PORTB |= _BV(SCK);
		PORTB &= ~_BV(SCK);
	}
		
	cleardisplay();
		
	PORTB |= _BV(RCK);
	PORTB &= ~_BV(RCK);
		
		
	PORTF &= ~(_BV(segment));
	segment++;
		
	if(segment==4){
		segment = 0;
	}
}
