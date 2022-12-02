/*
 * global.h
 *
 *  Created on: Nov 26, 2022
 *      Author: Guest_demo
 */

#ifndef INC_U_GLOBAL_H_
#define INC_U_GLOBAL_H_

#include <stdint.h>

#include "u_i_button.h"
#include "u_i_buzzer.h"
#include "u_i_led.h"
#include "u_i_timer.h"

//function for duration
extern uint32_t trafficDuration[3];
uint32_t global_get_totalDuration();

// state for traffic
extern uint8_t global_state;
extern uint8_t auto_A_state;
extern uint8_t auto_B_state;
extern uint8_t manual_state;
extern uint8_t set_state;

// state for pedestrian

//define for active pedestrian fsm
#define PD_A_INIT	60
#define PD_A_RED	61
#define PD_A_GREEN	62

extern uint8_t pd_active_state;

#endif /* INC_U_GLOBAL_H_ */
