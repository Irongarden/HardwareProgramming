/*
 * _7seg.h
 *
 * Created: 01-04-2022 08:51:56
 * Authors:	Mathias Hansen - 274392
 *			Jacob Norsted - 273962
 */ 

#ifndef SEG7_H_
#define SEG7_H_

#include <stdint.h>
#include "../../../include/definitions.h"

typedef enum {
	SERIAL = 0,
	SPI
} communication_t;

// No of segments in display.
#define D_NO_SEGMENTS				4

// Communication Mode
#define D_COMM						SPI  // must be of type communication_t.

#define D_7_D1_PORT					SEG_7_D1_PORT
#define D_7_D1_PIN					SEG_7_D1_PIN

#define D_7_D2_PORT					SEG_7_D2_PORT
#define D_7_D2_PIN					SEG_7_D2_PIN

#define D_7_D3_PORT					SEG_7_D3_PORT
#define D_7_D3_PIN					SEG_7_D3_PIN

#define D_7_D4_PORT					SEG_7_D4_PORT
#define D_7_D4_PIN					SEG_7_D4_PIN

#define D_7_DN_ACTIVE_STATE			SEG_7_DN_ACTIVE_STATE
#define D_7_DN_DEFAULT_STATE		SEG_7_DN_DEFAULT_STATE

#define D_7_RCK_PORT				SEG_7_RCK_PORT
#define D_7_RCK_PIN					SEG_7_RCK_PIN
#define D_7_RCK_ACTIVE_STATE		SEG_7_RCK_ACTIVE_STATE
#define D_7_RCK_DEFAULT_STATE		SEG_7_RCK_DEFAULT_STATE

#define D_7_SCK_PORT				SEG_7_SCK_PORT
#define D_7_SCK_PIN					SEG_7_SCK_PIN
#define D_7_SCK_ACTIVE_STATE		SEG_7_SCK_ACTIVE_STATE
#define D_7_SCK_DEFAULT_STATE		SEG_7_SCK_DEFAULT_STATE

#define D_7_SI_PORT					SEG_7_SI_PORT
#define D_7_SI_PIN					SEG_7_SI_PIN
#define D_7_SI_ACTIVE_STATE			SEG_7_SI_ACTIVE_STATE
#define D_7_SI_DEFAULT_STATE		SEG_7_SI_DEFAULT_STATE

void display_init();
void display_print_uint_4(uint16_t value);
void display_save();

#endif /* 7seg_H_ */