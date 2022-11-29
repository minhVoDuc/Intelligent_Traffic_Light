/*
 * u_test_IO.c
 *
 *  Created on: Nov 29, 2022
 *      Author: Guest_demo
 */

#include "u_test_IO.h"
#include "u_global.h"

void test_button() {
	if (button_isPressed(BTN_1)) {
	  led_turn_on(TRAFFIC_1, LED_RED);
	  led_turn_on(TRAFFIC_2, LED_RED);
	}
	if (button_isPressed(BTN_2)) {
	  led_turn_on(TRAFFIC_1, LED_GREEN);
	  led_turn_on(TRAFFIC_2, LED_GREEN);
	}
	if (button_isPressed(BTN_3)) {
	  led_turn_on(TRAFFIC_1, LED_YELLOW);
	  led_turn_on(TRAFFIC_2, LED_YELLOW);
	}
}
