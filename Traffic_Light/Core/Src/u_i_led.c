/*
 * u_i_led.c
 *
 *  Created on: Nov 26, 2022
 *      Author: Guest_demo
 */

#include "u_i_led.h"
#include "main.h"

#ifdef BOARD
//clear all led
void led_clear_all() {
	HAL_GPIO_WritePin(GPIOA, PD_LED_1_Pin|TR_LED_A_0_Pin, GPIO_PIN_RESET);
	HAL_GPIO_WritePin(GPIOB, PD_LED_0_Pin|TR_LED_A_1_Pin|TR_LED_B_1_Pin|TR_LED_B_0_Pin, GPIO_PIN_RESET);
}

//turn specific led with specific color
void led_turn_on(uint8_t led_index, uint8_t led_type) {
	switch (led_index) {
	case TRAFFIC_1:
		switch (led_type) {
		case LED_RED: //01
			HAL_GPIO_WritePin(GPIOA, TR_LED_A_0_Pin, GPIO_PIN_SET);
			HAL_GPIO_WritePin(GPIOB, TR_LED_A_1_Pin, GPIO_PIN_RESET);
			break;
		case LED_GREEN: //10
			HAL_GPIO_WritePin(GPIOA, TR_LED_A_0_Pin, GPIO_PIN_RESET);
			HAL_GPIO_WritePin(GPIOB, TR_LED_A_1_Pin, GPIO_PIN_SET);
			break;
		case LED_YELLOW: //11
			HAL_GPIO_WritePin(GPIOA, TR_LED_A_0_Pin, GPIO_PIN_SET);
			HAL_GPIO_WritePin(GPIOB, TR_LED_A_1_Pin, GPIO_PIN_SET);
			break;
		}
		break;
	//////////////////////////////////////////////////////////////////
	case TRAFFIC_2:
		switch (led_type) {
		case LED_RED: //01
			HAL_GPIO_WritePin(GPIOB, TR_LED_B_0_Pin, GPIO_PIN_SET);
			HAL_GPIO_WritePin(GPIOB, TR_LED_B_1_Pin, GPIO_PIN_RESET);
			break;
		case LED_GREEN: //10
			HAL_GPIO_WritePin(GPIOB, TR_LED_B_0_Pin, GPIO_PIN_RESET);
			HAL_GPIO_WritePin(GPIOB, TR_LED_B_1_Pin, GPIO_PIN_SET);
			break;
		case LED_YELLOW: //11
			HAL_GPIO_WritePin(GPIOB, TR_LED_B_0_Pin, GPIO_PIN_SET);
			HAL_GPIO_WritePin(GPIOB, TR_LED_B_1_Pin, GPIO_PIN_SET);
			break;
		}
		break;
	//////////////////////////////////////////////////////////////////
	case PEDESTRIAN:
		switch (led_type) {
		case LED_RED: //01
			HAL_GPIO_WritePin(GPIOB, PD_LED_0_Pin, GPIO_PIN_SET);
			HAL_GPIO_WritePin(GPIOA, PD_LED_1_Pin, GPIO_PIN_RESET);
			break;
		case LED_GREEN: //10
			HAL_GPIO_WritePin(GPIOB, PD_LED_0_Pin, GPIO_PIN_RESET);
			HAL_GPIO_WritePin(GPIOA, PD_LED_1_Pin, GPIO_PIN_SET);
			break;
		case LED_YELLOW: //00
			HAL_GPIO_WritePin(GPIOB, PD_LED_0_Pin, GPIO_PIN_RESET);
			HAL_GPIO_WritePin(GPIOA, PD_LED_1_Pin, GPIO_PIN_RESET);
			break;
		}
		break;
	//////////////////////////////////////////////////////////////////
	default:
		break;
	}
}

//turn of specific led
void led_turn_off(uint8_t led_index) {
	switch (led_index) {
	case TRAFFIC_1:
		HAL_GPIO_WritePin(GPIOA, TR_LED_A_0_Pin, GPIO_PIN_SET);
		HAL_GPIO_WritePin(GPIOB, TR_LED_A_1_Pin, GPIO_PIN_SET);
		break;
	//////////////////////////////////////////////////////////////////
	case TRAFFIC_2:
		HAL_GPIO_WritePin(GPIOB, TR_LED_B_0_Pin, GPIO_PIN_SET);
		HAL_GPIO_WritePin(GPIOB, TR_LED_B_1_Pin, GPIO_PIN_SET);
		break;
	//////////////////////////////////////////////////////////////////
	case PEDESTRIAN:
		HAL_GPIO_WritePin(GPIOB, PD_LED_0_Pin, GPIO_PIN_SET);
		HAL_GPIO_WritePin(GPIOA, PD_LED_1_Pin, GPIO_PIN_SET);
		break;
	//////////////////////////////////////////////////////////////////
	default:
		break;
	}
}
#endif

#ifdef PROTEUS
void led_clear_all();
void led_turn_on(uint8_t led_index);
void led_turn_off(uint8_t led_index);
#endif
