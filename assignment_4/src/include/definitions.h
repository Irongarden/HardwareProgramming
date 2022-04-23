/*
 * definitions.h
 *
 * Created: 23/04/2022 10.16.26
 *  Author: Jacob
 */ 

#include <avr/io.h>
#include "../hal/hal_definitions.h"

/************************************************************************/
/* Application Settings                                                                     */
/************************************************************************/

#define NO_INPUT_KEYS		3

#define NO_OUTPUT_LEDS		7

/************************************************************************/
/*  Default Initialization States                                                                     */
/************************************************************************/

#define LED_DEFAULT_STATE		INACTIVE

#define PUMP_DEFAULT_STATE		INACTIVE

/************************************************************************/
/*  Pull-up Resistor Configuration                                                                     */
/************************************************************************/

#define KEY_PULL_UP			PULL_UP

/************************************************************************/
/*  Port Active State Configuration                                                                     */
/************************************************************************/

#define KEY_ACTIVE_STATE	ACTIVE_LOW

#define PUMP_ACTIVE_STATE	ACTIVE_LOW

#define LED_ACTIVE_STATE	ACTIVE_LOW

/************************************************************************/
/* PORT A                                                                     */
/************************************************************************/

#define PUMP_PORT			PA
#define PUMP_PIN			PA0

#define LED_2_PORT			PA
#define LED_2_PIN			PA1

#define LED_3_PORT			PA
#define LED_3_PIN			PA2

#define LED_4_PORT			PA
#define LED_4_PIN			PA3

#define LED_5_PORT			PA
#define LED_5_PIN			PA4

#define LED_6_PORT			PA
#define LED_6_PIN			PA5

#define LED_7_PORT			PA
#define LED_7_PIN			PA6

#define LED_8_PORT			PA
#define LED_8_PIN			PA7

/************************************************************************/
/* PORTB                                                                     */
/************************************************************************/

#define SEG_7_RCK_PORT		PB
#define SEG_7_RCK_PIN		PB0

#define SEG_7_SCK_PORT		PB
#define SEG_7_SCK_PIN		PB1

#define SEG_7_SI_PORT		PB
#define SEG_7_SI_PIN		PB2

/************************************************************************/
/* PORT C                                                                     */
/************************************************************************/

#define KEY_T_LOW_PORT		PC
#define KEY_T_LOW_PIN		PC0

#define KEY_T_HIGH_PORT		PC
#define KEY_T_HIGH_PIN		PC1

#define KEY_T_CURR_PORT		PC
#define KEY_T_CURR_PIN		PC2

/************************************************************************/
/* PORT D                                                                   */
/************************************************************************/


/************************************************************************/
/* PORT E                                                                  */
/************************************************************************/


/************************************************************************/
/* PORT F                                                                  */
/************************************************************************/

#define SEG_7_D1_PORT		PF
#define SEG_7_D1_PIN		PF0

#define SEG_7_D2_PORT		PF
#define SEG_7_D2_PIN		PF1

#define SEG_7_D3_PORT		PF
#define SEG_7_D3_PIN		PF2

#define SEG_7_D4_PORT		PF
#define SEG_7_D4_PIN		PF3

/************************************************************************/
/* PORT G                                                                   */
/************************************************************************/


/************************************************************************/
/*  Timers
/*
/*		- ADC:				TIMER 1 B
/*		- Segment display:	TIMER 4 A                                                                    */
/************************************************************************/