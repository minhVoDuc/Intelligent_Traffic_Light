/*
 * traffic_fsm.h
 *
 *  Created on: Nov 28, 2022
 *      Author: Guest_demo
 */

#ifndef INC_TRAFFIC_FSM_H_
#define INC_TRAFFIC_FSM_H_

#include <stdint.h>

// for global fsm
#define INIT_MODE 	10
#define	AUTO_MODE	11
#define MANUAL_MODE	12
#define	SET_MODE	13

// for auto traffic fsm
#define AUTO_INIT 	20
#define	AUTO_RED	21
#define AUTO_GREEN	22
#define	AUTO_YELLOW	23

// for manual traffic fsm
#define MN_INIT 	30
#define	MN_RED0		31
#define MN_RED1		32
#define	MN_GREEN	33
#define MN_YELLOW	34

// for set traffic fsm
#define SET_INIT 	40
#define	SET_RED		41
#define SET_GREEN	42
#define	SET_YELLOW	43

// for traffic duration
#define DURATION_MAX	10000 //max duration = 10000ms ~ 10s
#define DURATION_UNIT	1000 //1000ms
void duration_inc(uint8_t led_type);

// for fsm
void traffic_init();
void traffic_fsm();
void traffic_auto_fsm_A();
void traffic_auto_fsm_B();
void traffic_manual_fsm();
void traffic_set_fsm();

#endif /* INC_TRAFFIC_FSM_H_ */
