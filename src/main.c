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
static uint8_t keypress = 0; // Default pressed key
static uint16_t array_to_int(uint8_t arr[]);
static uint8_t array[4] = {0,0,0,0}; // Array for entered keys
	static int8_t tlow = 19; // Default low temp
	int8_t thigh = 25; //Default high temp
	int8_t tlowNew = 0; // New Temp low value
	int8_t thighNew = 0; // New Temp high value

static void new_measurement(uint8_t deg_c)
{
	temp = deg_c;
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

int8_t newT(int8_t new, int8_t old, uint8_t k){
	if(k==14){ // If save pressed
		new = old;
		new = 0;
		array[3] = 0;
		array[2] = 0;
		}else if(k==13){ // if Cancel pressed
		new = 0;
		array[3] = 0;
		array[2] = 0;
		}else if(k<10){ // check if value is inside spectra
		array[2]=array[3];
		array[3]=k;
		new = array_to_int(array);
		return new;
		
	}
	return 127;
	
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
	
	
	
	_delay_ms(500);
	printint_4u(0);
    while (1) 
    {
		//assignment1();
		
		if(temp>thigh){
			lightbar(1);
		}else if(temp<tlow){
			lightbar(0);
		}
		
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
				
				uint8_t n = newT(thighNew,thigh,k);
				if(n!=127){
					thighNew =n;
				}
				
				
				
				}
			break;
			
			case 1:							// Low temp
			if(tlowNew!=0){
				printint_4u(tlowNew);
				}else{
				printint_4u(tlow);
			}
			uint8_t s = getxkey();
			_delay_ms(200);
			
			
			if(s!=127) // if keys are pressed
			{
				uint8_t x = newT(tlowNew,tlow,s);
				if(x!=127){
					tlowNew =x;
				}
				 
				
			}
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

void assignment1(){
	
		set_led(0,get_key(1) & get_key(2));// AND = True
		set_led(1,get_key(1) | get_key(2));//OR LED ON
		set_led(2,get_key(1) ^ get_key(2));//XOR LED OFF
		set_led(3,!(get_key(1) & get_key(2)));//NAND OFF
		set_led(4,!(get_key(1) | get_key(2)));//NOR OFF
		set_led(5,!(get_key(1) ^ get_key(2)));//XNOR ON
}

void assignment2(){
	if()
}



