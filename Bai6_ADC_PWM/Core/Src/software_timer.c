/*
 * software_timer.c
 *
 *  Created on: Sep 24, 2023
 *      Author: HaHuyen
 */

#include "software_timer.h"

uint16_t flag_timer[N0_OF_TIMER] = {0, 0, 0, 0};
uint16_t timer_counter[N0_OF_TIMER] = {0, 0, 0, 0};

void timer_init(){
	HAL_TIM_Base_Start_IT(&htim2);
}

void setTimer(uint16_t duration, uint16_t timer_type){
	timer_counter[timer_type] = duration/TIMER_CYCLE;
	flag_timer[timer_type] = 0;
}

void timerRun(uint16_t timer_type){
	if(timer_counter[timer_type] > 0){
		timer_counter[timer_type]--;
		if(timer_counter[timer_type] <= 0){
			flag_timer[timer_type] = 1;
		}
	}
}

void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim){
	if(htim->Instance == TIM2){
		timerRun(LCD_TIMER);
		timerRun(LED7SEG_TIMER);
		timerRun(BUZZER_TIMER);
	}
}
