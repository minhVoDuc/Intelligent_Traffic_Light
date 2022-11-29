/*
 * u_timer.h
 *
 *  Created on: Nov 26, 2022
 *      Author: Guest_demo
 */

#ifndef INC_U_I_TIMER_H_
#define INC_U_I_TIMER_H_

#include <stdint.h>
#include <stdlib.h>

#define MAX_TIMER 	2
#define CYCLE		10 //TIM20 = 10ms ~ 100Hz

struct timer_unit {
	uint8_t				index;
	uint32_t 			duration;
	struct timer_unit 	*nextTimer;
};

struct timer_list {
	uint8_t				size;
	struct timer_unit	*head;
};

// define index for timer
#define TIMER_AUTO_A	0
#define TIMER_AUTO_B	1


//  unit function
struct timer_unit* timer_unit_construct(uint8_t index, uint32_t duration);
void timer_unit_destruct(struct timer_unit *unit);

//  list function
void timer_list_add(struct timer_unit *unit);
void timer_list_pop(); //delete head of list

//  global function
void timer_init();
void timer_run();
void timer_setDuration(uint8_t index, uint32_t duration);
uint8_t	timer_checkFlag(uint8_t index);
void timer_clear(uint8_t index);

#endif /* INC_U_I_TIMER_H_ */
