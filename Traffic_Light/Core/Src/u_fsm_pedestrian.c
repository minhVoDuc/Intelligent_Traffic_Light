/*
 * u_fsm_pedestrian.c
 *
 *  Created on: 2 thg 12, 2022
 *      Author: Guest_demo
 */

#include "u_fsm_pedestrian.h"
#include "u_global.h"

// declare state for global fsm
uint8_t pd_state;

// initialize suitable state for each mode
void pedestrian_init() {
	pd_state = PD_INIT;
	pd_active_state = PD_A_INIT;
}

void pedestrian_active_fsm() {
	switch (pd_active_state) {
	case PD_A_INIT:
		pd_active_state = PD_A_RED;
		break;

	///////////////////////////////////////////
	case PD_A_RED:
		//TODO
		led_turn_on(PEDESTRIAN, LED_RED); //turn led red on

		if (button_isPressed(BTN_PD)) { //reset duration for pedestrian led
			timer_clear(TIMER_PD);
			timer_setDuration(TIMER_PD, global_get_totalDuration());
		}

		//change mode
		break;

	///////////////////////////////////////////
	case PD_A_GREEN:
		//TODO
		led_turn_on(PEDESTRIAN, LED_GREEN); //turn led green on

		if (button_isPressed(BTN_PD)) { //reset duration for pedestrian led
			timer_clear(TIMER_PD);
			timer_setDuration(TIMER_PD, global_get_totalDuration());
		}

		//change mode
		break;

	///////////////////////////////////////////
	default:
		break;
	}
}

void pedestrian_fsm() {
	//check state of pd_state
	switch (pd_state) {
	case PD_INIT:
		led_turn_off(PEDESTRIAN);
		pd_state = PD_IDLE;
		break;

	//////////////////////////////////////////////////////
	//pedestian led is not active
	case PD_IDLE:
		led_turn_off(PEDESTRIAN);

		if (button_isPressed(BTN_PD)) {
			pd_state = PD_ACTIVE;
			timer_clear(TIMER_PD);
			timer_setDuration(TIMER_PD, global_get_totalDuration());
		}
		break;

	//////////////////////////////////////////////////////
	//pedestrian led active in auto mode
	case PD_ACTIVE:
		//TODO
		pedestrian_active_fsm();

		//Change state
		if (timer_checkFlag(TIMER_PD)) {
			pd_state = PD_IDLE;
		}
		break;

	//////////////////////////////////////////////////////

	default:
		break;
	}
}
