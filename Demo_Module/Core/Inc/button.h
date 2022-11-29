/*
 * button.h
 *
 *  Created on: Nov 28, 2022
 *      Author: Guest_demo
 */

#ifndef INC_BUTTON_H_
#define INC_BUTTON_H_

#define MAX_BUTTON	4

#define BTN_1	0
#define BTN_2	1
#define BTN_3	2
#define BTN_PD	3

void button_reading(void);
int button_isPressed(int index);
int button_isLongPressed(int index);
void subKeyProcess(int index);

#endif /* INC_BUTTON_H_ */
