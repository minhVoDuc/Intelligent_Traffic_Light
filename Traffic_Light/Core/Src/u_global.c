/*
 * u_global.c
 *
 *  Created on: Nov 26, 2022
 *      Author: Guest_demo
 */

#include "u_global.h"

// initialize state for traffic
uint8_t global_state 	= 0;
uint8_t auto_A_state 	= 0;
uint8_t auto_B_state 	= 0;
uint8_t	manual_state 	= 0;
uint8_t set_state 		= 0;

// initialize state for traffic
uint8_t pd_active_state = 0;

//function for duration
uint32_t trafficDuration[3] = {5000, 3000, 2000};

uint32_t global_get_totalDuration() {
	return trafficDuration[0] + trafficDuration[1] + trafficDuration[2];
}
