/*
 * tmp36.c
 *
 * Created: 13/03/2022 14.53.26
 * Authors:	Mathias Hansen - 274392
 *			Jacob Norsted - 273962
 */ 

#include <stdlib.h>
#include <avr/io.h>
#include <avr/interrupt.h>
#include "../include/tmp36.h"
#include "../../digital_output/include/digital_output.h"
#include "../../input/include/input.h"

// Callback
static void (*cb)(uint8_t deg_c) = 0;

// IO
static io_descriptor_t v_in;
static io_descriptor_t enable;

// Not static for testing purposes.
uint8_t mv_to_c(uint16_t mv)
{
	return (mv - 500) / 10;	
}

// Not static for testing purposes.
uint16_t adc_to_mv(uint16_t adc)
{
	// Should have been adc * (v_ref / adc_max) = (uint16_t)((float) adc * ( (float) 5000 / (float) 1023)), but had truble with int devision.
	return adc * 4.887585533;
}

void tmp36_init(void (*callback)(uint8_t deg_c))
{
	// configure io.
	enable = output_init(ENABLE_PORT, ENABLE_PIN, ENABLE_ACTIVE_STATE, ENABLE_DEFAULT_STATE);
	v_in = input_init(V_IN_PORT, V_IN_PIN, V_IN_ACTIVE_STATE, V_IN_PULL_UP, NULL);
	
	// Set callback.
	if (0 != callback)
	{
		cb = callback;
	}
	
	// AVCC reference (5V).
	ADMUX |= _BV(REFS0);
	
	// Input channel select ADC15.
	ADMUX |= _BV(MUX2) | _BV(MUX1) | _BV(MUX0);
	ADCSRB |= _BV(MUX5);
	
	// Set pre-scaler 64
	ADCSRA |= _BV(ADPS1) | _BV(ADPS2);

	// Set auto trigger source timer1 Compare Match Channel B
	ADCSRB |= _BV(ADTS2) | _BV(ADTS0);
	
	// ****** Interrupt and auto trigger end ****
	
	// ***** Configure Timer 1 Channel B. ******
	
	// Set timer to toggle on compare match.
	TCCR1A |= _BV(COM1B0);
	
	// Set Clock frequency to 16MHz/256 = 62500kHz
	TCCR1B |=  _BV(CS12);  //256 prescaler
	
	// Set to Clear timer on Compare Match mode (CTC).
	TCCR1B |= _BV(WGM12);

	// set timer frequency 1 Hz. (16000000 / (2 * 1 * 256)) - 1 = 31249
	OCR1B = HZ; // ADC trigger on TOP
	OCR1A = HZ; // Counter top
	
	// Enable interrupt.
	ADCSRA |= _BV(ADIE);
	
	// Enable Auto Trigger
	ADCSRA |= _BV(ADATE);
	
	// Enable ADC
	ADCSRA |= _BV(ADEN);
	
	// Enable TMP36
	output_set_state(enable, ACTIVE);
	
	// Start Conversion.
	ADCSRA |= _BV(ADSC);
}

// AD Interrupt callback.
ISR(ADC_vect)
{
	// ADC (16bits) = ADCH and ADCL - Default right adjusted ADC value = 0-1023.
	if (0 != cb)
		cb(mv_to_c(adc_to_mv(ADC)));
	
	// Clear timer interrupt flag.
	TIFR1 |= _BV(OCR1B);
}