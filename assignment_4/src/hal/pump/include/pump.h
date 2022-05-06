/*
 * pump.h
 *
 * Created: 23/04/2022 17.47.57
 *  Author: Jacob
 *
 * Implemented as a single led.
 */ 


#ifndef PUMP_H_
#define PUMP_H_

#include "../../../include/definitions.h"

// Pump output port.
// type: port_t
#define P_PORT			PUMP_PORT

// Pump output pin.
// type: uint8_t
#define P_PIN			PUMP_PIN

// Pump active state configuration.
// Type: active_state_t
#define P_ACTIVE_STATE	PUMP_ACTIVE_STATE

// Pump default initialization state.
// Type: state_t
#define P_DEFAULT_STATE	PUMP_DEFAULT_STATE

void pump_init();
return_code_t pump_start();
return_code_t pump_stop();

#endif /* PUMP_H_ */