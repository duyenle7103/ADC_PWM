/*
 * software_timer.h
 *
 *  Created on: Sep 24, 2023
 *      Author: HaHuyen
 */

#ifndef INC_SOFTWARE_TIMER_H_
#define INC_SOFTWARE_TIMER_H_

#include "tim.h"

#define TIMER_CYCLE 1 // 1 milisecond
#define LED7SEG_PERIOD 5 // 5/1000 second
#define LCD_PERIOD 5 // 5/1000 second
#define UPDATE_PERIOD 1000 // 1000/1000 second
#define BUZZER_PERIOD 1000 // 1000/1000 second
#define DIAGRAM_PERIOD 1000 // 15000/1000 second
#define N0_OF_TIMER 5 // Number of timer be used

enum timer_type{LCD_TIMER, LED7SEG_TIMER, UPDATE_TIMER, BUZZER_TIMER, DIAGRAM_TIMER};

extern uint16_t flag_timer[N0_OF_TIMER];

void timer_init();
void setTimer(uint16_t duration, uint16_t timer_type);

#endif /* INC_SOFTWARE_TIMER_H_ */
