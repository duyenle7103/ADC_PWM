/*
 * buzzer.c
 *
 *  Created on: Sep 26, 2023
 *      Author: HaHuyen
 */

#include "buzzer.h"

uint8_t current_duty_cycle = 0;
uint8_t duty_cycle = 0;
uint8_t buzzer_status = 0;

void buzzer_init(){
	HAL_TIM_PWM_Start(&htim13, TIM_CHANNEL_1);
}

void buzzer_SetVolume(uint8_t _duty_cycle){
	duty_cycle = _duty_cycle;
	__HAL_TIM_SET_COMPARE(&htim13, TIM_CHANNEL_1, duty_cycle);
}
