/*
 * u_buzzer.c
 *
 *  Created on: Nov 26, 2022
 *      Author: Guest_demo
 */

#include "u_i_buzzer.h"

TIM_HandleTypeDef htim3;

void buzzer_modify_volume(uint8_t volumeLevel) {
  __HAL_TIM_SetCompare(&htim3, TIM_CHANNEL_1, volumeLevel);
}

void buzzer_turn_on() {
	buzzer_modify_volume(100);
}

void buzzer_turn_off() {
	buzzer_modify_volume(0);
}

void buzzer_bliny() {
	if (buzzer_state == BZ_ON) buzzer_turn_on();
	else buzzer_turn_off();
}
