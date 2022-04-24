/*
 * digital_output.c
 *
 * Created: 23/04/2022 13.36.56
 *  Author: Jacob
 */ 

#include <stdlib.h>
#include <avr/io.h>
#include "../include/digital_output.h"

static void configure_output(io_descriptor_t output)
{
	// Initialize Data Direction Register for each output-pin.
	*(io_ddr(output)) |= _BV(io_bit(output));
}

io_descriptor_t output_init(port_t port, uint8_t bit, active_state_t active, state_t default_state)
{
	io_descriptor_t output = io_descriptor_init(port, bit, active);
	
	configure_output(output);
	
	output_set_state(output, default_state);
	
	return output;
}

return_code_t output_set_state(io_descriptor_t output, state_t state)
{
	if (io_active_state(output) == ACTIVE_LOW) {
		if (state == ACTIVE) {
			// Set port low.
			*(io_port(output)) &= ~_BV(io_bit(output));
		}
		else {
			// Set port high.
			*(io_port(output)) |= _BV(io_bit(output));
		}
	}
	else {
		if (state == ACTIVE) {
			// set port high.
			*(io_port(output)) |= _BV(io_bit(output));
		}
		else {
			// Set port low.
			*(io_port(output)) &= ~_BV(io_bit(output));
		}
	}
	
	// Could preform a check of the actual pin state. 
	return OK;
}

return_code_t output_destroy(io_descriptor_t output)
{
	return io_descriptor_destroy(output);
}
