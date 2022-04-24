/*
 * io_descriptor.c
 *
 * Created: 24/04/2022 10.20.05
 *  Author: Jacob
 */ 

#include <stdlib.h>
#include <avr/io.h>
#include "../include/io_descriptor.h"

typedef struct io_desc {
	volatile uint8_t* ddr;
	volatile uint8_t* pin;
	volatile uint8_t* port;
	active_state_t active;
	uint8_t bit;
} io_desc_st;

io_descriptor_t io_descriptor_init(port_t port, uint8_t bit, active_state_t active)
{
	// Reserving memory.
	io_descriptor_t desc = malloc(sizeof(io_desc_st));
	
	// Checking that memory is reserved.
	if (0 == desc) {
		return 0;
	}
	
	// Input validation.
	if (!(bit >= 0 && bit <= 7)) {
		return 0;
	}
	
	// Assign values.
	desc->bit = bit;
	desc->active = active;
	
	switch (port) {
		case PA:
			desc->ddr = &DDRA;
			desc->pin = &PINA;
			desc->port = &PORTA;
			break;
		case PB:
			desc->ddr = &DDRB;
			desc->pin = &PINB;
			desc->port = &PORTB;
			break;
		case PC:
			desc->ddr = &DDRC;
			desc->pin = &PINC;
			desc->port = &PORTC;
			break;
		case PD:
			desc->ddr = &DDRD;
			desc->pin = &PIND;
			desc->port = &PORTD;
			break;
		case PE:
			desc->ddr = &DDRE;
			desc->pin = &PINE;
			desc->port = &PORTE;
			break;
		case PF:
			desc->ddr = &DDRF;
			desc->pin = &PINF;
			desc->port = &PORTF;
			break;
		case PG:
			desc->ddr = &DDRG;
			desc->pin = &PING;
			desc->port = &PORTG;
			break;
		case PH:
			desc->ddr = &DDRH;
			desc->pin = &PINH;
			desc->port = &PORTH;
			break;
		case PJ:
			desc->ddr = &DDRJ;
			desc->pin = &PINJ;
			desc->port = &PORTJ;
			break;
		case PK:
			desc->ddr = &DDRK;
			desc->pin = &PINK;
			desc->port = &PORTK;
			break;
		case PL:
			desc->ddr = &DDRL;
			desc->pin = &PINL;
			desc->port = &PORTL;
			break;
		default:
			return 0;
	}
	
	return desc;
}

volatile uint8_t* io_ddr(io_descriptor_t self)
{
	return self->ddr;
}

volatile uint8_t* io_pin(io_descriptor_t self)
{
	return self->pin;
}

volatile uint8_t* io_port(io_descriptor_t self)
{
	return self->port;
}

active_state_t io_active_state(io_descriptor_t self)
{
	return self->active;
}

uint8_t io_bit(io_descriptor_t self)
{
	return self->bit;
}

return_code_t io_descriptor_destroy(io_descriptor_t self)
{
	if (0 == self) {
		return IS_NULL;
	}
	
	free(self);
	
	return OK;
}