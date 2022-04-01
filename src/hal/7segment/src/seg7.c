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

// Segment that is currently being written to.
static uint8_t currentSegment = 0;

// Holds number split into digits.
static uint8_t digits[SEGMENTS] = {8, 8, 8, 8};
	
// Holds possible values for segment, 10 = OFF 
static char segValues[] = {0x3, 0x9F, 0x25, 0xD, 0x99, 0x49, 0x41, 0x1F, 0x1, 0x19, 0xFF};

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
	
	// Set timer frequency 60Hz/digit (16000000 / (2*240*8))-1 = 4165.6
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

// Splits number into digits.
void printint_4u(uint16_t value) 
{
	digits[3] = value % 10;
	value = value / 10;
	digits[2] = value % 10;
	value = value / 10;
	digits[1] = value % 10;
	value = value / 10;
	digits[0] = value % 10;
}

// Returns the number that should be converted to display code.
// If a zero is found, it will determine if it should return 0 or 10 where 10 will turn off the segment.
static uint8_t get_digit(uint8_t segment) 
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
		 return 10;
	 }

	 // Decrement segment to check the digit before.
	 segment--;

	 // Checks digit before, getDigit returns 10 if only zeros are found.
	 if (get_digit(segment) == 10) 
	 {
		 // All previous digit are 0
		 // Turns off the current segment.
		 return 10;
	 }
	 else 
	 {
		 // A non-zero value is found in previous digits
		 // Sets current segment = 0.
		 return 0;
	 }
}

ISR(TIMER4_COMPA_vect)
{	
	// Gets the value for the current segment. 
	uint8_t val = get_digit(currentSegment);
	
	// Convert digit to display code
	for(uint8_t i = 0; i < 8; i++)
	{
		// Value bitwise right shift to onto serial input.
		if (segValues[val] >> i & 1) 
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
