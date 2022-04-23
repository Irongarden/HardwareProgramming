/*
 * main.c
 *
 * Created: 20/02/2022 11.08.39
 */ 
#include <avr/io.h>
#include <avr/interrupt.h>
#include "hal/key/include/key.h"
#include "hal/led/include/led.h"
#include "app/assignment1/assignment1.h"
#include "app/interupt/interupt.h"

int main(void)
{
	// Initializing hardware.
	init_leds();
	init_keys();
	
	
	app_ext_int_start();
	
    while (1) 
    {	
		//assignment_1_start();
		
		//lightbar(scan_key());
	}
	
	return 0;
}
