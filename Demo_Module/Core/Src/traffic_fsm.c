/*
 * traffic_fsm.c
 *
 *  Created on: Nov 28, 2022
 *      Author: Guest_demo
 */

#include "traffic_fsm.h"
#include "global.h"

/*-------------------- init setting --------------------*/
uint32_t	trafficDuration[3] = {2000, 1200, 800};

void traffic_init() {
	global_state = INIT_MODE;
	auto_A_state = AUTO_INIT;
	auto_B_state = AUTO_INIT;
	manual_state = MN_INIT;
	set_state = SET_INIT;
}

/*------------------- auto fsm -------------------------*/
void traffic_auto_fsm_A() {
	switch(auto_A_state) {
	case AUTO_INIT:
		auto_A_state = AUTO_RED;
		timer_setDuration(TIMER_AUTO_A, trafficDuration[LED_RED]);
		break;

	/////////////////////////////////////////////////////
	case AUTO_RED:
		if (timer_checkFlag(TIMER_AUTO_A)) { //change led
			auto_A_state = AUTO_GREEN;
			timer_setDuration(TIMER_AUTO_A, trafficDuration[LED_GREEN]);
		}

		led_turn_on(TRAFFIC_1, LED_RED);
		led_turn_off(TRAFFIC_1, LED_YELLOW);
		break;

	/////////////////////////////////////////////////////
	case AUTO_GREEN:
		if (timer_checkFlag(TIMER_AUTO_A)) { //change led
			auto_A_state = AUTO_YELLOW;
			timer_setDuration(TIMER_AUTO_A, trafficDuration[LED_YELLOW]);
		}

		led_turn_on(TRAFFIC_1, LED_GREEN);
		led_turn_off(TRAFFIC_1, LED_RED);
		break;

	/////////////////////////////////////////////////////
	case AUTO_YELLOW:
		if (timer_checkFlag(TIMER_AUTO_A)) { //change led
			auto_A_state = AUTO_RED;
			timer_setDuration(TIMER_AUTO_A, trafficDuration[LED_RED]);
		}

		led_turn_on(TRAFFIC_1, LED_YELLOW);
		led_turn_off(TRAFFIC_1, LED_GREEN);
		break;

	/////////////////////////////////////////////////////
	default:
		break;
	}
}

void traffic_auto_fsm_B() {
	switch(auto_B_state) {
	case AUTO_INIT:
		auto_B_state = AUTO_GREEN;
		timer_setDuration(TIMER_AUTO_B, trafficDuration[LED_GREEN]);
		break;

	/////////////////////////////////////////////////////
	case AUTO_RED:
		if (timer_checkFlag(TIMER_AUTO_B)) { //change led
			auto_B_state = AUTO_GREEN;
			timer_setDuration(TIMER_AUTO_B, trafficDuration[LED_GREEN]);
		}

		led_turn_on(TRAFFIC_2, LED_RED);
		led_turn_off(TRAFFIC_2, LED_YELLOW);
		break;

	/////////////////////////////////////////////////////
	case AUTO_GREEN:
		if (timer_checkFlag(TIMER_AUTO_B)) { //change led
			auto_B_state = AUTO_YELLOW;
			timer_setDuration(TIMER_AUTO_B, trafficDuration[LED_YELLOW]);
		}

		led_turn_on(TRAFFIC_2, LED_GREEN);
		led_turn_off(TRAFFIC_2, LED_RED);
		break;

	/////////////////////////////////////////////////////
	case AUTO_YELLOW:
		if (timer_checkFlag(TIMER_AUTO_B)) { //change led
			auto_B_state = AUTO_RED;
			timer_setDuration(TIMER_AUTO_B, trafficDuration[LED_RED]);
		}

		led_turn_on(TRAFFIC_2, LED_YELLOW);
		led_turn_off(TRAFFIC_2, LED_GREEN);
		break;

	/////////////////////////////////////////////////////
	default:
		break;
	}
}

/*----------------- manual fsm -------------------------*/
void traffic_manual_fsm() {
	switch(manual_state) {
	case MN_INIT:
		led_clear_all();
		manual_state = MN_RED0;
		break;

	///////////////////////////////////////////////////////////
	case MN_RED0:
		if (button_isPressed(BTN_2)) { //when pressing button 2
			manual_state = MN_RED1;
		}

		led_turn_off(TRAFFIC_1, LED_YELLOW);
		led_turn_off(TRAFFIC_2, LED_RED);
		led_turn_on(TRAFFIC_1, LED_RED);
		led_turn_on(TRAFFIC_2, LED_GREEN);
		break;

	///////////////////////////////////////////////////////////
	case MN_RED1:
		if (button_isPressed(BTN_2)) { //when pressing button 2
			manual_state = MN_GREEN;
		}

		led_turn_off(TRAFFIC_2, LED_GREEN);
		led_turn_on(TRAFFIC_1, LED_RED);
		led_turn_on(TRAFFIC_2, LED_YELLOW);
		break;

	///////////////////////////////////////////////////////////
	case MN_GREEN:
		if (button_isPressed(BTN_2)) { //when pressing button 2
			manual_state = MN_YELLOW;
		}

		led_turn_off(TRAFFIC_1, LED_RED);
		led_turn_off(TRAFFIC_2, LED_YELLOW);
		led_turn_on(TRAFFIC_1, LED_GREEN);
		led_turn_on(TRAFFIC_2, LED_RED);
		break;

	///////////////////////////////////////////////////////////
	case MN_YELLOW:
		if (button_isPressed(BTN_2)) { //when pressing button 2
			manual_state = MN_RED0;
		}

		led_turn_off(TRAFFIC_1, LED_GREEN);
		led_turn_on(TRAFFIC_1, LED_YELLOW);
		led_turn_on(TRAFFIC_2, LED_RED);
		break;

	///////////////////////////////////////////////////////////
	default:
		break;
	}
}

/*-------------------- set fsm -------------------------*/
void duration_inc(uint8_t led_type) {
	trafficDuration[led_type] += DURATION_UNIT;
	if (trafficDuration[led_type] > DURATION_MAX) { //if duration over max, reset to DURATION_UNIT
		trafficDuration[led_type] -= DURATION_MAX;
	}
}

void traffic_set_fsm() {
	switch(set_state) {
	case SET_INIT:
		set_state = SET_RED;
		break;
	case SET_RED:
		//change led
		if (button_isPressed(BTN_2)) {
			set_state = SET_GREEN;
		}
		//TODO
		led_turn_off(TRAFFIC_1, LED_YELLOW);
		led_turn_off(TRAFFIC_2, LED_YELLOW);
		led_turn_on(TRAFFIC_1, LED_RED);
		led_turn_on(TRAFFIC_2, LED_RED);
		//increase duration; max: 10000ms
		if (button_isPressed(BTN_3)) { //for one-pressed button
			duration_inc(LED_RED);
			timer_setDuration(TIMER_SET_LONG, 10); //set timer for long press
		}
		if (button_isLongPressed(BTN_3)) { //for long-pressed button
			if (timer_checkFlag(TIMER_SET_LONG)) {
				duration_inc(LED_RED);
				timer_setDuration(TIMER_SET_LONG, 500);
			}
		}
		else timer_clear(TIMER_SET_LONG);

		break;
	case SET_GREEN:
		//change led
		if (button_isPressed(BTN_2)){
			set_state = SET_YELLOW;
		}

		//TODO
		led_turn_off(TRAFFIC_1, LED_RED);
		led_turn_off(TRAFFIC_2, LED_RED);
		led_turn_on(TRAFFIC_1, LED_GREEN);
		led_turn_on(TRAFFIC_2, LED_GREEN);
		//increase duration; max: 10000ms
		if (button_isPressed(BTN_3)) { //for one-pressed button
			duration_inc(LED_GREEN);
			timer_setDuration(TIMER_SET_LONG, 10); //set timer for long press
		}
		if (button_isLongPressed(BTN_3)) { //for long-pressed button
			if (timer_checkFlag(TIMER_SET_LONG)) {
				duration_inc(LED_GREEN);
				timer_setDuration(TIMER_SET_LONG, 500);
			}
		}
		else timer_clear(TIMER_SET_LONG);

		break;
	case SET_YELLOW:
		//change led
		if (button_isPressed(BTN_2)){
			set_state = SET_RED;
		}

		//TODO
		led_turn_off(TRAFFIC_1, LED_GREEN);
		led_turn_off(TRAFFIC_2, LED_GREEN);
		led_turn_on(TRAFFIC_1, LED_YELLOW);
		led_turn_on(TRAFFIC_2, LED_YELLOW);
		//increase duration; max: 10000ms
		if (button_isPressed(BTN_3)) { //for one-pressed button
			duration_inc(LED_YELLOW);
			timer_setDuration(TIMER_SET_LONG, 10); //set timer for long press
		}
		if (button_isLongPressed(BTN_3)) { //for long-pressed button
			if (timer_checkFlag(TIMER_SET_LONG)) {
				duration_inc(LED_YELLOW);
				timer_setDuration(TIMER_SET_LONG, 500);
			}
		}
		else timer_clear(TIMER_SET_LONG);

		break;
	default:
		break;
	}
}

/*----------------- global fsm -------------------------*/
void traffic_fsm() {
	switch(global_state) {
	case INIT_MODE:
		led_clear_all();
		global_state = AUTO_MODE;
		break;

	///////////////////////////////////////////////
	case AUTO_MODE:
		//change mode
		if (button_isPressed(BTN_1)) { //when pressing button 1
			led_clear_all();
			global_state = MANUAL_MODE;
			switch (auto_A_state) { //manual mode with previous auto state
			case AUTO_RED:
				switch (auto_B_state){
				case AUTO_GREEN:
					manual_state = MN_RED0;
					break;
				case AUTO_YELLOW:
					manual_state = MN_RED1;
					break;
				}
				break;
			case AUTO_GREEN:
				manual_state = MN_GREEN;
				break;
			case AUTO_YELLOW:
				manual_state = MN_YELLOW;
				break;
			default:
				break;
			}
			return;
		}

		//TODO
		traffic_auto_fsm_A();
		traffic_auto_fsm_B();
		break;

	///////////////////////////////////////////////
	case MANUAL_MODE:
		//change mode
		if (button_isPressed(BTN_1)) { //when pressing button 1
			global_state = SET_MODE;
			set_state = SET_INIT;
			auto_A_state = AUTO_INIT;
			auto_B_state = AUTO_INIT;
			timer_clear(TIMER_AUTO_A);
			timer_clear(TIMER_AUTO_B);
			led_clear_all();
			return;
		}

		//TODO
		traffic_manual_fsm();
		break;

	///////////////////////////////////////////////
	case SET_MODE:
		//change mode
		if (button_isPressed(BTN_1)) { //when pressing button 1
			global_state = AUTO_MODE;
			led_clear_all();
//			switch(manual_state) { //auto mode with previous manual state
//			case MN_RED0:
//				auto_A_state = AUTO_RED;
//				timer_setDuration(TIMER_AUTO_A, trafficDuration[LED_RED]);
//				auto_B_state = AUTO_GREEN;
//				timer_setDuration(TIMER_AUTO_B, trafficDuration[LED_GREEN]);
//				break;
//			case MN_RED1:
//				auto_A_state = AUTO_RED;
//				timer_setDuration(TIMER_AUTO_A, trafficDuration[LED_YELLOW]);
//				auto_B_state = AUTO_YELLOW;
//				timer_setDuration(TIMER_AUTO_B, trafficDuration[LED_YELLOW]);
//				break;
//			case MN_GREEN:
//				auto_A_state = AUTO_GREEN;
//				timer_setDuration(TIMER_AUTO_A, trafficDuration[LED_GREEN]);
//				auto_B_state = AUTO_RED;
//				timer_setDuration(TIMER_AUTO_B, trafficDuration[LED_RED]);
//				break;
//			case MN_YELLOW:
//				auto_A_state = AUTO_YELLOW;
//				timer_setDuration(TIMER_AUTO_A, trafficDuration[LED_YELLOW]);
//				auto_B_state = AUTO_RED;
//				timer_setDuration(TIMER_AUTO_B, trafficDuration[LED_YELLOW]);
//				break;
//			}
			return;
		}

		//TODO
		traffic_set_fsm();
		break;

	///////////////////////////////////////////////
	default:
		break;
	}
}