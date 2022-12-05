/*
 * u_buzzer.h
 *
 *  Created on: Nov 26, 2022
 *      Author: Guest_demo
 */

#ifndef INC_U_I_BUZZER_H_
#define INC_U_I_BUZZER_H_

#include "main.h"

extern TIM_HandleTypeDef htim3;

void buzzer_modify_volume(uint8_t volumeLevel); //modify volume of buzzer at volumeLevel
void buzzer_turn_on(); //turn on buzzer
void buzzer_turn_off(); //turn off buzzer or volume = 0
void buzzer_blinky(); //buzzer turn on and off periodly

#endif /* INC_U_I_BUZZER_H_ */
