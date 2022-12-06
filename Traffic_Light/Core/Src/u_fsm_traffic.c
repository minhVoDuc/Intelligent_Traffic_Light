/*
 * u_traffic_fsm.c
 *
 *  Created on: 28 thg 11, 2022
 *      Author: Guest_demo
 */
#include <u_fsm_traffic.h>
#include "u_global.h"

/*-------------------- init setting --------------------*/
//uint32_t	trafficDuration[3] = {5000, 3000, 2000};
uint32_t traffic_prevDur = 0,
         traffic_currDur = 0; //previous and current duration of traffic

void traffic_init() {
	global_state = INIT_MODE;
	auto_A_state = AUTO_INIT;
	auto_B_state = AUTO_INIT;
	manual_state = MN_INIT;
	set_state = SET_INIT;
}

/*------------------- auto fsm -------------------------*/
void traffic_send_duration() {  //send duration to uart
	traffic_currDur = duration_get(DUR_TRAFFIC);
	if (traffic_currDur && traffic_currDur != traffic_prevDur) {
		uart_send_num("Traffic duration: ", traffic_currDur);
	}
	traffic_prevDur = traffic_currDur;
}

void traffic_auto_fsm_A() {
	switch(auto_A_state) {
	case AUTO_INIT:
		//change mode
		auto_A_state = AUTO_RED;
		timer_setDuration(TIMER_AUTO_A, trafficDuration[LED_RED]);
		duration_set(DUR_TRAFFIC, trafficDuration[LED_RED]);
		break;

	/////////////////////////////////////////////////////
	case AUTO_RED:
		//TODO
		led_turn_on(TRAFFIC_1, LED_RED);
		traffic_send_duration();

		//change mode
		if (timer_checkFlag(TIMER_AUTO_A)) { //change led
			auto_A_state = AUTO_GREEN;
			pd_active_state = PD_A_RED; //change pedestrian led to red
			timer_setDuration(TIMER_AUTO_A, trafficDuration[LED_GREEN]);
			duration_set(DUR_TRAFFIC, trafficDuration[LED_GREEN]);
		}
		break;

	/////////////////////////////////////////////////////
	case AUTO_GREEN:
		//TODO
		led_turn_on(TRAFFIC_1, LED_GREEN);
		traffic_send_duration();

		//change mode
		if (timer_checkFlag(TIMER_AUTO_A)) { //change led
			auto_A_state = AUTO_YELLOW;
			timer_setDuration(TIMER_AUTO_A, trafficDuration[LED_YELLOW]);
			duration_set(DUR_TRAFFIC, trafficDuration[LED_YELLOW]);
		}
		break;

	/////////////////////////////////////////////////////
	case AUTO_YELLOW:
		//TODO
		led_turn_on(TRAFFIC_1, LED_YELLOW);
		traffic_send_duration();

		//change mode
		if (timer_checkFlag(TIMER_AUTO_A)) { //change led
			auto_A_state = AUTO_RED;
			pd_active_state = PD_A_GREEN; //change pedestrian led to green
			timer_setDuration(TIMER_AUTO_A, trafficDuration[LED_RED]);
			duration_set(DUR_TRAFFIC, trafficDuration[LED_RED]);
		}
		break;

	/////////////////////////////////////////////////////
	default:
		break;
	}
}

void traffic_auto_fsm_B() {
	switch(auto_B_state) {
	case AUTO_INIT:
		//change mode
		auto_B_state = AUTO_GREEN;
		timer_setDuration(TIMER_AUTO_B, trafficDuration[LED_GREEN]);
		break;

	/////////////////////////////////////////////////////
	case AUTO_RED:
		//TODO
		led_turn_on(TRAFFIC_2, LED_RED);

		//change mode
		if (timer_checkFlag(TIMER_AUTO_B)) { //change led
			auto_B_state = AUTO_GREEN;
			timer_setDuration(TIMER_AUTO_B, trafficDuration[LED_GREEN]);
		}
		break;

	/////////////////////////////////////////////////////
	case AUTO_GREEN:
		//TODO
		led_turn_on(TRAFFIC_2, LED_GREEN);

		//change mode
		if (timer_checkFlag(TIMER_AUTO_B)) { //change led
			auto_B_state = AUTO_YELLOW;
			timer_setDuration(TIMER_AUTO_B, trafficDuration[LED_YELLOW]);
		}
		break;

	/////////////////////////////////////////////////////
	case AUTO_YELLOW:
		//TODO
		led_turn_on(TRAFFIC_2, LED_YELLOW);

		//change mode
		if (timer_checkFlag(TIMER_AUTO_B)) { //change led
			auto_B_state = AUTO_RED;
			timer_setDuration(TIMER_AUTO_B, trafficDuration[LED_RED]);
		}
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
		//change mode
		manual_state = MN_RED0;
		break;

	///////////////////////////////////////////////////////////
	// traffic A - red; traffic B - green
	case MN_RED0:
		//TODO
		led_turn_on(TRAFFIC_1, LED_RED);
		led_turn_on(TRAFFIC_2, LED_GREEN);

		//change mode
		if (button_isPressed(BTN_2)) { //when pressing button 2
			manual_state = MN_RED1;
		}
		break;

	///////////////////////////////////////////////////////////
	// traffic A - red; traffic B - yellow
	case MN_RED1:
		//TODO
		led_turn_on(TRAFFIC_1, LED_RED);
		led_turn_on(TRAFFIC_2, LED_YELLOW);

		//change mode
		if (button_isPressed(BTN_2)) { //when pressing button 2
			manual_state = MN_GREEN;
			pd_active_state = PD_A_RED; //change pedestrian led to red
		}
		break;

	///////////////////////////////////////////////////////////
	// traffic A - green; traffic B - red
	case MN_GREEN:
		//TODO
		led_turn_on(TRAFFIC_1, LED_GREEN);
		led_turn_on(TRAFFIC_2, LED_RED);

		//change mode
		if (button_isPressed(BTN_2)) { //when pressing button 2
			manual_state = MN_YELLOW;
		}
		break;

	///////////////////////////////////////////////////////////
	// traffic A - yellow; traffic B - red
	case MN_YELLOW:
		//TODO
		led_turn_on(TRAFFIC_1, LED_YELLOW);
		led_turn_on(TRAFFIC_2, LED_RED);

		//change mode
		if (button_isPressed(BTN_2)) { //when pressing button 2
			manual_state = MN_RED0;
			pd_active_state = PD_A_GREEN; //change pedestrian led to green
		}
		break;

	///////////////////////////////////////////////////////////
	default:
		break;
	}
}

/*-------------------- set fsm -------------------------*/
void duration_inc(uint8_t led_type) {
	// increase specific duration by 1 unit
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

	//////////////////////////////////////////////////////////////
	case SET_RED:
		//TODO
		led_turn_on(TRAFFIC_1, LED_RED);
		led_turn_on(TRAFFIC_2, LED_RED);
		//increase duration; max: 10000ms
		if (button_isPressed(BTN_3)) { //for one-pressed button
			duration_inc(LED_RED);
			timer_clear(TIMER_SET_LONG);
			timer_setDuration(TIMER_SET_LONG, 10); //set timer for long press
		}
		if (button_isLongPressed(BTN_3)) { //for long-pressed button
			if (timer_checkFlag(TIMER_SET_LONG)) {
				duration_inc(LED_RED);
				timer_setDuration(TIMER_SET_LONG, 500);
			}
		}

		//change led
		if (button_isPressed(BTN_2)) {
			set_state = SET_GREEN;
		}
		break;

	//////////////////////////////////////////////////////////////
	case SET_GREEN:
		//TODO
		led_turn_on(TRAFFIC_1, LED_GREEN);
		led_turn_on(TRAFFIC_2, LED_GREEN);
		//increase duration; max: 10000ms
		if (button_isPressed(BTN_3)) { //for one-pressed button
			duration_inc(LED_GREEN);
			timer_clear(TIMER_SET_LONG);
			timer_setDuration(TIMER_SET_LONG, 10); //set timer for long press
		}
		if (button_isLongPressed(BTN_3)) { //for long-pressed button
			if (timer_checkFlag(TIMER_SET_LONG)) {
				duration_inc(LED_GREEN);
				timer_setDuration(TIMER_SET_LONG, 500);
			}
		}

		//change led
		if (button_isPressed(BTN_2)){
			set_state = SET_YELLOW;
		}
		break;

	//////////////////////////////////////////////////////////////
	case SET_YELLOW:
		//TODO
		led_turn_on(TRAFFIC_1, LED_YELLOW);
		led_turn_on(TRAFFIC_2, LED_YELLOW);
		//increase duration; max: 10000ms
		if (button_isPressed(BTN_3)) { //for one-pressed button
			duration_inc(LED_YELLOW);
			timer_clear(TIMER_SET_LONG);
			timer_setDuration(TIMER_SET_LONG, 10); //set timer for long press
		}
		if (button_isLongPressed(BTN_3)) { //for long-pressed button
			if (timer_checkFlag(TIMER_SET_LONG)) {
				duration_inc(LED_YELLOW);
				timer_setDuration(TIMER_SET_LONG, 500);
			}
		}

		//change led
		if (button_isPressed(BTN_2)){
			set_state = SET_RED;
		}
		break;

	//////////////////////////////////////////////////////////////
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

	//////////////////////////////////////////////////////
	case AUTO_MODE: //automatically control traffic light
		//TODO
		traffic_auto_fsm_A();
		traffic_auto_fsm_B();

		//change mode
		if (button_isPressed(BTN_1)) { //when pressing button 1
			led_clear_all();
			global_state = MANUAL_MODE;
			duration_set(DUR_TRAFFIC, 0);
			switch (auto_A_state) { //manual mode with previous auto state
			case AUTO_RED: // traffic A = red
				switch (auto_B_state){
				case AUTO_GREEN: //traffic B = green
					manual_state = MN_RED0;
					break;
				case AUTO_YELLOW: //traffic B = yellow
					manual_state = MN_RED1;
					break;
				}
				break;
			case AUTO_GREEN: // traffic A = green
				manual_state = MN_GREEN;
				break;
			case AUTO_YELLOW: // traffic A = yellow
				manual_state = MN_YELLOW;
				break;
			}
		}
		break;

	////////////////////////////////////////////////////
	case MANUAL_MODE: // manually control traffic light
		//TODO
		traffic_manual_fsm();

		//change mode
		if (button_isPressed(BTN_1)) { //when pressing button 1
			global_state = SET_MODE;
			set_state = SET_INIT;
			led_clear_all();
		}
		break;

	//////////////////////////////////////////////////////
	case SET_MODE: //set duration for each led of traffic
		//TODO
		traffic_set_fsm();

		//change mode
		if (button_isPressed(BTN_1)) { //when pressing button 1
			global_state = AUTO_MODE;
			led_clear_all();
			timer_clear(TIMER_AUTO_A); //clear timer, prepare for auto mode
			timer_clear(TIMER_AUTO_B); //clear timer, prepare for auto mode
			switch(manual_state) { //auto mode with previous manual state
			///////////////////////////////////////////////////
			case MN_RED0: //traffic A: red; traffic B: green
				auto_A_state = AUTO_RED;
				timer_setDuration(TIMER_AUTO_A, trafficDuration[LED_RED]);
				duration_set(DUR_TRAFFIC, trafficDuration[LED_RED]);

				auto_B_state = AUTO_GREEN;
				timer_setDuration(TIMER_AUTO_B, trafficDuration[LED_GREEN]);
				break;
			///////////////////////////////////////////////////
			case MN_RED1: //traffic A: red; traffic B: yellow
				auto_A_state = AUTO_RED;
				timer_setDuration(TIMER_AUTO_A, trafficDuration[LED_YELLOW]);
				duration_set(DUR_TRAFFIC, trafficDuration[LED_YELLOW]);

				auto_B_state = AUTO_YELLOW;
				timer_setDuration(TIMER_AUTO_B, trafficDuration[LED_YELLOW]);
				break;

			///////////////////////////////////////////////////
			case MN_GREEN: //traffic A: green; traffic B: red
				auto_A_state = AUTO_GREEN;
				timer_setDuration(TIMER_AUTO_A, trafficDuration[LED_GREEN]);
				duration_set(DUR_TRAFFIC, trafficDuration[LED_GREEN]);

				auto_B_state = AUTO_RED;
				timer_setDuration(TIMER_AUTO_B, trafficDuration[LED_RED]);
				break;
			///////////////////////////////////////////////////
			case MN_YELLOW: //traffic A: yellow; traffic B: red
				auto_A_state = AUTO_YELLOW;
				timer_setDuration(TIMER_AUTO_A, trafficDuration[LED_YELLOW]);
				duration_set(DUR_TRAFFIC, trafficDuration[LED_YELLOW]);

				auto_B_state = AUTO_RED;
				timer_setDuration(TIMER_AUTO_B, trafficDuration[LED_YELLOW]);
				break;
			}
		}
		break;

	///////////////////////////////////////////////
	default:
		break;
	}
}
