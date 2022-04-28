/*
 * matrix.c
 *
 * Created: 28-04-2022 11:17:30
 *  Author: mathi
 */ 
#include "../include/matrix.h"
#include <avr/io.h>

typedef struct key_descr_t{
	volatile uint8_t* ddr;
	volatile uint8_t* pin;
	volatile uint8_t* port;
	uint8_t bit;
	
	}key_descr_t;
	
static key_descr_t keypad[] = {
	{&DDRB, &PINB, &PORTB, PB7}, //Row 1
	{&DDRB, &PINB, &PORTB, PB5}, //Row 2
	{&DDRB, &PINB, &PORTB, PB4}, //Row 3
	{&DDRE, &PINE, &PORTE, PE3}, //Row 4
	{&DDRE, &PINE, &PORTE, PE5}, //Col 1
	{&DDRH, &PINH, &PORTH, PH3}, //Col 2
	{&DDRH, &PINH, &PORTH, PH5}, //Col 3
	{&DDRL, &PINL, &PORTL, PL1}  //Col 4
};

void init_matrix_keyboard(){
	// Rows as Output
	for(uint8_t i=0; i<4; i++){
		*(keypad[i].ddr) |= _BV(keypad[i].bit);
		*(keypad[i].port) |= _BV(keypad[i].bit);
	}
	// Collumns as Input
	for (uint8_t a=4; a<8; a++)
	{
		*(keypad[a].ddr) &= ~_BV(keypad[a].bit);
		*(keypad[a].port) |= _BV(keypad[a].bit);
	}
}

static uint8_t val[4][4] = 
{{1,2,3,10},
{4,5,6,11},
{7,8,9,12},
{13,0,14,15}};

int8_t getxkey(){
	for (uint8_t b =0; b<4; b++)
	{
		// Set row to low (0)
		*(keypad[b].port) &= ~_BV(keypad[b].bit);
		for (uint8_t c =4; c<8; c++)
		{
			if((*(keypad[c].pin) & _BV(keypad[c].bit))==0){
				// set row to high (1)
				*(keypad[b].port) |= _BV(keypad[b].bit);
				return val[b][c-4];
			}
			
			
			
		}
		// set row to high (1)
		*(keypad[b].port) |= _BV(keypad[b].bit);
	}
	
	return 127;
}

	