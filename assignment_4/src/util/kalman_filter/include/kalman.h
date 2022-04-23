/*
 * kalman.h
 *
 * Created: 23/04/2022 20.18.41
 *  Author: Jacob
 */ 


#ifndef KALMAN_H_
#define KALMAN_H_

#include <stdint.h>

void kalman_init(double r, double q, double a, double b, double c);
uint8_t kalman_filter (uint8_t measurement);



#endif /* KALMAN_H_ */