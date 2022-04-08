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

uint8_t segment = 2;
uint8_t digits[4] = {8,8,8,8};
static char segValues[] = {0x3, 0x9F, 0x25, 0xD, 0x99, 0x49, 0x41, 0x1F, 0x1, 0x19, 0xFF};
uint8_t display[4] = {0xFF,0xFF,0xFF,0xFF};


void init_display(){
	// Set PF0-PF3 to output (digits)
	DDRF |= _BV(D1) | _BV(D2) | _BV(D3) | _BV(D4);
	
	//--!!!! SPI Change: !!!!!--
	
	// Setup CPOL functionality to sample at rising edge.
	SPCR &= ~ (_BV(CPOL) | _BV(CPHA));
	
	// DORD 0 OR 1: start from least significant bit or opposite.
	SPCR |=_BV(DORD);
	
	SPCR |= _BV(MSTR);
	
	// set SCK frequency to Fosc/128
	SPCR |= _BV(SPR1) | _BV(SPR0);
	SPSR &= ~_BV(SPI2X);
	
	// Enable SPI
	SPCR |= _BV(SPE);
	 
	//--!!!! SPI Change: !!!!!--
	
	// Set SI to output
	DDRB |= _BV(SI);
	
	// Set SCK to output
	
	DDRB |= _BV(SCK);
	
	// Set RCK to output
	
	DDRB |= _BV(RCK);
	
	
	// Initializes Timer and interrupt
	setrefreshrate();
}

void convert(){
	
	display[0]=segValues[digits[0]];
	display[1]=segValues[digits[1]];
	display[2]=segValues[digits[2]];
	display[3]=segValues[digits[3]];
	
}
void printint_4u(uint16_t value){
	
	// Seperating digits
	digits[3] = value%10;
	value = value/10;
	digits[2] = value%10;
	value = value/10;
	digits[1] = value%10;
	value = value/10;
	digits[0] = value%10;
	
	convert();
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


ISR(TIMER4_COMPA_vect){	
	
	
	//for(uint8_t i =0; i<8;i++){
		//uint8_t val = digits[segment];
		//
		//// Turns off digit display if value = 0 and is first display.
		//if (segment == 0 && val == 0){
			//val = 10;
		//}
		//// Turns off digit display if value = 0 and display before = 0.
		//else if (segment == 1 && val == 0){
			//if (digits[segment - 1] == 0) {
				//val = 10;
			//}
			//// Turns off digit display if value = 0 and 2 displays before are both 0.
		//} else if ( segment == 2 && val == 0){
			//if (digits[segment -1] == 0 && digits[segment -2] == 0){
				//val = 10;
			//}
		//}
		//
	//
		//// Convert digit to display code.
		//if(segValues[val]>>i & 1){
			//// load SI with value
			//PORTB |=_BV(SI);
			//}else{
			//PORTB &= ~_BV(SI);
		//}
		//// Clock the value into the storage register
		//PORTB |= _BV(SCK);
		//PORTB &= ~_BV(SCK);
	//}
	
	
	
	
	
	
	cleardisplay();
		// Clock to state output
	PORTB |= _BV(RCK);
	PORTB &= ~_BV(RCK);
		
		
	PORTF &= ~(_BV(segment));
	segment++;
		
		
	if(segment==4){
		segment = 0;
	}
	SPDR = display[segment];
}
