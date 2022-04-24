/*
 * led.c
 *
 * Created: 20/02/2022 11.13.08
 * Authors:	Mathias Hansen - 274392
 *			Jacob Norsted - 273962
 */ 

#include <avr/io.h>
#include "../include/led.h"
#include "../../digital_output/include/digital_output.h"

static io_descriptor_t leds[L_NO];

void led_init(io_definition_t io[])
{	
	for (uint8_t i = 0; i < L_NO; i++)
	{
		leds[i] = output_init(io[i].port, io[i].pin, L_ACTIVE_STATE, L_DEFAULT_STATE);
	}
}

/*
* Leds are active low.
*/
void led_set(uint8_t led_no, state_t state)
{
	if (led_no >= 1 && led_no <= L_NO)
	{
		led_no --;	
		output_set_state(leds[led_no], state);
	}
}

/*
* Turns on all leds <= level og turns all off itteratively.
*/
void led_lightbar(uint8_t level) 
{
	if (level >= 0 && level <= L_NO) {
		for(uint8_t i = 1; i <= L_NO; i++)
		{
			if (i <= level)
				led_set(i, ACTIVE);
			else
				led_set(i, INACTIVE);
		}
	}	
}