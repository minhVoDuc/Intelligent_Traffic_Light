/*
 * led.c
 *
 *  Created on: Nov 28, 2022
 *      Author: Guest_demo
 */

#include "led.h"
#include "main.h"

#ifdef BOARD
//clear all led
void led_clear_all() {
	  HAL_GPIO_WritePin(GPIOA, PD_LED_1_Pin|TR_LED_A_0_Pin, GPIO_PIN_SET);
	  HAL_GPIO_WritePin(GPIOB, PD_LED_0_Pin|TR_LED_A_1_Pin|TR_LED_B_1_Pin|TR_LED_B_0_Pin, GPIO_PIN_SET);
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
		case LED_YELLOW: //00
			HAL_GPIO_WritePin(GPIOA, TR_LED_A_0_Pin, GPIO_PIN_RESET);
			HAL_GPIO_WritePin(GPIOB, TR_LED_A_1_Pin, GPIO_PIN_RESET);
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
		case LED_YELLOW: //00
			HAL_GPIO_WritePin(GPIOB, TR_LED_B_0_Pin, GPIO_PIN_RESET);
			HAL_GPIO_WritePin(GPIOB, TR_LED_B_1_Pin, GPIO_PIN_RESET);
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
void led_clear_all() {
	HAL_GPIO_WritePin(GPIOA, RED_0_Pin|GREEN_0_Pin|YELLOW_0_Pin|
			  	  	  	  	 RED_1_Pin|GREEN_1_Pin|YELLOW_1_Pin|
							 PD_RED_Pin|PD_GREEN_Pin, GPIO_PIN_SET);
}

void led_turn_on(uint8_t led_index, uint8_t led_type) {
	switch (led_index) {
	case TRAFFIC_1:
		switch (led_type) {
		case LED_RED: //01
			HAL_GPIO_WritePin(GPIOA, RED_0_Pin, GPIO_PIN_RESET);
			HAL_GPIO_WritePin(GPIOA, GREEN_0_Pin, GPIO_PIN_SET);
			HAL_GPIO_WritePin(GPIOA, YELLOW_0_Pin, GPIO_PIN_SET);
			break;
		case LED_GREEN: //10
			HAL_GPIO_WritePin(GPIOA, GREEN_0_Pin, GPIO_PIN_RESET);
			HAL_GPIO_WritePin(GPIOA, RED_0_Pin, GPIO_PIN_SET);
			HAL_GPIO_WritePin(GPIOA, YELLOW_0_Pin, GPIO_PIN_SET);
			break;
		case LED_YELLOW: //00
			HAL_GPIO_WritePin(GPIOA, YELLOW_0_Pin, GPIO_PIN_RESET);
			HAL_GPIO_WritePin(GPIOA, GREEN_0_Pin, GPIO_PIN_SET);
			HAL_GPIO_WritePin(GPIOA, RED_0_Pin, GPIO_PIN_SET);
			break;
		}
		break;
	//////////////////////////////////////////////////////////////////
	case TRAFFIC_2:
		switch (led_type) {
		case LED_RED: //01
			HAL_GPIO_WritePin(GPIOA, RED_1_Pin, GPIO_PIN_RESET);
			HAL_GPIO_WritePin(GPIOA, GREEN_1_Pin, GPIO_PIN_SET);
			HAL_GPIO_WritePin(GPIOA, YELLOW_1_Pin, GPIO_PIN_SET);
			break;
		case LED_GREEN: //10
			HAL_GPIO_WritePin(GPIOA, GREEN_1_Pin, GPIO_PIN_RESET);
			HAL_GPIO_WritePin(GPIOA, RED_1_Pin, GPIO_PIN_SET);
			HAL_GPIO_WritePin(GPIOA, YELLOW_1_Pin, GPIO_PIN_SET);
			break;
		case LED_YELLOW: //00
			HAL_GPIO_WritePin(GPIOA, YELLOW_1_Pin, GPIO_PIN_RESET);
			HAL_GPIO_WritePin(GPIOA, RED_1_Pin, GPIO_PIN_SET);
			HAL_GPIO_WritePin(GPIOA, GREEN_1_Pin, GPIO_PIN_SET);
			break;
		}
		break;
	//////////////////////////////////////////////////////////////////
	case PEDESTRIAN:
		switch (led_type) {
		case LED_RED:
			HAL_GPIO_WritePin(GPIOB, PD_RED_Pin, GPIO_PIN_RESET);
			HAL_GPIO_WritePin(GPIOB, PD_GREEN_Pin, GPIO_PIN_SET);
			break;
		case LED_GREEN:
			HAL_GPIO_WritePin(GPIOB, PD_GREEN_Pin, GPIO_PIN_RESET);
			HAL_GPIO_WritePin(GPIOB, PD_RED_Pin, GPIO_PIN_SET);
			break;
		}
		break;
	//////////////////////////////////////////////////////////////////
	default:
		break;
	}
}

void led_turn_off(uint8_t led_index, uint8_t led_type) {
	switch (led_index) {
	case TRAFFIC_1:
		switch (led_type) {
		case LED_RED: //01
			HAL_GPIO_WritePin(GPIOA, RED_0_Pin, GPIO_PIN_SET);
			break;
		case LED_GREEN: //10
			HAL_GPIO_WritePin(GPIOA, GREEN_0_Pin, GPIO_PIN_SET);
			break;
		case LED_YELLOW: //00
			HAL_GPIO_WritePin(GPIOA, YELLOW_0_Pin, GPIO_PIN_SET);
			break;
		}
		break;
	//////////////////////////////////////////////////////////////////
	case TRAFFIC_2:
		switch (led_type) {
		case LED_RED: //01
			HAL_GPIO_WritePin(GPIOA, RED_1_Pin, GPIO_PIN_SET);
			break;
		case LED_GREEN: //10
			HAL_GPIO_WritePin(GPIOA, GREEN_1_Pin, GPIO_PIN_SET);
			break;
		case LED_YELLOW: //00
			HAL_GPIO_WritePin(GPIOA, YELLOW_1_Pin, GPIO_PIN_SET);
			break;
		}
		break;
	//////////////////////////////////////////////////////////////////
	case PEDESTRIAN:
		switch (led_type) {
		case LED_RED:
			HAL_GPIO_WritePin(GPIOB, PD_RED_Pin, GPIO_PIN_SET);
			break;
		case LED_GREEN:
			HAL_GPIO_WritePin(GPIOB, PD_GREEN_Pin, GPIO_PIN_SET);
			break;
		}
		break;
	//////////////////////////////////////////////////////////////////
	default:
		break;
	}
}
#endif
