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
#define D_NO_SEGMENTS	4

// Communication Mode
#define D_COMM			SPI

void display_init(io_definition_t segment_pwr[], io_definition_t rck, io_definition_t sck, io_definition_t si);
void display_print_uint_4(uint16_t value);

#endif /* 7seg_H_ */