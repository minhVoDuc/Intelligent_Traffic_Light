/*
 * u_i_duration.h
 *
 *  Created on: Dec 3, 2022
 *      Author: Guest_demo
 */

#ifndef INC_U_I_DURATION_H_
#define INC_U_I_DURATION_H_

#include <stdint.h>

// for index
#define DUR_TRAFFIC		0
#define	DUR_PEDESTRIAN	1

// for duration unit
#define DUR_UNIT	1000
#define DUR_CYCLE	10

uint32_t durationList[2]; //traffic = List[0]; pedestrian = List[1]

void duration_init();
void duration_set(uint8_t index, uint32_t duration_ms); //set value for spec. object (traffic || pedestrian)
uint32_t duration_get(uint8_t index); //get value of spec. object (traffic || pedestrian)
void duration_run(); //auto decrease value of duration per second

#endif /* INC_U_I_DURATION_H_ */
