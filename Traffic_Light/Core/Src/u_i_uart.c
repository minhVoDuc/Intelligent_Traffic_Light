/*
 * u_i_uart.c
 *
 *  Created on: Dec 3, 2022
 *      Author: Guest_demo
 */

#include "u_i_uart.h"

UART_HandleTypeDef huart2;

void uart_init() {
	sprintf(tx_data, "HELLO!\r\n");
	HAL_UART_Transmit(&huart2, &tx_data, sizeof(tx_data), 1000);
	HAL_UART_Receive_IT(&huart2, &rx_data, 1);
}

void uart_send_str(char str[]) {
	sprintf(tx_data, "%s\r\n", str);
	HAL_UART_Transmit(&huart2, tx_data, sizeof(tx_data), 1000);
	HAL_UART_Receive_IT(&huart2, &rx_data, 1);
}

void uart_send_num(char str[], uint32_t data) {
	sprintf(tx_data, "%s%ld\r\n", str, data);
	HAL_UART_Transmit(&huart2, tx_data, sizeof(tx_data), 1000);
	HAL_UART_Receive_IT(&huart2, &rx_data, 1);
}
