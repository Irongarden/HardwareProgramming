/*
 * kalman.c
 *
 * Created: 23/04/2022 20.18.54
 *  Author: Jacob
 */ 

#include "../include/kalman.h"

static double _r; // noise power desirable
static double _q; // noise power estimated
static double _a;
static double _b;
static double _c;
static double _cov = -1;
static double _u = 0;
static double _x = 255; // estimated signal without noise

void kalman_init(double r, double q, double a, double b, double c)
{
	_r = r;
	_q = q;
	_a = a;
	_b = b;
	_c = c;
}

static double predict() 
{
	return (_a * _x) + (_b * _u);
}

static double uncertenty()
{
	return ((_a * _cov) * _a) + _r; 
}

uint8_t kalman_filter(uint8_t measurement)
{
	if (_x == 255)
	{
		_x = (1 / _c) * measurement;
		_cov = (1 / _c) * _q * (1 / _c); 
	}
	else 
	{
		// compute prediction
		double pred_x = predict();
		double pred_cov = uncertenty();
		
		// kalman gain
		double k = pred_cov  * _c * (1 / ((_c * pred_cov * _c) + _q));
		
		// Correction
		_x = pred_x + k * (measurement - (_c * pred_x));
		_cov = pred_cov - (k * _c * pred_cov);
	}
	 return _x;
}