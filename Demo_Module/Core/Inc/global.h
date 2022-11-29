/*
 * global.h
 *
 *  Created on: Nov 28, 2022
 *      Author: Guest_demo
 */

#ifndef INC_GLOBAL_H_
#define INC_GLOBAL_H_

#include <stdint.h>

#include "button.h"
//#include "buzzer.h"
#include "led.h"
#include "timer.h"

extern uint8_t global_state;
extern uint8_t auto_A_state;
extern uint8_t auto_B_state;
extern uint8_t manual_state;
extern uint8_t set_state;

#endif /* INC_GLOBAL_H_ */
