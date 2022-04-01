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

void init_display();
void printint_4u(uint16_t value);

#endif /* 7seg_H_ */