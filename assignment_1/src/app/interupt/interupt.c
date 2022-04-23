/*
 * interupt.c
 *
 * Created: 04/03/2022 09.44.45
 *  Author: Jacob
 */ 
#include <avr/io.h>
#include <avr/interrupt.h>
#include "interupt.h"

#define LOW 0
#define RISING_EDGE 1
#define FALLING_EDGE 2
#define ANY_EDGE 3


void init_ext_int(uint8_t trigger)
{
	switch (trigger) {
		case LOW:
			EICRA &= ~_BV(ISC20);
			EICRA &= ~_BV(ISC21);
			break;
		case RISING_EDGE:
			EICRA |= _BV(ISC20);
			EICRA |= _BV(ISC21);
			break;
		case FALLING_EDGE:
			EICRA &= ~_BV(ISC20);
			EICRA |= _BV(ISC21);
			break;
		case ANY_EDGE:
			EICRA |= _BV(ISC20);
			EICRA &= ~_BV(ISC21);
			break;
		default:
			break;
	}
	
	// Enable INT2 in the Externalinterrupt register
	EIMSK |= _BV(INT2);
}

void app_ext_int_start()
{
	init_ext_int(FALLING_EDGE);	sei();	}ISR(INT2_vect) {
	// Toggle PA0
	PORTA = PORTA ^ _BV(PA0);
}