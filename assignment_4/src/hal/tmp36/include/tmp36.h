/*
 * temperature_sensor.h
 *
 * Created: 13/03/2022 14.52.34
 * Authors:	Mathias Hansen - 274392
 *			Jacob Norsted - 273962
 */ 


#ifndef tmp36_H_
#define tmp36_H_

#include <stdint.h>
#include "../../../include/definitions.h"

// TMP36 port configuration.
// type: port_t
#define V_IN_PORT						TMP36_V_IN_PORT
#define ENABLE_PORT						TMP36_ENABLE_PORT

// TMP36 pin configuration.
// type: uint8_t
#define V_IN_PIN						TMP36_V_IN_PIN
#define ENABLE_PIN						TMP36_ENABLE_PIN

// TMP36 active state configuration.
// Type: active_state_t
#define V_IN_ACTIVE_STATE				TMP36_V_IN_ACTIVE_STATE
#define ENABLE_ACTIVE_STATE				TMP36_ENABLE_ACTIVE_STATE

// TMP36 input pull up configuration
// Type: pull_up_t
#define V_IN_PULL_UP					TMP36_V_IN_PULL_UP

// TMP36 enable default initialization state.
// Type: state_t
#define ENABLE_DEFAULT_STATE			TMP36_ENABLE_DEFAULT_STATE

void tmp36_init(void (*callback)(uint8_t deg_c));

// Measurement frequency.
// 1 Hz. (16000000 / (2 * 1 * 256)) - 1 = 31249
// Type: uint16_t
#define HZ  31249;

// For testing only.
uint8_t mv_to_c(uint16_t mv);
uint16_t adc_to_mv(uint16_t adc);

#endif /* tmp36_H_ */