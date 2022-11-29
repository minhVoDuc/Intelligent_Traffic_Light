/*
 * u_led.h
 *
 *  Created on: Nov 26, 2022
 *      Author: Guest_demo
 */

#ifndef INC_U_I_LED_H_
#define INC_U_I_LED_H_

#include <stdint.h>

#define BOARD

#define	TRAFFIC_1	5
#define	TRAFFIC_2	6
#define PEDESTRIAN	7

#define LED_RED		0
#define	LED_GREEN 	1
#define LED_YELLOW	2

#ifdef BOARD
void led_clear_all();
void led_turn_on(uint8_t led_index, uint8_t led_type);
void led_turn_off(uint8_t led_index);
#endif

#ifdef PROTEUS
void led_clear_all();
void led_turn_on(uint8_t led_index);
void led_turn_off(uint8_t led_index);
#endif

#endif /* INC_U_I_LED_H_ */
