/*
 * input.h
 *
 * Created: 23/04/2022 11.06.16
 *  Author: Jacob
 */ 

#ifndef INPUT_H_
#define INPUT_H_
#include <stdint.h>
#include "../../io_descriptior/include/io_descriptor.h"

/**
* Specifies the edge when the interrupt and callback is triggered.
* Type: trigger_t.
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
uint8_t input_activated(io_descriptor_t input);

return_code_t input_destroy(io_descriptor_t input);

#endif /* INPUT_H_ */