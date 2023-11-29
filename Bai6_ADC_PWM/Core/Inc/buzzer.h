/*
 * buzzer.h
 *
 *  Created on: Sep 26, 2023
 *      Author: HaHuyen
 */

#ifndef INC_BUZZER_H_
#define INC_BUZZER_H_

#include "tim.h"

extern uint8_t current_duty_cycle;
extern uint8_t buzzer_status;

void buzzer_init();
void buzzer_SetVolume(uint8_t _duty_cycle);

#endif /* INC_BUZZER_H_ */
