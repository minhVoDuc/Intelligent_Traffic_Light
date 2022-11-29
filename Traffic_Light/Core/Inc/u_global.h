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

extern uint8_t global_state;
extern uint8_t auto_A_state;
extern uint8_t auto_B_state;
extern uint8_t manual_state;
extern uint8_t set_state;

#endif /* INC_U_GLOBAL_H_ */
