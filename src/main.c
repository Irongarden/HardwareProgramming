/*
 * assignment_2.c
 *
 * Created: 13/03/2022 14.36.01
 * 
 */ 

#include <avr/io.h>
#include <stdint.h>
#include <avr/interrupt.h>
#include "hal/tmp36/include/tmp36.h"
#include "hal/led/include/led.h"
#include "hal/7segment/include/seg7.h"
#include "hal/matrix16/include/matrix.h"
#include <util/delay.h>

// Offset 17 = led 1-8 @ 18-25 deg C.
#define offset 17
static uint8_t temp = 0;

static void new_measurement(uint8_t deg_c)
{
	temp = deg_c;
}


int main(void)
{
	init_leds();
	tmp36_init(new_measurement);
	init_display();
	init_matrix_keyboard();
	
	// Enable interrupt globally.
	sei();
	int8_t bob = 0;
	
    while (1) 
    {
		bob = getxkey();
		//_delay_ms(500);
		printint_4u(bob);
		//uint8_t level = temp - offset;
		//if (level <= 0)
		//{
			//lightbar(0);
		//}
		//else if (level < 9)
		//{
			//lightbar(level);
		//}
		//else
		//{
			//lightbar(8);
		//}
    }
	
	return 0;
}

