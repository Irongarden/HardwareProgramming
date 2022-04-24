/*
 * pump.c
 *
 * Created: 23/04/2022 17.47.45
 *  Author: Jacob
 */ 

#include "../include/pump.h"

static io_descriptor_t pump;

void pump_init()
{
	pump = output_init(P_PORT, P_PIN, P_ACTIVE_STATE, P_DEFAULT_STATE);
}

return_code_t pump_start()
{
	return output_set_state(pump, ACTIVE);
}

return_code_t pump_stop()
{
	return output_set_state(pump, INACTIVE);
}