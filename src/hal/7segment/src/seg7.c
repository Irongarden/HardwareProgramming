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

// Holds possible values for segment, 10 = all elements of segment off.
static char display_code[] = {0x3, 0x9F, 0x25, 0xD, 0x99, 0x49, 0x41, 0x1F, 0x1, 0x19, 0xFF};

// Segment that is currently being written to.
static uint8_t currentSegment = 0;

// Holds number split into digits - default all elements of segment off.
static uint8_t digits[SEGMENTS] = {0xFF, 0xFF, 0xFF, 0xFF};

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

void init_display() 
{
	// Set PF0-PF3 to output (digits)
	DDRF |= _BV(D1) | _BV(D2) | _BV(D3) | _BV(D4);
	
	// Set SI to output
	DDRB |= _BV(SI);
	
	// Set SCK to output
	DDRB |= _BV(SCK);
	
	// Set RCK to output
	DDRB |= _BV(RCK);
	
	// Initializes timer and interrupt
	set_refresh_rate();
}

// Returns display code.
// If a zero is found, it will determine if it should return code equivalent to 0 or turn off all elements of segment.
static uint8_t get_display_code(uint8_t segment)
{
	// Will return current value if non-zero except last digit (segment 3) are allowed to show 0.
	if (segment == SEGMENTS - 1 || digits[segment] != 0)
	{
		return digits[segment];
	}

	// Current digit is 0

	// No more segments to check
	if (segment == 0)
	{
		return display_code[10];
	}

	// Decrement segment to check the digit before.
	segment--;

	// Checks digit before, get_display_code returns 0xFF if only zeros are found.
	if (get_display_code(segment) == display_code[10])
	{
		// All previous digit are 0
		// Turns off the current segment.
		return display_code[10];
	}
	else
	{
		// A non-zero value is found in previous digits
		// Sets current segment to 0.
		return digits[segment];
	}
}

// Overwrites original separated values with display code equivalent. 
static void convert_to_display_code() {
	for (uint8_t i = 0; i < SEGMENTS - 1; i++) {
		digits[i] = get_display_code(digits[i]);
	}
}

// Splits number into separate digits.
static void split_digits(uint8_t value, uint8_t digit) {
	// Base case - Done.
	if (digit == 0) {
		digits[digit] = value % 10;
	}
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
	split_digits(value, SEGMENTS - 1);
	convert_to_display_code();
}


ISR(TIMER4_COMPA_vect)
{	
	// Shift display code into register.
	for(uint8_t i = 0; i < 8; i++)
	{
		// bitwise right shift to onto serial input.
		if (digits[currentSegment] >> i & 1) 
		{
			PORTB |=_BV(SI);
		} 
		else 
		{
			PORTB &= ~_BV(SI);
		}
		
		// Shift into register.
		PORTB |= _BV(SCK);
		PORTB &= ~_BV(SCK);
	}
		
	// Turn off all segments
	PORTF |= _BV(D1) | _BV(D2) | _BV(D3)| _BV(D4);
	
	// Move into storage register.
	PORTB |= _BV(RCK);
	PORTB &= ~_BV(RCK);
		
	// Turn on current segment.
	PORTF &= ~(_BV(currentSegment));
	
	// Increment to next segment.
	currentSegment++;
		
	// Loops around to first segment again.
	if(currentSegment == SEGMENTS)
	{
		currentSegment = 0;
	}
}
