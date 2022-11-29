/*
 * u_traffic_fsm.c
 *
 *  Created on: 28 thg 11, 2022
 *      Author: Guest_demo
 */
#include "u_traffic_fsm.h"
#include "u_global.h"

/*-------------------- init setting --------------------*/
uint32_t	trafficDuration[3] = {5000, 3000, 2000};

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
		break;

	/////////////////////////////////////////////////////
	case AUTO_GREEN:
		if (timer_checkFlag(TIMER_AUTO_A)) { //change led
			auto_A_state = AUTO_YELLOW;
			timer_setDuration(TIMER_AUTO_A, trafficDuration[LED_YELLOW]);
		}

		led_turn_on(TRAFFIC_1, LED_GREEN);
		break;

	/////////////////////////////////////////////////////
	case AUTO_YELLOW:
		if (timer_checkFlag(TIMER_AUTO_A)) { //change led
			auto_A_state = AUTO_RED;
			timer_setDuration(TIMER_AUTO_A, trafficDuration[LED_RED]);
		}

		led_turn_on(TRAFFIC_1, LED_YELLOW);
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
		break;

	/////////////////////////////////////////////////////
	case AUTO_GREEN:
		if (timer_checkFlag(TIMER_AUTO_B)) { //change led
			auto_B_state = AUTO_YELLOW;
			timer_setDuration(TIMER_AUTO_B, trafficDuration[LED_YELLOW]);
		}

		led_turn_on(TRAFFIC_2, LED_GREEN);
		break;

	/////////////////////////////////////////////////////
	case AUTO_YELLOW:
		if (timer_checkFlag(TIMER_AUTO_B)) { //change led
			auto_B_state = AUTO_RED;
			timer_setDuration(TIMER_AUTO_B, trafficDuration[LED_RED]);
		}

		led_turn_on(TRAFFIC_2, LED_YELLOW);
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
		manual_state = MN_RED0;
		break;

	///////////////////////////////////////////////////////////
	case MN_RED0:
		if (button_isPressed(BTN_2)) { //when pressing button 2
			manual_state = MN_RED1;
		}

		led_turn_on(TRAFFIC_1, LED_RED);
		led_turn_on(TRAFFIC_2, LED_GREEN);
		break;

	///////////////////////////////////////////////////////////
	case MN_RED1:
		if (button_isPressed(BTN_2)) { //when pressing button 2
			manual_state = MN_GREEN;
		}

//		led_turn_on(TRAFFIC_1, LED_RED);
		led_turn_on(TRAFFIC_2, LED_YELLOW);
		break;

	///////////////////////////////////////////////////////////
	case MN_GREEN:
		if (button_isPressed(BTN_2)) { //when pressing button 2
			manual_state = MN_YELLOW;
		}

		led_turn_on(TRAFFIC_1, LED_GREEN);
		led_turn_on(TRAFFIC_2, LED_RED);
		break;

	///////////////////////////////////////////////////////////
	case MN_YELLOW:
		if (button_isPressed(BTN_2)) { //when pressing button 2
			manual_state = MN_RED0;
		}

		led_turn_on(TRAFFIC_1, LED_YELLOW);
//		led_turn_on(TRAFFIC_2, LED_RED);
		break;

	///////////////////////////////////////////////////////////
	default:
		break;
	}
}

/*-------------------- set fsm -------------------------*/
void traffic_set_fsm() {
	switch(set_state) {
	case SET_INIT:
		set_state = SET_RED;
		break;
	case SET_RED:
		//change led
		if (button_isPressed(BTN_2)){
			set_state = SET_GREEN;
		}
		//TODO
		led_turn_on(TRAFFIC_1, LED_RED);
		led_turn_on(TRAFFIC_2, LED_RED);
		break;
	case SET_GREEN:
		//change led
		if (button_isPressed(BTN_2)){
			set_state = SET_YELLOW;
		}

		//TODO
		led_turn_on(TRAFFIC_1, LED_GREEN);
		led_turn_on(TRAFFIC_2, LED_GREEN);
		break;
	case SET_YELLOW:
		//change led
		if (button_isPressed(BTN_2)){
			set_state = SET_RED;
		}

		//TODO
		led_turn_on(TRAFFIC_1, LED_YELLOW);
		led_turn_on(TRAFFIC_2, LED_YELLOW);
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
//			auto_A_state = AUTO_INIT;
//			auto_B_state = AUTO_INIT;
//			timer_clear(TIMER_AUTO_A);
//			timer_clear(TIMER_AUTO_A);
			led_clear_all();
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
			timer_clear(TIMER_AUTO_A);
			timer_clear(TIMER_AUTO_B);
			switch(manual_state) { //auto mode with previous manual state
			case MN_RED0:
				auto_A_state = AUTO_RED;
				timer_setDuration(TIMER_AUTO_A, trafficDuration[LED_RED]);
				auto_B_state = AUTO_GREEN;
				timer_setDuration(TIMER_AUTO_B, trafficDuration[LED_GREEN]);
				break;
			case MN_RED1:
				auto_A_state = AUTO_RED;
				timer_setDuration(TIMER_AUTO_A, trafficDuration[LED_YELLOW]);
				auto_B_state = AUTO_YELLOW;
				timer_setDuration(TIMER_AUTO_B, trafficDuration[LED_YELLOW]);
				break;
			case MN_GREEN:
				auto_A_state = AUTO_GREEN;
				timer_setDuration(TIMER_AUTO_A, trafficDuration[LED_GREEN]);
				auto_B_state = AUTO_RED;
				timer_setDuration(TIMER_AUTO_B, trafficDuration[LED_RED]);
				break;
			case MN_YELLOW:
				auto_A_state = AUTO_YELLOW;
				timer_setDuration(TIMER_AUTO_A, trafficDuration[LED_YELLOW]);
				auto_B_state = AUTO_RED;
				timer_setDuration(TIMER_AUTO_B, trafficDuration[LED_YELLOW]);
				break;
			}
		}

		//TODO
		traffic_set_fsm();
		break;

	///////////////////////////////////////////////
	default:
		break;
	}
}
