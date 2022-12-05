/*
 * u_buzzer.h
 *
 *  Created on: Nov 26, 2022
 *      Author: Guest_demo
 */

#ifndef INC_U_I_BUZZER_H_
#define INC_U_I_BUZZER_H_

#include "main.h"

void buzzer_modify_volume(uint8_t volumeLevel); //chỉnh volume buzzer ở mức volumeLevel
void buzzer_turn_on(); //mo buzzer
void buzzer_turn_off(); //tắt buzzer hay volume = 0

#endif /* INC_U_I_BUZZER_H_ */
