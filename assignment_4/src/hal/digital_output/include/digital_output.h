/*
 * digital_output.h
 *
 * Created: 23/04/2022 13.36.33
 *  Author: Jacob
 */ 

#ifndef DIGITAL_OUTPUT_H_
#define DIGITAL_OUTPUT_H_

#include <stdint.h>
#include "../../hal_definitions.h"

io_descriptor_t output_init(port_t port, uint8_t bit, active_state_t active, uint8_t init_stat, state_t default_state);
return_code_t output_set_state(io_descriptor_t self, state_t state);
return_code_t output_destroy(io_descriptor_t self);

#endif /* DIGITAL_OUTPUT_H_ */