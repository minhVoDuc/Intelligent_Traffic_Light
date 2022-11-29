/*
 * test_IO.c
 *
 *  Created on: Nov 29, 2022
 *      Author: Guest_demo
 */

#include "test_IO.h"
#include "global.h"
#include "main.h"

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

void test_timer() {
	if (timer_checkFlag(TIMER_AUTO_A)) {
		timer_setDuration(TIMER_AUTO_A, 5000);
		HAL_GPIO_TogglePin(GPIOA, GREEN_0_Pin);
	}
	if (timer_checkFlag(TIMER_AUTO_B)) {
		timer_setDuration(TIMER_AUTO_B, 2000);
		HAL_GPIO_TogglePin(GPIOA, YELLOW_0_Pin);
	}
}

void test_long_button(uint8_t index) {
	if (button_isPressed(BTN_3)) {
		led_turn_on(TRAFFIC_1, LED_RED);
		led_turn_off(TRAFFIC_1, LED_GREEN);
	}
	if (button_isLongPressed(BTN_3)) {
		led_turn_off(TRAFFIC_1, LED_RED);
		led_turn_on(TRAFFIC_1, LED_GREEN);
	}
}
