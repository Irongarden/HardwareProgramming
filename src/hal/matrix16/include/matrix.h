/*
 * matrix.h
 *
 * Created: 28-04-2022 11:17:19
 *  Author: Mathias
 */ 
#include <avr/io.h>

#ifndef MATRIX_H_
#define MATRIX_H_


void init_matrix_keyboard(); // Initialization of matrix keyboard.
int8_t getxkey(); // Function returning pressed key on matrix keyboard.


#endif /* MATRIX_H_ */