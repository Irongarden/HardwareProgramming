/*
 * led.c
 *
 * Created: 20/02/2022 11.13.08
 * Authors:	Mathias Hansen - 274392
 *			Jacob Norsted - 273962
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
	if (led_no > 0 && led_no < 9)
	{
		if (state == ON)
		{
			// Set port low.
			PORTA &= ~_BV(led_no - 1);
		}
		else
		{
			// Set port high.
			PORTA |= _BV(led_no - 1);
		}
	}
}

/*
* Turns on all leds <= level og turns all off itteratively.
*/
void lightbar(uint8_t level) 
{
	if (level >= 0 && level <= 8)
	{
		for(uint8_t i = 1; i <= 8; i++)
		{
			if (i <= level) 
			{
				set_led(i, ON);
			}
			else
			{
				set_led(i, OFF);	
			}
		}
	}
}