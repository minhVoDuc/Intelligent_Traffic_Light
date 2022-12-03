/*
 * duration.c
 *
 *  Created on: Dec 2, 2022
 *      Author: Guest_demo
 */

#include "duration.h"
#include "global.h"

void duration_init() {
	timer_setDuration(TIMER_DUR, 10);
	durationList[0] = durationList[1] = 0; //0s
}
void duration_set(uint8_t index, uint32_t duration_ms) {
	durationList[index] = duration_ms / DUR_CYCLE; //unit of time: milisecond
}

uint32_t duration_get(uint8_t index) { //return value of duration in second (not in milisecond)
	uint32_t extra_duration = ((durationList[index] * DUR_CYCLE) % (DUR_UNIT)) ? 1 : 0;
	return (durationList[index] * DUR_CYCLE / DUR_UNIT) + extra_duration;
}

void duration_run() { //use timer interupt to auto increase
	durationList[0] = (durationList[0] == 0) ? 0 : durationList[0] - 1;
	durationList[1] = (durationList[1] == 0) ? 0 : durationList[1] - 1;
}
