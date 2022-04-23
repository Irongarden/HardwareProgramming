/*
 * assignment1.c
 *
 * Created: 04/03/2022 09.30.16
 */ 

/*
* Setting all leds.
*/
#include <avr/io.h>
#include "assignment1.h"
#include "../../hal/key/include/key.h"
#include "../../hal/led/include/led.h"

void assignment_1_start() 
{	
	set_led(1, get_key(1) & get_key(2));
	set_led(2, get_key(1) | get_key(2));
	set_led(3, get_key(1) ^ get_key(2));
	set_led(4, !(get_key(1) & get_key(2)));
	set_led(5, !(get_key(1) | get_key(2)));
	set_led(6, !(get_key(1) ^ get_key(2)));
}