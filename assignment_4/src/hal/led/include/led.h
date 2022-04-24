/*
 * led.h
 *
 * Created: 20/02/2022 11.12.37
 * Authors:	Mathias Hansen - 274392
 *			Jacob Norsted - 273962
 */ 

#ifndef LED_H_
#define LED_H_

#include <stdint.h>
#include "../../../include/definitions.h"
#include "../../io_descriptior/include/io_descriptor.h"

#define L_NO			NO_OUTPUT_LEDS
#define L_ACTIVE_STATE	LED_ACTIVE_STATE
#define L_DEFAULT_STATE	LED_DEFAULT_STATE

void led_init(io_definition_t io[]);
void led_set(uint8_t led_no, state_t state);
void led_lightbar(uint8_t level);

#endif /* LED_H_ */