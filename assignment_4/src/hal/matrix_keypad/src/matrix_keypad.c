/*
 * matrix_keypad.c
 *
 * Created: 24/04/2022 01.49.09
 *  Author: Jacob
 */ 

#include "../include/matrix_keypad.h"
#include "../../input/include/input.h"
#include "../../digital_output/include/digital_output.h"

// Outputs.
static io_descriptor_t row[PAD_SIZE];
// Inputs.
static io_descriptor_t col[PAD_SIZE];

// Matrix to represent keys on keypad.
static int8_t keypad[PAD_SIZE][PAD_SIZE] = {
	{KEYPAD_1, KEYPAD_2, KEYPAD_3, KEYPAD_A},
	{KEYPAD_4, KEYPAD_5, KEYPAD_6, KEYPAD_B},
	{KEYPAD_7, KEYPAD_8, KEYPAD_9, KEYPAD_C},
	{KEYPAD_ASTRIX, KEYPAD_0, KEYPAD_NO, KEYPAD_D},
};

static void configure_io()
{
	row[0] = output_init(PAD_R1_PORT, PAD_R1_PIN, ACTIVE_LOW, INACTIVE);
	row[1] = output_init(PAD_R2_PORT, PAD_R2_PIN, ACTIVE_LOW, INACTIVE);
	row[2] = output_init(PAD_R3_PORT, PAD_R3_PIN, ACTIVE_LOW, INACTIVE);
	row[3] = output_init(PAD_R4_PORT, PAD_R4_PIN, ACTIVE_LOW, INACTIVE);
	
	col[0] = input_init(PAD_C1_PORT, PAD_C1_PIN, ACTIVE_LOW, PAD_COL_PULL_UP, 0);
	col[1] = input_init(PAD_C2_PORT, PAD_C2_PIN, ACTIVE_LOW, PAD_COL_PULL_UP, 0);
	col[2] = input_init(PAD_C3_PORT, PAD_C3_PIN, ACTIVE_LOW, PAD_COL_PULL_UP, 0);
	col[3] = input_init(PAD_C4_PORT, PAD_C4_PIN, ACTIVE_LOW, PAD_COL_PULL_UP, 0);
}

void matrix_keypad_init()
{
	configure_io();
}

int8_t matrix_keypad_get_x()
{
	// Loop through rows.
	for (uint8_t r = 0; r < PAD_SIZE; r++)
	{
		// Set row active.
		output_set_state(row[r], ACTIVE);
		
		// Loop through columns.
		for (uint8_t c = 0; c < PAD_SIZE; c++)
		{
			// check if column is active.
			if (input_activated(col[c])){
				// Set row inactive.
				output_set_state(row[r], INACTIVE);
				// Lookup return value.
				return keypad[r][c];
			}
		}	
		// Set row inactive.
		output_set_state(row[r], INACTIVE);
	}
	// No input registered.
	return KEYPAD_INACTIVE;
}