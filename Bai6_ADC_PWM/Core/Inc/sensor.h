/*
 * sensor.h
 *
 *  Created on: Sep 26, 2023
 *      Author: HaHuyen
 */

#ifndef INC_SENSOR_H_
#define INC_SENSOR_H_

#include "adc.h"

#define LIGHT_INDEX 2
#define POTENTIOMETER_INDEX 3
#define VOLTAGE_INDEX 0
#define CURRENT_INDEX 1
#define TEMPERATURE_INDEX 4

extern float Power;
extern uint16_t Light;
extern char* Light_intensity;
extern uint16_t Humidity;

void sensor_init();
void sensor_Read();
uint16_t sensor_GetLight();
uint16_t sensor_GetPotentiometer();
float sensor_GetVoltage();
float sensor_GetCurrent();
float sensor_GetTemperature();

#endif /* INC_SENSOR_H_ */
