/*
 * u_buzzer.c
 *
 *  Created on: Nov 26, 2022
 *      Author: Guest_demo
 */

#include "u_i_buzzer.h"

uint8_t volume = 0;

void buzzer_modify_volume(uint8_t volumeLevel)
{
  volume = volumeLevel;
}

void buzzer_turn_on()
{
  __HAL_TIM_SetCompare(&htim3, TIM_CHANNEL_1, volume);
}

void buzzer_turn_off()
{
  __HAL_TIM_SetCompare(&htim3, TIM_CHANNEL_1, 0);
}
