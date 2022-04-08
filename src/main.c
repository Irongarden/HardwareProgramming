/*
 * assignment_2.c
 *
 * Created: 13/03/2022 14.36.01
 * Authors:	Mathias Hansen - 274392
 *			Jacob Norsted - 273962
 */ 

#include <avr/io.h>
#include <stdint.h>
#include <avr/interrupt.h>
#include "hal/tmp36/include/tmp36.h"
#include "hal/led/include/led.h"
#include "hal/7segment/include/seg7.h"
#include <util/delay.h>

// Offset 18 = led 1-8 @ 18-25 deg C.
#define offset 18
static uint8_t temp = 0;
static uint8_t led_level = 0;

// Temperature callback.
static void new_measurement(uint8_t deg_c)
{
	temp = deg_c;
}

int main(void)
{
	// Initialize HAL.
	init_leds();
	tmp36_init(new_measurement);
	init_display(SPI);
	
	// Enable interrupt globally.
	sei();
	
	// Will shortly turn on all elements in segments. 
	_delay_ms(500);
	
	// Application
    while (1)
    {		
		printint_4u(temp);
		
		led_level = temp - offset;
		
		if (led_level <= 0)
			lightbar(0);
		else if (led_level < 9)
			lightbar(led_level);
		else
			lightbar(8);
    }
	
	return 0;
}

