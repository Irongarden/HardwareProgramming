/*
 * digital_output.c
 *
 * Created: 23/04/2022 13.36.56
 *  Author: Jacob
 */ 

#include <stdlib.h>
#include <avr/io.h>
#include "../include/digital_output.h"

static void configure_output(io_descriptor_t output, uint8_t init_state, state_t default_state)
{
	// Initialize Data Direction Register for each output-pin.
	*(output->ddr) |= _BV(output->bit);
	
	// Initialise default state.
	if (init_state)
		output_set_state(output, default_state);
}

io_descriptor_t output_init(port_t port, uint8_t bit, active_state_t active, uint8_t init_state, state_t default_state)
{
	// Reserving memory.
	io_descriptor_t output = malloc(sizeof(io_descriptor_st));
	
	// Checking that memory is reserved.
	if (0 == output) {
		return 0;
	}
	
	// Input validation.
	if (!(bit >= 0 && bit <= 7)) {
		return 0;
	}
	
	// Assign values.
	output->bit = bit;
	output->active = active;
	
	switch (port) {
		case PA:
			output->ddr = &DDRA;
			output->pin = &PINA;
			output->port = &PORTA;
			break;
		case PB:
			output->ddr = &DDRB;
			output->pin = &PINB;
			output->port = &PORTB;
			break;
		case PC:
			output->ddr = &DDRC;
			output->pin = &PINC;
			output->port = &PORTC;
			break;
		case PD:
			output->ddr = &DDRD;
			output->pin = &PIND;
			output->port = &PORTD;
			break;
		case PE:
			output->ddr = &DDRE;
			output->pin = &PINE;
			output->port = &PORTE;
			break;
		case PF:
			output->ddr = &DDRF;
			output->pin = &PINF;
			output->port = &PORTF;
			break;
		case PG:
			output->ddr = &DDRG;
			output->pin = &PING;
			output->port = &PORTG;
			break;
		default:
			return 0;
	}
	
	configure_output(output, init_state, default_state);
	
	return output;
}

return_code_t output_set_state(io_descriptor_t self, state_t state)
{
	if (self->active == ACTIVE_LOW) {
		if (state == ACTIVE) {
			// Set port low.
			*(self->port) &= ~_BV(self->bit);
		}
		else {
			// Set port high.
			*(self->port) |= _BV(self->bit);
		}
	}
	else {
		if (state == ACTIVE) {
			// set port high.
			*(self->port) |= _BV(self->bit);
		}
		else {
			// Set port low.
			*(self->port) &= ~_BV(self->bit);
		}
	}
	
	// Could preform a check of the actual pin state. 
	return OK;
}

return_code_t output_destroy(io_descriptor_t self)
{
	if (0 == self) {
		return IS_NULL;
	}
	
	free(self);
	
	return OK;
}
