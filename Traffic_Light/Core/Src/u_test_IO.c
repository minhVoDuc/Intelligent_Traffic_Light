/*
 * u_test_IO.c
 *
 *  Created on: Nov 29, 2022
 *      Author: Guest_demo
 */

#include "u_test_IO.h"
#include "u_global.h"
#include "main.h"

void test_button() {
	if (button_isPressed(BTN_1)) {
	  buzzer_turn_on();
	  led_turn_on(TRAFFIC_1, LED_RED);
	  led_turn_on(TRAFFIC_2, LED_RED);
	}
	if (button_isPressed(BTN_2)) {
	  buzzer_turn_off();
	  led_turn_on(TRAFFIC_1, LED_GREEN);
	  led_turn_on(TRAFFIC_2, LED_GREEN);
	}
	if (button_isPressed(BTN_3)) {
	  buzzer_turn_on();
	  led_turn_on(TRAFFIC_1, LED_YELLOW);
	  led_turn_on(TRAFFIC_2, LED_YELLOW);
	}
	if (button_isPressed(BTN_PD)) {
	  buzzer_turn_off();
	  led_turn_on(PEDESTRIAN, LED_RED);
	}
}

void test_pd() {
	if (button_isPressed(BTN_1)) {
		led_turn_on(PEDESTRIAN, LED_RED);
		buzzer_turn_on();
	}
}

void test_buzzer() {
	buzzer_turn_on();
	HAL_Delay(1000);
	buzzer_turn_off();
	HAL_Delay(1000);
}
