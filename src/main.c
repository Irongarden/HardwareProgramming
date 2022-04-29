/*
 * assignment_2.c
 *
 * Created: 13/03/2022 14.36.01
 * 
 */ 

#include <avr/io.h>
#include <stdint.h>
#include <avr/interrupt.h>
#include "hal/tmp36/include/tmp36.h"
#include "hal/led/include/led.h"
#include "hal/7segment/include/seg7.h"
#include "hal/matrix16/include/matrix.h"
#include "hal/key/include/key.h"
#include <util/delay.h>
#include <stdio.h>

// Offset 17 = led 1-8 @ 18-25 deg C.
#define offset 17
static uint8_t temp = 0;
static uint8_t key = 3; // Current temp default key press
uint8_t keypress = 0; // Default pressed key
uint16_t array_to_int(uint8_t arr[]);
uint8_t array[4] = {0,0,0,0}; // Array for entered keys

static void new_measurement(uint8_t deg_c)
{
	temp = deg_c;
}


int main(void)
{
	init_leds();
	
	tmp36_init(new_measurement);
	init_display(SPI);
	init_matrix_keyboard();
	init_keys();
	
	// Enable interrupt globally.
	sei();
	int8_t tlow = 20; // Default low temp
	int8_t thigh = 25; //Default high temp
	int8_t tlowNew = 0; // New Temp low value
	int8_t thighNew = 0; // New Temp high value
	
	
	_delay_ms(500);
	printint_4u(0);
    while (1) 
    {
		
		keypress = scan_key();
		
		
		if(keypress){
			//_delay_ms(100);
			key = keypress;	
			//printint_4u(scan_key());
		}
		
		
		switch (key){						// Which key pressed
			
			case 3:							// Current temp
			
			printint_4u(temp);
			//printint_4u(keypress);
			//printint_4u(temp);
			break;
			
			case 2:							// High temp
			
			
			if(thighNew!=0){
				printint_4u(thighNew);
			}else{
				printint_4u(thigh);
			}
			uint8_t k = getxkey();
			_delay_ms(200);
			
			
			if(k!=127) // if keys are pressed
			{
				if(k==14){ // If save pressed
					thigh = thighNew;
					thighNew = 0;
					array[3] = 0;
					array[2] = 0;
				}else if(k==13){ // if Cancel pressed
					thighNew = 0;
					array[3] = 0;
					array[2] = 0;
				}else if(thighNew<=99){ // check if value is inside spectra
					if(array[3]!=0){
						array[2]=array[3];
						array[3]=0;
						}else{
						array[3] = k;
					}
					thighNew = array_to_int(array);
					
					//thighNew += k;
				}
				
				
				}
			break;
			
			case 1:							// Low temp
			printint_4u(tlow);
			break;
		}
		
		
		//else{
			//bob = getxkey();
			////_delay_ms(500);
			//printint_4u(bob);
		//}
		
		//uint8_t level = temp - offset;
		//if (level <= 0)
		//{
			//lightbar(0);
		//}
		//else if (level < 9)
		//{
			//lightbar(level);
		//}
		//else
		//{
			//lightbar(8);
		//}
    }
	
	
	
	
	//return 0;
}

uint16_t array_to_int(uint8_t array[])
{
	uint16_t k = 0;
	for (uint8_t i = 0; i < 4; i++)
	{
		k = 10 * k + array[i];
	}

	return k;
}

void newT(int8_t new, int8_t old, uint8_t k){
	
}

