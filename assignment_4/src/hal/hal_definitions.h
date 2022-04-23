/*
 * hal_definitions.h
 *
 * Created: 23/04/2022 11.24.13
 *  Author: Jacob
 */ 


#ifndef HAL_DEFINITIONS_H_
#define HAL_DEFINITIONS_H_

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
	PG
} port_t;

typedef enum
{
	ACTIVE_LOW = 0,
	ACTIVE_HIGH,
	DEFAULT
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
	INACTIVE = 0,
	ACTIVE
} state_t;

typedef struct io_descriptor* io_descriptor_t;

typedef struct io_descriptor
{
	volatile uint8_t* ddr;
	volatile uint8_t* pin;
	volatile uint8_t* port;
	active_state_t active;
	uint8_t bit;
} io_descriptor_st;

#endif /* HAL_DEFINITIONS_H_ */