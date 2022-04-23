/*
 * key.c
 *
 * Created: 20/02/2022 11.13.58
 */ 

#include <avr/io.h>
#include "../include/key.h"

void init_keys()
{
	/*
	* Setting data direction.
	* Only setting PC0 to PC5 as input on Port C.
	* Only setting PD2 and PD3 as input on Port D.
	*/
	DDRC &= ~(_BV(PC0) | _BV(PC1) | _BV(PC2) | _BV(PC3) | _BV(PC4) | _BV(PC5));
	DDRD &= ~(_BV(PD2) | _BV(PD3));
	
	/*
	* Setting pull up resistor.
	* Only setting PC0 to PC5 as input on Port C.
	* Only setting PD2 and PD3 as input on Port D.
	*/
	PORTC |= _BV(PC0) | _BV(PC1) | _BV(PC2) | _BV(PC3) | _BV(PC4) | _BV(PC5);
	PORTD |= _BV(PD2) | _BV(PD3);
}

/*
* Check current state.
* If 0 then key is pressed and returns a 1.
* Assignment specifies key numbers 1-8.
* Subtracting 1 from the key numbers <= 6 mapping them to port C 0-5.
* Subtracting 5 from the key numbers > 6 mapping them to port D 2 and 3.
*/
uint8_t get_key(uint8_t key_no)
{
	if (key_no > 0 && key_no < 9)
	{
		if (key_no <= 6) 
		{
			// Port C.
			return ((PINC & _BV(key_no - 1)) == 0);
		}
		else 
		{
			// port D.
			return ((PIND & _BV(key_no - 5)) == 0);
		}
	}
	return 0;
}

/*
* Iterates keys, returns number of first found key 1-8.
*/
uint8_t scan_key()
{
	for(uint8_t i = 0; i < 8; i++)
	{
		if (get_key(i + 1) == 1)
		{
			return i + 1;
		}
	}
	return 0;
}