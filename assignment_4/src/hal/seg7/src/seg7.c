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
#include "../../digital_output/include/digital_output.h"

// Segment off
#define BLANK_DIGIT 0xFF

// Holds possible values for segment, 10 = all elements of segment off. Decimal point always off
static char display_code[] = {0x3, 0x9F, 0x25, 0xD, 0x99, 0x49, 0x41, 0x1F, 0x1, 0x19};
	
// Current communication mode.
static communication_t communication = D_COMM;

// Segment that is currently being written to.
static uint8_t current_segment = 0;

// Indicates if all leading values of a segment is zero.
static uint8_t leading_zeros = 1;

// Holds number split into digits.
static uint8_t digits[] = {0, 0, 0, 0};

// Holds all separated digits as display code - default all elements of segment on.
static uint8_t display[] = {0x0, 0x0, 0x0, 0x0};
	
io_descriptor_t d_segments[D_NO_SEGMENTS];
io_descriptor_t d_rck;
io_descriptor_t d_sck;
io_descriptor_t d_si;
 

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

static void configure_spi()
{
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

void display_init(io_definition_t segment_pwr[], io_definition_t rck, io_definition_t sck, io_definition_t si) 
{
	// Configure outputs.
	for (uint8_t i = 0; i < D_NO_SEGMENTS; i++)
	{
		d_segments[i] = output_init(segment_pwr[i].port, segment_pwr[i].pin, DEFAULT, 0, ACTIVE);
	}
	
	d_rck = output_init(rck.port, rck.pin, DEFAULT, 0, INACTIVE);
	d_sck = output_init(sck.port, sck.pin, DEFAULT, 0, INACTIVE);
	d_si = output_init(si.port, si.pin, DEFAULT, 0, INACTIVE);

	if (communication == SPI) {
		configure_spi();
	}
	
	// Initializes timer and interrupt
	set_refresh_rate();
}

// Returns display code equivalent to digit value.
// If a zero is found, it will determine if it should return code equivalent to 0 or turn off the segment based on values in more significant segments.
static uint8_t get_display_code(uint8_t segment)
{
	// Least significant segment is allowed to be zero.
	if (segment == D_NO_SEGMENTS - 1)
		return display_code[digits[segment]];
	
	// If a value is zero and all more significant segments are zero it will return display code equivalent to be turned off. 
	if (digits[segment] == 0 && leading_zeros) 
		return BLANK_DIGIT;
	
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
	for (uint8_t i = 0; i < D_NO_SEGMENTS; i++) 
		display[i] = get_display_code(i);
}

// Splits number into separate digits.
static void split_digits(uint16_t value, uint8_t digit) 
{	
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
void display_print_uint_4(uint16_t value) 
{
	// Split digits from least significant value.
	split_digits(value, D_NO_SEGMENTS - 1);
	set_display_code();
}

static void turn_off_segments()
{
	for (uint8_t i = 0; i < D_NO_SEGMENTS; i++)
	{
		*d_segments[i]->port |= _BV(d_segments[i]->bit);
	}
		//D_D1_PORT |= _BV(D_D1_PIN);
		//D_D2_PORT |= _BV(D_D2_PIN);
		//D_D3_PORT |= _BV(D_D3_PIN);
		//D_D4_PORT |= _BV(D_D4_PIN);
}

static void toggle_pin(io_descriptor_t pin)
{
	*pin->port |= _BV(pin->bit);
	*pin->port = ~_BV(pin->bit);
	//D_RCK_PORT |= _BV(D_RCK_PIN);
	//D_RCK_PORT &= ~_BV(D_RCK_PIN);
}

static void transfer_to_display()
{
	if (communication == SPI)
	// Load Shift register
	SPDR = display[current_segment];
	else
	// Shift display code into register.
	for(uint8_t i = 0; i < 8; i++)
	{
		// bitwise right shift to onto serial input.
		if (display[current_segment] >> i & 1)
			*d_si->port |= _BV(d_si->bit);
		else
			*d_si->port &= ~_BV(d_si->bit);
		
		// shift into register.
		toggle_pin(d_sck);
	}
}

static void change_current_segment()
{
	current_segment = (current_segment + 1) % D_NO_SEGMENTS;
}

ISR(TIMER4_COMPA_vect)
{		
	turn_off_segments();
	
	// Move into storage register.
	toggle_pin(d_rck);
		
	// Turn on current segment.
	*d_segments[current_segment]->port &= ~(_BV(current_segment));
	
	change_current_segment();
		
	transfer_to_display();
}