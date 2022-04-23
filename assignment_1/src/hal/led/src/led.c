/*
 * led.c
 *
 * Created: 20/02/2022 11.13.08

 */ 

#include <avr/io.h>
#include "../include/led.h"

void init_leds()
{
	// set pin direction to output
	DDRA = 0xFF;
	// turn all leds off - Active low
	PORTA = 0xFF;
}

/*
* Leds are active low.
*/
void set_led(uint8_t led_no, uint8_t state)
{
	uint8_t led = led_no - 1;
	if (led >= 0 && led <= 7)
	{
		if (state == ON)
		{
			// Set port low.
			PORTA &= ~_BV(led);
		}
		else
		{
			// Set port high.
			PORTA |= _BV(led);
		}
	}
}

/*
* Turns on all leds <= level og turns all off itteratively.
*/
void lightbar(uint8_t level) 
{
	if (level > 0)
	{
		for(uint8_t i = 0; i < level; i++)
		{
			set_led(i + 1, ON);
		}
	}
	else
	{
		for(uint8_t i = 0; i < 8; i++)
		{
			set_led(i + 1, OFF);
		}
	}
}