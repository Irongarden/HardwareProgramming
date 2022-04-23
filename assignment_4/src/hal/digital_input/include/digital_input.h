/*
 * digital_input.h
 *
 * Created: 23/04/2022 11.06.16
 *  Author: Jacob
 */ 

#include "../../hal_definitions.h"

#ifndef DIGITAL_INPUT_H_
#define DIGITAL_INPUT_H_

typedef enum 
{
	FALLING_EDGE = 0,
	RISING_EDGE,
	ANY_EDGE
} trigger_t;

typedef enum 
{
	FLOATING = 0,
	PULL_UP
} pull_up_t;

/**
* Specifies the edge when the interrupt and callback is triggered.
* Must be trigger_t.
**/
#define cb_trigger FALLING_EDGE


/**
* Configures the io and returns a DI struct.
* Callbacks can be used with:
*	- PD2, INT2
*	- PD3, INT3 
**/
io_descriptor_t input_init(port_t port, uint8_t bit, active_state_t active, pull_up_t pull_up, void (*cb)());

/**
* Returns 0 if the input is inactive and 1 if active. 
**/
uint8_t input_activated(io_descriptor_t self);

return_code_t input_destroy(io_descriptor_t self);

#endif /* DIGITAL_INPUT_H_ */