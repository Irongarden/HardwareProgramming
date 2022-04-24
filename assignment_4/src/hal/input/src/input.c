/*
 * input.c
 *
 * Created: 23/04/2022 11.06.28
 *  Author: Jacob
 */ 

#include <stdlib.h>
#include <avr/io.h>
#include <avr/interrupt.h>
#include "../include/input.h"

static void (*cb2)() = 0;
static void (*cb3)() = 0;

static void configure_input(io_descriptor_t input, pull_up_t pull_up_res)
{
	// Initialize Data Direction Register for each input-pin.
	*(input->ddr) &= ~_BV(input->bit);
		
	// Enable Pull-ups on each input.
	if (pull_up_res == PULL_UP)
		*(input->port) |= _BV(input->bit);
}

static void set_trigger(uint8_t reg0, uint8_t reg1, uint8_t int_n)
{
	switch (cb_trigger)
	{
		case FALLING_EDGE:
			EICRA &= ~_BV(reg0);
			EICRA |= _BV(reg1);
			break;
		case RISING_EDGE:
			EICRA |= _BV(reg0);
			EICRA |= _BV(reg1);
			break;
		case ANY_EDGE:
			EICRA |= _BV(reg0);
			EICRA &= ~_BV(reg1);
			break;
		default:
			break;
	}
	
	// Enable external interrupt in register.
	EIMSK |= _BV(int_n);
}

io_descriptor_t input_init(port_t port, uint8_t bit, active_state_t active, pull_up_t pull_up_res, void (*cb)())
{
	io_descriptor_t input = io_descriptor_init(port, bit, active);
	
	configure_input(input, pull_up_res);
	
	// Configure callback.
	if (0 != cb)
	{
		// Configure interrupt.
		if (port == PD)
		{
			if (bit == PD2)
			{
				cb2 = cb;
				set_trigger(ISC20, ISC21, INT2);
			}
			else if (bit == PD3)
			{
				cb3 = cb;
				set_trigger(ISC30, ISC31, INT3);
			}
		}
	}

	return input;
}

uint8_t input_activated(io_descriptor_t input)
{
	switch (input->active)
	{
		case ACTIVE_LOW:
			return (((*input->pin) & _BV(input->bit)) == 0);
		case ACTIVE_HIGH:
			return !(((*input->pin) & _BV(input->bit)) == 0);
		default:
			return 0;
	}
}

return_code_t input_destroy(io_descriptor_t input)
{
	return io_descriptor_destroy(input);
}

ISR(INT2_vect)
{
	if (0 != cb2)
	cb2();
}

ISR(INT3_vect)
{
	if (0 != cb3)
	cb3();
}