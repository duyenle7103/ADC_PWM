/*
 * sensor.c
 *
 *  Created on: Sep 26, 2023
 *      Author: HaHuyen
 */

#include "sensor.h"

uint16_t adc_receive[5];

float Power = 0.0;
uint16_t Light = 0;
char* Light_intensity = "";
uint16_t Humidity = 0;

void sensor_init(){
	HAL_ADC_Start_DMA(&hadc1, (uint32_t*)adc_receive, 5);
}

void sensor_Read(){
	HAL_ADC_Start_DMA(&hadc1, (uint32_t*)adc_receive, 5);
}

uint16_t sensor_GetLight(){
	return adc_receive[LIGHT_INDEX];
}

uint16_t sensor_GetPotentiometer(){
	return adc_receive[POTENTIOMETER_INDEX];
}

float sensor_GetVoltage(){
	return ((float)adc_receive[VOLTAGE_INDEX]*3.3*12)/(4095*1.565);
}

float sensor_GetCurrent(){
	return (((float)adc_receive[CURRENT_INDEX]*3.3*1000)/(4095*0.647)-2.5)*5/2.5;
}

float sensor_GetTemperature(){
	return ((float)adc_receive[TEMPERATURE_INDEX]*330)/(4095);
}
