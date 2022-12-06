/*
 * u_fsm_pedestrian.c
 *
 *  Created on: 2 thg 12, 2022
 *      Author: Guest_demo
 */

#include "u_fsm_pedestrian.h"
#include "u_global.h"

// declare state for global fsm
uint8_t 	pd_state;
uint32_t	pd_duration = 0,
			pedestrian_prevDur = 0,
			pedestrian_currDur = 0;

// initialize suitable state for each mode
void pedestrian_init() {
	pd_state = PD_INIT;
	pd_active_state = PD_A_INIT;
}

void pedestrian_send_duration() { //send duration to uart
	pedestrian_currDur = duration_get(DUR_PEDESTRIAN);
	if (pedestrian_currDur != pedestrian_prevDur) {
		uart_send_num("Pedestrian duration: ", pedestrian_currDur);
	}
	pedestrian_prevDur = pedestrian_currDur;
}

void pedestrian_active_fsm() {
	pd_duration = global_get_totalDuration(); //get total duration
	if (timer_checkFlag(TIMER_BLINK)) { //check timer for blink led
		timer_setDuration(TIMER_BLINK, PD_DUR_BLINK);
		if (pd_led_state == PD_LED_OFF) {
			pd_led_state = PD_LED_ON;
			buzzer_state = BZ_ON;
		}
		else {
			pd_led_state = PD_LED_OFF;
			buzzer_state = BZ_OFF;
		}
	}

	switch (pd_active_state) {
	case PD_A_INIT:
		pd_active_state = PD_A_RED;
		break;

	///////////////////////////////////////////
	case PD_A_RED:
		//TODO
		pedestrian_send_duration();
		if (pedestrian_currDur > 3) led_turn_on(PEDESTRIAN, LED_RED); //turn led red on when duration over 3 second
		else {
			led_pedestrian_blinky(LED_RED); //otherwise, blink led red
			buzzer_blinky();
		}

		if (button_isPressed(BTN_PD)) { //reset duration for pedestrian led
			timer_clear(TIMER_PD);
			timer_setDuration(TIMER_PD, pd_duration);
			duration_set(DUR_PEDESTRIAN, pd_duration);
			buzzer_turn_off();
		}

		//change mode
		break;

	///////////////////////////////////////////
	case PD_A_GREEN:
		//TODO
		pedestrian_send_duration();
		if (pedestrian_currDur > 3) led_turn_on(PEDESTRIAN, LED_GREEN); //turn led green on when duration over 3 second
		else {
			led_pedestrian_blinky(LED_GREEN); //otherwise, blink led green
			buzzer_blinky();
		}

		if (button_isPressed(BTN_PD)) { //reset duration for pedestrian led
			timer_clear(TIMER_PD);
			timer_setDuration(TIMER_PD, pd_duration);
			duration_set(DUR_PEDESTRIAN, pd_duration);
			buzzer_turn_off();
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
		//change mode
		led_turn_off(PEDESTRIAN);
		pd_state = PD_IDLE;
		break;

	//////////////////////////////////////////////////////
	//pedestian led is not active
	case PD_IDLE:
		//TODO
		buzzer_turn_off();
		led_turn_off(PEDESTRIAN);

		//change mode
		if (button_isPressed(BTN_PD)) {
			pd_state = PD_ACTIVE;
			pd_duration = global_get_totalDuration(); //get total duration for a cycle of traffic
			timer_clear(TIMER_PD); //clear timer for pedestrian (if yes)
			timer_setDuration(TIMER_PD, pd_duration); //set new timer for pedestrian
			duration_set(DUR_PEDESTRIAN, pd_duration);//set duration for counter
			timer_clear(TIMER_BLINK);
			timer_setDuration(TIMER_BLINK, PD_DUR_BLINK); //set timer for blinking led for the last 3 second
		}
		break;

	//////////////////////////////////////////////////////
	//pedestrian led active in active mode
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
