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

#include "../../digital_output/include/digital_output.h"
#include "../../../include/definitions.h"
#include "../../hal_definitions.h"

#define P_PORT			PUMP_PORT
#define P_PIN				PUMP_PIN
#define P_ACTIVE_STATE	PUMP_ACTIVE_STATE
#define P_DEFAULT_STATE	PUMP_DEFAULT_STATE

void pump_init();
return_code_t pump_start();
return_code_t pump_stop();

#endif /* PUMP_H_ */