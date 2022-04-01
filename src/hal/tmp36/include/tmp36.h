/*
 * temperature_sensor.h
 *
 * Created: 13/03/2022 14.52.34
 * 
 */ 


#ifndef tmp36_H_
#define tmp36_H_

#include <avr/io.h>
#include <stdint.h>

void tmp36_init(void (*callback)(uint8_t deg_c));

// For testing only.
uint8_t mv_to_c(uint16_t mv);
uint16_t adc_to_mv(uint16_t adc);

#endif /* tmp36_H_ */