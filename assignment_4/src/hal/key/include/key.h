/*
 * key.h
 *
 * Created: 23/04/2022 15.45.38
 *  Author: Jacob
 */ 


#ifndef KEY_H_
#define KEY_H_

#include "../../digital_input/include/digital_input.h"
#include "../../../include/definitions.h"
#include "../../hal_definitions.h"

#define K_NO			NO_INPUT_KEYS
#define K_PULL_UP_STATE	KEY_PULL_UP
#define K_ACTIVE_STATE	KEY_ACTIVE_STATE

/**
* Initializes keys without callback. 
**/
void key_init(io_definition_t io[]);
uint8_t key_get(uint8_t key_no);
uint8_t key_scan();

#endif /* KEY_H_ */