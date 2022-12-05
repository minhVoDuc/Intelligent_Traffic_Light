/*
 * u_pedestrian_fsm.h
 *
 *  Created on: 2 thg 12, 2022
 *      Author: Guest_demo
 */

#ifndef INC_U_FSM_PEDESTRIAN_H_
#define INC_U_FSM_PEDESTRIAN_H_

#include <stdint.h>

//define for global pedestrian fsm
#define PD_INIT		50
#define PD_IDLE		51
#define PD_ACTIVE	52

//define duration for blink led
#define PD_DUR_BLINK	300

//for fsm
void pedestrian_init();
void pedestrian_fsm();
void pedestrian_active_fsm();

#endif /* INC_U_FSM_PEDESTRIAN_H_ */
