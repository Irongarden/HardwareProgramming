/*
 * matrix_keyboard.h
 *
 * Created: 24/04/2022 01.49.31
 *  Author: Jacob
 */ 


#ifndef MATRIX_KEYPAD_H_
#define MATRIX_KEYPAD_H_

#include <stdint.h>
#include "../../../include/definitions.h"
#include "../../io_descriptior/include/io_descriptor.h"

#define PAD_R1_PORT				KEYPAD_R1_PORT
#define PAD_R1_PIN				KEYPAD_R1_PIN
#define PAD_R2_PORT				KEYPAD_R2_PORT
#define PAD_R2_PIN				KEYPAD_R2_PIN
#define PAD_R3_PORT				KEYPAD_R3_PORT
#define PAD_R3_PIN				KEYPAD_R3_PIN
#define PAD_R4_PORT				KEYPAD_R4_PORT
#define PAD_R4_PIN				KEYPAD_R4_PIN

#define PAD_C1_PORT				KEYPAD_C1_PORT
#define PAD_C1_PIN				KEYPAD_C1_PIN
#define PAD_C2_PORT				KEYPAD_C2_PORT
#define PAD_C2_PIN				KEYPAD_C2_PIN
#define PAD_C3_PORT				KEYPAD_C3_PORT
#define PAD_C3_PIN				KEYPAD_C3_PIN
#define PAD_C4_PORT				KEYPAD_C4_PORT
#define PAD_C4_PIN				KEYPAD_C4_PIN

#define KEYPAD_0				0
#define KEYPAD_1				1
#define KEYPAD_2				2
#define KEYPAD_3				3
#define KEYPAD_4				4
#define KEYPAD_5				5
#define KEYPAD_6				6
#define KEYPAD_7				7
#define KEYPAD_8				8
#define KEYPAD_9				9
#define KEYPAD_A				10
#define KEYPAD_B				11
#define KEYPAD_C				12
#define KEYPAD_ASTRIX			13
#define KEYPAD_NO				14
#define KEYPAD_D				15

#define KEYPAD_INACTIVE			127

#define PAD_ROW_DEFAULT_STATE	KEYPAD_ROW_DEFAULT_STATE

#define PAD_ACTIVE_STATE		KEYPAD_ACTIVE_STATE

#define PAD_COL_PULL_UP			KEYPAD_COL_PULL_UP

#define PAD_SIZE				4

void matrix_keypad_init();
int8_t matrix_keypad_get_x();

#endif /* MATRIX_KEYPAD_H_ */