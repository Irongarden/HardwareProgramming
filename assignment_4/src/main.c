/*
 * assignment_2.c
 *
 * Created: 13/03/2022 14.36.01
 * Authors:	Mathias Hansen - 274392
 *			Jacob Norsted - 273962
 */ 

#include <stdlib.h>
#include <stdint.h>
#include <stdio.h>
#include <util/delay.h>
#include <avr/io.h>
#include <avr/interrupt.h>

#include "include/definitions.h"
#include "hal/key/include/key.h"
#include "hal/pump/include/pump.h"
#include "hal/tmp36/include/tmp36.h"
#include "util/kalman_filter/include/kalman.h"
#include "hal/seg7/include/seg7.h"   
#include "hal/led/include/led.h"
#include "hal/matrix_keypad/include/matrix_keypad.h" 
        
// Offset 18 = led 1-8 @ 18-25 deg C.
#define OFFSET 18

// Keypad value redefines.
#define SAVE KEYPAD_NO
#define CANCEL KEYPAD_ASTRIX

// Temperature variables.
static uint8_t t_current = 0;
static uint8_t t_filtered = 0;
static uint16_t t_low = 22;
static uint16_t t_high = 24;

// Determines what is displayed. 1: t_low, 2: t_high, 3, t_filtered. 
static uint8_t display_current = 3;

// Holds values from key input.
static uint8_t display_key = 0;
// Holds values from keypad input.
static int8_t keypad_current = KEYPAD_INACTIVE;

// Temperature callback.
static void tmp36_callback(uint8_t deg_c)
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

static uint16_t array_to_int(uint8_t arr[])
{
	uint16_t k = 0;
	for (uint8_t i = 0; i < D_NO_SEGMENTS; i++)
	{
		k = 10 * k + arr[i];
	}
	
	return k;
}

static void take_input()
{
	uint16_t input_value = 0;
	uint8_t inputs[] = {0, 0, 0, 0};

	display_print_uint_4(input_value);
	_delay_ms(200);
	do
	{
		keypad_current = matrix_keypad_get_x();
		
		if (keypad_current >= KEYPAD_0 && keypad_current <= KEYPAD_9)
		{	
			// Left shift array to fit next number.
			for (uint8_t i = 0; i < D_NO_SEGMENTS - 1; i++) {
				inputs[i] = inputs[i + 1];
			}	
			// Add new digit to end of array.		
			inputs[3] = keypad_current;
		}
		else if (keypad_current == KEYPAD_D)
		{
			// right shift array to delete last input.
			for (uint8_t i = D_NO_SEGMENTS - 1; i > 0; i--)
			{
				inputs[i] = inputs[i - 1];			
			}
			inputs[0] = 0;		
		}
		
		// convert input array to int.
		input_value = array_to_int(inputs);
		
		display_print_uint_4(input_value);
		_delay_ms(300);
		
	} while (keypad_current != SAVE && keypad_current != CANCEL);
	
	// save new value.
	if (keypad_current == SAVE)
	{
		// Show SAVE in display
		display_save();
		switch (display_current)
		{
			case 1:
				t_low = input_value;
				break;
			case 2:
				t_high = input_value;
				break;
			default:
				break;
		}
		
		// Display save 1s.
		_delay_ms(1000);
		// Show current temperature when returning.
		display_current = 3;
	}
}

// Application
static void run_solar_heating() {
	t_filtered = kalman_filter(t_current);
	
	// check input keys for changing display.
	display_key = key_scan();
	
	if (display_key)
		display_current = display_key;
	
	keypad_current = matrix_keypad_get_x();
	
	// check keypad for changing display.
	switch (keypad_current) {
		case KEYPAD_A:
			display_current = 1;
			break;
		case KEYPAD_B:
			display_current = 2;
			break;
		case KEYPAD_C:
			display_current = 3;
			break;
		default:
			break;
	}

	// set display.
	switch (display_current)
	{
		case 1:
			if (keypad_current >= KEYPAD_0 && keypad_current <= KEYPAD_9)
				take_input();
			else 
				display_print_uint_4(t_low);
			break;
		case 2:
			if (keypad_current >= KEYPAD_0 && keypad_current <= KEYPAD_9)
				take_input();
			else
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
	leds_init_all();
	shift_keys_init();
	pump_init();
	display_init();
	tmp36_init(tmp36_callback);
	matrix_keypad_init();
}

static void util_init()
{
	// Initialize basic Kalman filter
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
		run_solar_heating();
    }
	
	return 0;
}
