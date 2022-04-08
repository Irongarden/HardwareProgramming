/*
 * _7seg.c
 *
 * Created: 01-04-2022 08:52:06
 * Authors:	Mathias Hansen - 274392
 *			Jacob Norsted - 273962
 */ 

#include <avr/io.h>
#include <avr/interrupt.h>
#include "../include/seg7.h"

// Output for display serial input.
#define SI PB2
// Output for display shift register clock pulse.
#define SCK PB1
// Output for display storage register clock pulse.
#define RCK PB0

// Output for segment 1-4 power. 
#define D1 PF0
#define D2 PF1
#define D3 PF2
#define D4 PF3

// No of segments in display.
#define SEGMENTS 4

// Holds possible values for segment, 10 = all elements of segment off. Decimal point always off
static char display_code[] = {0x3, 0x9F, 0x25, 0xD, 0x99, 0x49, 0x41, 0x1F, 0x1, 0x19, 0xFF};
	
// Current communication mode - default serial.
static communication_t communication = SERIAL;

// Segment that is currently being written to.
static uint8_t current_segment = 0;

// Indicates if all leading values of a segment is zero.
static uint8_t leading_zeros = 1;

// Holds number split into digits.
static uint8_t digits[SEGMENTS] = {0, 0, 0, 0};

// Holds all separated digits as display code - default all elements of segment on.
static uint8_t display[SEGMENTS] = {0x0, 0x0, 0x0, 0x0};

static void set_refresh_rate() 
{
	// Set timer toggle on compare match
	TCCR4A |= _BV(COM4A0);
	
	// Set prescaler 8
	TCCR4B |= _BV(CS41);
	
	// Set to Clear timer on compare match (CTC mode)
	TCCR4B |= _BV(WGM42);
	
	// Enable Timer interrupt
	TIMSK4 |= _BV(OCIE4A);
	
	// Set timer frequency 60Hz/digit (16000000 / (2*60*4*8))-1 = 4165.6
	OCR4A = 4166;
}

void init_display(communication_t mode) {
	// Set communication mode.
	communication = mode;
	
	// Set PF0-PF3 to output (digits)
	DDRF |= _BV(D1) | _BV(D2) | _BV(D3) | _BV(D4);
	
	// Set SI to output
	DDRB |= _BV(SI);
	
	// Set SCK to output
	DDRB |= _BV(SCK);
	
	// Set RCK to output
	DDRB |= _BV(RCK);
	
	if (communication == SPI) {
		// Setup CPOL functionality to sample at rising edge.
		SPCR &= ~ (_BV(CPOL) | _BV(CPHA));
	
		// DORD 0 OR 1: start from least significant bit or opposite.
		SPCR |=_BV(DORD);
	
		// Set Master.
		SPCR |= _BV(MSTR);
	
		// Set SCK frequency to Fosc/128.
		SPCR |= _BV(SPR1) | _BV(SPR0);
		SPSR &= ~_BV(SPI2X);
	
		// Enable SPI.
		SPCR |= _BV(SPE);
	}
	
	// Initializes timer and interrupt
	set_refresh_rate();
}

// Returns display code equivalent to digit value.
// If a zero is found, it will determine if it should return code equivalent to 0 or turn off the segment based on values in more significant segments.
static uint8_t get_display_code(uint8_t segment)
{
	// Least significant segment is allowed to be zero.
	if (segment == SEGMENTS - 1)
		return display_code[digits[segment]];
	
	// If a value is zero and all more significant segments are zero it will return display code equivalent to be turned off. 
	if (digits[segment] == 0 && leading_zeros) 
		return display_code[10];
	
	// First time a non-zero value is found leading zeros will be false. 
	// This effectively returns less significant zeros to display code equivalent to zero instead of having them turned off.
	if (leading_zeros)
		leading_zeros = 0;

	// Returns display code equivalent to digit value.
	return display_code[digits[segment]];
}

// Sets display code from separated digit values starting from most significant segment.
static void set_display_code() {
	leading_zeros = 1;
	for (uint8_t i = 0; i < SEGMENTS; i++) 
		display[i] = get_display_code(i);
}

// Splits number into separate digits.
static void split_digits(uint16_t value, uint8_t digit) {
	
	// Base case - Done.
	if (digit == 0)
		digits[digit] = value % 10;
	else {
		digits[digit] = value % 10;
		value = value / 10;
		
		// Recurse until done.
		digit--;
		split_digits(value, digit);
	}
}

// Input from application
void printint_4u(uint16_t value) 
{
	// Split digits from least significant value.
	split_digits(value, SEGMENTS - 1);
	set_display_code();
}

ISR(TIMER4_COMPA_vect)
{		
	// Turn off all segments
	PORTF |= _BV(D1) | _BV(D2) | _BV(D3)| _BV(D4);
	
	// Move into storage register.
	PORTB |= _BV(RCK);
	PORTB &= ~_BV(RCK);
		
	// Turn on current segment.
	PORTF &= ~(_BV(current_segment));
	
	// Increment to next segment.
	current_segment++;
		
	// Loops around to first segment again.
	if(current_segment == SEGMENTS)
		current_segment = 0;
		
	if (communication == SPI)
		SPDR = display[current_segment];
	else 
		// Shift display code into register.
		for(uint8_t i = 0; i < 8; i++)
		{
			// bitwise right shift to onto serial input.
			if (display[current_segment] >> i & 1)
			PORTB |=_BV(SI);
			else
			PORTB &= ~_BV(SI);
			
			// Shift into register.
			PORTB |= _BV(SCK);
			PORTB &= ~_BV(SCK);
		}
}