/*
 * u_timer.c
 *
 *  Created on: Nov 26, 2022
 *      Author: Guest_demo
 */

#include "u_i_timer.h"

struct timer_list timerList;
uint8_t	timerFlag[MAX_TIMER] = {0};

/*-------------- unit function -------------------*/
struct timer_unit* timer_unit_construct(uint8_t index, uint32_t duration) {
	struct timer_unit *newUnit = malloc(sizeof (struct timer_unit)); //dynamic allocating a timer unit
	if (newUnit == NULL) {
		return NULL;
	}
	newUnit->index = index;
	newUnit->duration = duration;
	newUnit->nextTimer = NULL;
	return newUnit;
}

void timer_unit_destruct(struct timer_unit *unit) {
	free(unit);
}

/*-------------- list function -------------------*/
void timer_list_add(struct timer_unit *unit){
	//list full
	if (timerList.size == MAX_TIMER) return;

	//list empty
	if (timerList.size == 0) {
		timerList.head = unit;
		timerList.size++;
		return;
	}

	//list has at least 1 item
	struct timer_unit *curr = timerList.head,
					  *prev = NULL;
	uint32_t totalDuration = 0;
	while(curr != NULL) { //iterating the list
		totalDuration += curr->duration;
		if (unit->duration < totalDuration) break;
		prev = curr;
		curr = curr->nextTimer;
	}
	if (prev == NULL) { //new unit is added before the head
		unit->nextTimer = curr;
		curr->duration -= unit->duration;
		timerList.head = unit;
		timerList.size++;
		return;
	}
	prev->nextTimer = unit;
	unit->nextTimer = curr;
	if (curr == NULL){
		unit->duration -= totalDuration;
	}
	else{
		unit->duration -= (totalDuration - prev->duration);
	}
	timerList.size++;
}

void timer_list_pop(){
	 //list empty
	if (timerList.size == 0) return;

	struct timer_unit *delUnit = timerList.head;
	timerList.head = delUnit->nextTimer;
	timer_unit_destruct(delUnit);
	timerList.size--;
}

/*-------------- global function -------------------*/
void timer_init(){
	timerList.head = NULL;
	timerList.size = 0;
}

void timer_run(){
	if (timerList.size == 0) return;
	if (timerList.head->duration >= 0) {
		timerList.head->duration--;
		if (timerList.head->duration <= 0) {
			uint8_t index = 0;
			while(timerList.size && timerList.head->duration == 0) {
				index = timerList.head->index;
				timerFlag[index] = 1;
				timer_list_pop();
			}
		}
	}
}

void timer_setDuration(uint8_t index, uint32_t duration) {
	struct timer_unit *newUnit = timer_unit_construct(index, duration/CYCLE);
	timer_list_add(newUnit);
}

uint8_t	timer_checkFlag(uint8_t index) {
	if (timerFlag[index] == 1) {
		timerFlag[index] = 0;
		return 1;
	}
	return 0;
}
