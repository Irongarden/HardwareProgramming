/*
 * definitions.h
 *
 * Created: 23/04/2022 10.16.26
 *  Author: Jacob
 *
 *
 * Defines application settings.
 */ 

#include <avr/io.h>
#include "../hal/io_descriptior/include/io_descriptor.h"

/************************************************************************/
/* Application Settings                                                 */
/************************************************************************/

#define NO_INPUT_KEYS				3

#define NO_OUTPUT_LEDS				8

#define PUMP_PORT					LED_1_PORT
#define PUMP_PIN					LED_1_PIN
#define PUMP_ACTIVE_STATE			LED_ACTIVE_STATE
#define PUMP_DEFAULT_STATE			INACTIVE

/************************************************************************/
/*  Default Initialization States                                       */
/************************************************************************/

#define LED_DEFAULT_STATE			INACTIVE

#define SEG_7_DN_DEFAULT_STATE		ACTIVE
#define SEG_7_RCK_DEFAULT_STATE		INACTIVE
#define SEG_7_SCK_DEFAULT_STATE		INACTIVE
#define SEG_7_SI_DEFAULT_STATE		INACTIVE

#define TMP36_ENABLE_DEFAULT_STATE	INACTIVE

#define KEYPAD_ROW_DEFAULT_STATE	INACTIVE

/************************************************************************/
/*  Pull-up Resistor Configuration                                      */
/************************************************************************/

#define KEY_PULL_UP					PULL_UP

#define TMP36_V_IN_PULL_UP			FLOATING

#define KEYPAD_COL_PULL_UP			PULL_UP

/************************************************************************/
/*  Port Active State Configuration                                     */
/************************************************************************/

#define KEY_ACTIVE_STATE			ACTIVE_LOW

#define LED_ACTIVE_STATE			ACTIVE_LOW
	
#define SEG_7_DN_ACTIVE_STATE		ACTIVE_LOW
#define SEG_7_RCK_ACTIVE_STATE		ACTIVE_HIGH
#define SEG_7_SCK_ACTIVE_STATE		ACTIVE_HIGH
#define SEG_7_SI_ACTIVE_STATE		ACTIVE_HIGH

#define TMP36_ENABLE_ACTIVE_STATE	ACTIVE_HIGH
#define TMP36_V_IN_ACTIVE_STATE		ANALOG

#define KEYPAD_ACTIVE_STATE		ACTIVE_LOW

/************************************************************************/
/* PORT A                                                               */
/************************************************************************/

#define LED_1_PORT					PA
#define LED_1_PIN					PA0

#define LED_2_PORT					PA
#define LED_2_PIN					PA1

#define LED_3_PORT					PA
#define LED_3_PIN					PA2
	
#define LED_4_PORT					PA
#define LED_4_PIN					PA3

#define LED_5_PORT					PA
#define LED_5_PIN					PA4

#define LED_6_PORT					PA
#define LED_6_PIN					PA5

#define LED_7_PORT					PA
#define LED_7_PIN					PA6

#define LED_8_PORT					PA
#define LED_8_PIN					PA7


/************************************************************************/
/* PORTB                                                                */
/************************************************************************/

#define SEG_7_RCK_PORT				PB
#define SEG_7_RCK_PIN				PB0

#define SEG_7_SCK_PORT				PB
#define SEG_7_SCK_PIN				PB1

#define SEG_7_SI_PORT				PB
#define SEG_7_SI_PIN				PB2

#define KEYPAD_R3_PORT				PB
#define KEYPAD_R3_PIN				PB4

#define KEYPAD_R2_PORT				PB
#define KEYPAD_R2_PIN				PB5

#define KEYPAD_R1_PORT				PB
#define KEYPAD_R1_PIN				PB7

/************************************************************************/
/* PORT C                                                               */
/************************************************************************/

#define KEY_T_LOW_PORT				PC
#define KEY_T_LOW_PIN				PC0
		
#define KEY_T_HIGH_PORT				PC
#define KEY_T_HIGH_PIN				PC1

#define KEY_T_CURR_PORT				PC
#define KEY_T_CURR_PIN				PC2

/************************************************************************/
/* PORT D                                                               */
/************************************************************************/


/************************************************************************/
/* PORT E                                                               */
/************************************************************************/

#define KEYPAD_R4_PORT				PE
#define KEYPAD_R4_PIN				PE3

#define KEYPAD_C1_PORT				PE
#define KEYPAD_C1_PIN				PE5

/************************************************************************/
/* PORT F                                                               */
/************************************************************************/

#define SEG_7_D1_PORT				PF
#define SEG_7_D1_PIN				PF0
		
#define SEG_7_D2_PORT				PF
#define SEG_7_D2_PIN				PF1

#define SEG_7_D3_PORT				PF
#define SEG_7_D3_PIN				PF2

#define SEG_7_D4_PORT				PF
#define SEG_7_D4_PIN				PF3

/************************************************************************/
/* PORT G                                                               */
/************************************************************************/

#define TMP36_ENABLE_PORT			PG
#define TMP36_ENABLE_PIN			PG0

/************************************************************************/
/* PORT H                                                               */
/************************************************************************/

#define KEYPAD_C2_PORT				PH
#define KEYPAD_C2_PIN				PH3

#define KEYPAD_C3_PORT				PH
#define KEYPAD_C3_PIN				PH5

/************************************************************************/
/* PORT J                                                               */
/************************************************************************/


/************************************************************************/
/* PORT K                                                               */
/************************************************************************/

#define TMP36_V_IN_PORT				PK
#define TMP36_V_IN_PIN				PK7

/************************************************************************/
/* PORT L                                                               */
/************************************************************************/

#define KEYPAD_C4_PORT				PL
#define KEYPAD_C4_PIN				PL1

//************************************************************************
/**  
*	Timers
*
*		- ADC:				TIMER 1 B
*		- Segment display:	TIMER 4 A     
* 
**/
//************************************************************************