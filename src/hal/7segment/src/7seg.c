/*
 * _7seg.c
 *
 * Created: 01-04-2022 08:52:06
 *  Author: mathias
 */ 

#include <stdint.h>
#include <avr/io.h>
#include <stdio.h>

void init_display(){
	// Set PF0-PF3 to output (digits)
	DDRF |= _BV(PF0) | _BV(PF1) | _BV(PF2) | _BV(PF3);
	
	// Set SI to output
	DDRB |= _BV(PB2);
	
	// Set SCK to output
	
	DDRB |= _BV(PB1);
	
	// Set RCK to output
	
	DDRB |= _BV(PB0);
}

void printint_4u(uint16_t value){
	//std::map<uint8_t, uint8_t> segvalue;
	//segvalue[0]=10101101;
	
//
	//unsigned int v = value;
	//unsigned int dig = count(v);
	//uint8_t one;
	//char arr[dig];
	//while (dig--){
		//arr[dig]=v%10;
		//v/=10;
	//}
	//uint8_t i =0;
	//while(arr[i]!=NULL){
		//if(arr[i]==0){
			////digit = 7segv[0];
		//}
	//}
	//
	
	

	
}
//
//unsigned int count(unsigned int i){
	//unsigned int ret = 1;
	//while(i/=10) ret++;
	//return ret;
//}