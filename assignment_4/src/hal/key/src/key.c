/*
 * key.c
 *
 * Created: 23/04/2022 15.45.59
 *  Author: Jacob
 */ 

#include <stdlib.h>
#include "../include/key.h"

static io_descriptor_t keys[K_NO];

void key_init(io_definition_t io[])
{
	for (uint8_t i = 0; i < K_NO; i++)
	{
		keys[i] = input_init(io[i].port, io[i].pin, K_ACTIVE_STATE, K_PULL_UP_STATE, NULL);
	}
}

uint8_t key_get(uint8_t key_no)
{
	if((key_no >= 1) && (key_no <= 8))
	{
		key_no--;	// Convert key number to index
		
		return input_activated(keys[key_no]);
	}
	return 0;
}

uint8_t key_scan()
{
	for(uint8_t i = 1; i <= K_NO; i++)
	{
		if(key_get(i))
		{
			return i;
		}
	}
	return 0;
}

