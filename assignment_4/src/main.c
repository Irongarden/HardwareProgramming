/*
 * assignment_2.c
 *
 * Created: 13/03/2022 14.36.01
 * Authors:	Mathias Hansen - 274392
 *			Jacob Norsted - 273962
 */ 

#include <stdlib.h>
#include <stdint.h>
#include <util/delay.h>
#include <avr/io.h>
#include <avr/interrupt.h>

#include "util/kalman_filter/include/kalman.h"
#include "include/definitions.h"
#include "hal/digital_input/include/digital_input.h"
#include "hal/digital_output/include/digital_output.h"
#include "hal/key/include/key.h"
#include "hal/pump/include/pump.h"

#include "hal/tmp36/include/tmp36.h"
#include "hal/seg7/include/seg7.h"   
#include "hal/led/include/led.h" 

        
// Offset 18 = led 1-8 @ 18-25 deg C.
#define offset 18

static uint8_t t_current = 0;
static uint8_t t_filtered = 0;
static uint8_t t_low = 22;
static uint8_t t_high = 24;
static uint8_t display_current = 3;
static uint8_t key_current = 0;


// Temperature callback.
static void new_measurement(uint8_t deg_c)
{
	t_current = deg_c;  
}

static void shift_keys_init()
{
	io_definition_t keys[] = {
		{KEY_T_LOW_PORT, KEY_T_LOW_PIN}, 
		{KEY_T_HIGH_PORT, KEY_T_HIGH_PIN},
		{KEY_T_CURR_PORT, KEY_T_CURR_PIN}
	};
	key_init(keys);
}


static void leds_init_all()
{
	io_definition_t leds[] = {
		{LED_2_PORT, LED_2_PIN},
		{LED_3_PORT, LED_3_PIN},
		{LED_4_PORT, LED_4_PIN},
		{LED_5_PORT, LED_5_PIN},
		{LED_6_PORT, LED_6_PIN},
		{LED_7_PORT, LED_7_PIN},
		{LED_8_PORT, LED_8_PIN}
	};
	led_init(leds);
}

static void segment_display_init()
{
	io_definition_t segments[] = {
		{SEG_7_D1_PORT, SEG_7_D1_PIN},
		{SEG_7_D2_PORT, SEG_7_D2_PIN},
		{SEG_7_D3_PORT, SEG_7_D3_PIN},
		{SEG_7_D4_PORT, SEG_7_D4_PIN},
	};
	io_definition_t rck = {SEG_7_RCK_PORT, SEG_7_RCK_PIN};
	io_definition_t sck = {SEG_7_SCK_PORT, SEG_7_SCK_PIN};
	io_definition_t si = {SEG_7_SI_PORT, SEG_7_SI_PIN};
		
	display_init(segments, rck, sck, si);
}

// Application
static void run() {
	t_filtered = kalman_filter(t_current);
	
	key_current = key_scan();
	
	if (key_current)
	display_current = key_current;
	
	switch (display_current)
	{
		case 1:
			display_print_uint_4(t_low);
			break;
		case 2:
			display_print_uint_4(t_high);
			break;
		case 3:
			display_print_uint_4(t_filtered);
			break;
		default:
			break;
	}
	
	if (t_filtered < t_low)
	{
		pump_stop();
	}
	else if (t_filtered >= t_high)
	{
		pump_start();
	}
}

static void hal_init()
{
	shift_keys_init();
	pump_init();
	segment_display_init();
	leds_init_all();
	
	tmp36_init(new_measurement);
	
}

static void util_init()
{
	// Initialize basic kalman filter
	kalman_init(0.001, 5, 1, 0, 1);
}

int main(void)
{
	util_init();
	hal_init();
	
	// Enable interrupt globally.
	sei();
	
	// Will shortly turn on all elements in display segments. 
	_delay_ms(500);
	
	// Application
    while (1)
    {	
		run();
    }
	
	return 0;
}

