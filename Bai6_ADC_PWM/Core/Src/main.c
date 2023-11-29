/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.c
  * @brief          : Main program body
  ******************************************************************************
  * @attention
  *
  * <h2><center>&copy; Copyright (c) 2023 STMicroelectronics.
  * All rights reserved.</center></h2>
  *
  * This software component is licensed by ST under BSD 3-Clause license,
  * the "License"; You may not use this file except in compliance with the
  * License. You may obtain a copy of the License at:
  *                        opensource.org/licenses/BSD-3-Clause
  *
  ******************************************************************************
  */
/* USER CODE END Header */
/* Includes ------------------------------------------------------------------*/
#include "main.h"
#include "adc.h"
#include "dma.h"
#include "i2c.h"
#include "spi.h"
#include "tim.h"
#include "gpio.h"
#include "fsmc.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */
#include "software_timer.h"
#include "led_7seg.h"
#include "button.h"
#include "lcd.h"
#include "picture.h"
#include "ds3231.h"
#include "sensor.h"
#include "buzzer.h"
/* USER CODE END Includes */

/* Private typedef -----------------------------------------------------------*/
/* USER CODE BEGIN PTD */

/* USER CODE END PTD */

/* Private define ------------------------------------------------------------*/
/* USER CODE BEGIN PD */

/* USER CODE END PD */

/* Private macro -------------------------------------------------------------*/
/* USER CODE BEGIN PM */

/* USER CODE END PM */

/* Private variables ---------------------------------------------------------*/

/* USER CODE BEGIN PV */
uint16_t Point[19][2];
/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);
/* USER CODE BEGIN PFP */
void system_init();
void button_Update();
void adc_Display();
void led7_Update();
void adc_Update();
void buzzer_Sound(uint8_t _buzzer_status);
void diagram_display();
/* USER CODE END PFP */

/* Private user code ---------------------------------------------------------*/
/* USER CODE BEGIN 0 */

/* USER CODE END 0 */

/**
  * @brief  The application entry point.
  * @retval int
  */
int main(void)
{
  /* USER CODE BEGIN 1 */

  /* USER CODE END 1 */

  /* MCU Configuration--------------------------------------------------------*/

  /* Reset of all peripherals, Initializes the Flash interface and the Systick. */
  HAL_Init();

  /* USER CODE BEGIN Init */

  /* USER CODE END Init */

  /* Configure the system clock */
  SystemClock_Config();

  /* USER CODE BEGIN SysInit */

  /* USER CODE END SysInit */

  /* Initialize all configured peripherals */
  MX_GPIO_Init();
  MX_DMA_Init();
  MX_SPI1_Init();
  MX_FSMC_Init();
  MX_I2C1_Init();
  MX_TIM13_Init();
  MX_TIM2_Init();
  MX_ADC1_Init();
  /* USER CODE BEGIN 2 */
  system_init();
  /* USER CODE END 2 */

  /* Infinite loop */
  /* USER CODE BEGIN WHILE */
  while (1)
  {
	  if(flag_timer[LED7SEG_TIMER] == 1){
		  setTimer(LED7SEG_PERIOD, LED7SEG_TIMER);
		  led7_Scan();
		  led7_SetColon(colon_status = 1 - colon_status);
	  }
	  if(flag_timer[LCD_TIMER] == 1){
		  setTimer(LCD_PERIOD, LCD_TIMER);
		  button_Update();
		  adc_Display();
		  diagram_display();
	  }
	  if(flag_timer[UPDATE_TIMER] == 1){
		  setTimer(UPDATE_PERIOD, UPDATE_TIMER);
		  led7_Update();
		  adc_Update();
	  }
	  if(flag_timer[BUZZER_TIMER] == 1){
		  setTimer(BUZZER_PERIOD, BUZZER_TIMER);
		  if(Humidity > 70){
			  buzzer_Sound(buzzer_status = 1 - buzzer_status);
		  }else{
			  buzzer_Sound(0);
		  }
	  }
	  if(flag_timer[DIAGRAM_TIMER] == 1){
		  setTimer(DIAGRAM_PERIOD, DIAGRAM_TIMER);
		  lcd_Clear(WHITE);
		  for(int i = 18; i > 0; i--){
			  Point[i][0] = Point[i - 1][0] + 10;
			  Point[i][1] = Point[i - 1][1];
		  }
		  Point[0][0] = 10;
		  Point[0][1] = 300 - Power/2.0;
	  }
    /* USER CODE END WHILE */

    /* USER CODE BEGIN 3 */
  }
  /* USER CODE END 3 */
}

/**
  * @brief System Clock Configuration
  * @retval None
  */
void SystemClock_Config(void)
{
  RCC_OscInitTypeDef RCC_OscInitStruct = {0};
  RCC_ClkInitTypeDef RCC_ClkInitStruct = {0};

  /** Configure the main internal regulator output voltage
  */
  __HAL_RCC_PWR_CLK_ENABLE();
  __HAL_PWR_VOLTAGESCALING_CONFIG(PWR_REGULATOR_VOLTAGE_SCALE1);
  /** Initializes the RCC Oscillators according to the specified parameters
  * in the RCC_OscInitTypeDef structure.
  */
  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSI;
  RCC_OscInitStruct.HSIState = RCC_HSI_ON;
  RCC_OscInitStruct.HSICalibrationValue = RCC_HSICALIBRATION_DEFAULT;
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON;
  RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_HSI;
  RCC_OscInitStruct.PLL.PLLM = 8;
  RCC_OscInitStruct.PLL.PLLN = 168;
  RCC_OscInitStruct.PLL.PLLP = RCC_PLLP_DIV2;
  RCC_OscInitStruct.PLL.PLLQ = 4;
  if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK)
  {
    Error_Handler();
  }
  /** Initializes the CPU, AHB and APB buses clocks
  */
  RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK|RCC_CLOCKTYPE_SYSCLK
                              |RCC_CLOCKTYPE_PCLK1|RCC_CLOCKTYPE_PCLK2;
  RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_PLLCLK;
  RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
  RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV4;
  RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV4;

  if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_5) != HAL_OK)
  {
    Error_Handler();
  }
}

/* USER CODE BEGIN 4 */
void point_init(){
	for(int i = 0; i < 19; i++){
		Point[i][0] = 10;
		Point[i][1] = 300;
	}
}

void system_init(){
	timer_init();
	ds3231_init();
	button_init();
	lcd_init();
	sensor_init();
	buzzer_init();
	led7_init();
	point_init();
	setTimer(LCD_PERIOD, LCD_TIMER);
	setTimer(LED7SEG_PERIOD, LED7SEG_TIMER);
	setTimer(UPDATE_PERIOD, UPDATE_TIMER);
	setTimer(BUZZER_PERIOD, BUZZER_TIMER);
	setTimer(DIAGRAM_PERIOD, DIAGRAM_TIMER);
}

void button_Update(){
	button_Scan();
	if(isButtonUp()){
		current_duty_cycle = (current_duty_cycle + 1)%100;
	}
	if(isButtonDown()){
		if(current_duty_cycle > 0){
			current_duty_cycle = (current_duty_cycle - 1)%100;
		}
	}
}

void adc_Display(){
	lcd_ShowStr(10, 10, "Duty cycle:", RED, WHITE, 16, 0);
	lcd_ShowIntNum(130, 10, current_duty_cycle, 2, RED, WHITE, 16);
	lcd_ShowStr(200, 10, "(%)", RED, WHITE, 16, 0);

	lcd_ShowStr(10, 30, "Power:", RED, WHITE, 16, 0);
	lcd_ShowFloatNum(130, 30, Power, 5, RED, WHITE, 16);
	lcd_ShowStr(200, 30, "(mW)", RED, WHITE, 16, 0);

	lcd_ShowStr(10, 50, "Light:", RED, WHITE, 16, 0);
	lcd_ShowStr(130, 50, Light_intensity, RED, WHITE, 16, 0);

	lcd_ShowStr(10, 70, "Temperature:", RED, WHITE, 16, 0);
	lcd_ShowFloatNum(130, 70, sensor_GetTemperature(), 4, RED, WHITE, 16);
	lcd_ShowStr(200, 70, "(oC)", RED, WHITE, 16, 0);

	lcd_ShowStr(10, 90, "Humidity:", RED, WHITE, 16, 0);
	lcd_ShowIntNum(130, 90, Humidity, 2, RED, WHITE, 16);
	lcd_ShowStr(200, 90, "(%)", RED, WHITE, 16, 0);
}

void led7_Update(){
	ds3231_ReadTime();
	led7_SetDigit(ds3231_hours/10, 0, 0);
	led7_SetDigit(ds3231_hours%10, 1, 0);
	led7_SetDigit(ds3231_min/10, 2, 0);
	led7_SetDigit(ds3231_min%10, 3, 0);
}

void adc_Update(){
	sensor_Read();
	Power = sensor_GetCurrent()*sensor_GetVoltage();
	Light = sensor_GetLight();
	if(Light < 2048){
		Light_intensity = "Weak";
	}else{
		Light_intensity = "Strong";
	}
	Humidity = (((float)sensor_GetPotentiometer())/4095.0)*100.0;
}

void buzzer_Sound(uint8_t _buzzer_status){
	if(_buzzer_status == 0){
		buzzer_SetVolume(0);
	}else{
		buzzer_SetVolume(current_duty_cycle);
	}
}

void diagram_display(){
	lcd_ShowStr(10, 180, "Power", BLACK, WHITE, 16, 0);
	lcd_DrawLine(10, 200, 10, 300, BLACK);
	lcd_ShowStr(200, 290, "Time", BLACK, WHITE, 16, 0);
	lcd_DrawLine(10, 300, 190, 300, BLACK);
	for(int i = 0; i < 18; i++){
		lcd_DrawLine(Point[i][0], Point[i][1], Point[i + 1][0], Point[i + 1][1], BLACK);
	}
}
/* USER CODE END 4 */

/**
  * @brief  This function is executed in case of error occurrence.
  * @retval None
  */
void Error_Handler(void)
{
  /* USER CODE BEGIN Error_Handler_Debug */
  /* User can add his own implementation to report the HAL error return state */
  __disable_irq();
  while (1)
  {
  }
  /* USER CODE END Error_Handler_Debug */
}

#ifdef  USE_FULL_ASSERT
/**
  * @brief  Reports the name of the source file and the source line number
  *         where the assert_param error has occurred.
  * @param  file: pointer to the source file name
  * @param  line: assert_param error line source number
  * @retval None
  */
void assert_failed(uint8_t *file, uint32_t line)
{
  /* USER CODE BEGIN 6 */
  /* User can add his own implementation to report the file name and line number,
     ex: printf("Wrong parameters value: file %s on line %d\r\n", file, line) */
  /* USER CODE END 6 */
}
#endif /* USE_FULL_ASSERT */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
