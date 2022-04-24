/*
 * io_descriptor.h
 *
 * Created: 23/04/2022 11.24.13
 *  Author: Jacob
 */ 

#ifndef IO_DESCRIPTOR_H_
#define IO_DESCRIPTOR_H_

#include <stdint.h>
#include <avr/io.h>

typedef enum
{
	PA = 0,
	PB,
	PC,
	PD,
	PE,
	PF,
	PG,
	PH,
	PJ,
	PK,
	PL
} port_t;

typedef enum
{
	ACTIVE_LOW = 0,
	ACTIVE_HIGH,
	ANALOG
} active_state_t;

typedef enum
{
	IS_NULL = 0,
	ERROR,
	OK
} return_code_t;

typedef struct  
{
	port_t port;
	uint8_t pin;
} io_definition_t;

typedef enum
{
	FALLING_EDGE = 0,
	RISING_EDGE,
	ANY_EDGE
} trigger_t;

typedef enum
{
	FLOATING = 0,
	PULL_UP
} pull_up_t;

typedef enum
{
	INACTIVE = 0,
	ACTIVE
} state_t;

typedef struct io_desc* io_descriptor_t;

io_descriptor_t io_descriptor_init(port_t port, uint8_t bit, active_state_t active);
return_code_t io_descriptor_destroy(io_descriptor_t self);
volatile uint8_t* io_ddr(io_descriptor_t self);
volatile uint8_t* io_pin(io_descriptor_t self);
volatile uint8_t* io_port(io_descriptor_t self);
active_state_t io_active_state(io_descriptor_t self);
uint8_t io_bit(io_descriptor_t self);

#endif /* IO_DESCRIPTOR_H_ */