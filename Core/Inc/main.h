/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.h
  * @brief          : Header for main.c file.
  *                   This file contains the common defines of the application.
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2023 STMicroelectronics.
  * All rights reserved.
  *
  * This software is licensed under terms that can be found in the LICENSE file
  * in the root directory of this software component.
  * If no LICENSE file comes with this software, it is provided AS-IS.
  *
  ******************************************************************************
  */
/* USER CODE END Header */

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __MAIN_H
#define __MAIN_H

#ifdef __cplusplus
extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "stm32l1xx_hal.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */
#include <stdio.h>
#include <string.h>
/* USER CODE END Includes */

/* Exported types ------------------------------------------------------------*/
/* USER CODE BEGIN ET */
	typedef enum
	{
		TIMER_INTERRUPT,
		BUTTON_1_INTERRUPT,
		BUTTON_2_INTERRUPT,
		BUTTON_3_INTERRUPT,
		BUTTON_4_INTERRUPT,
		KEYBOARD_INTERRUPT,
		FIRST_BOOT,
		UNKNOWN
	} inter_mode;

	typedef enum
	{
		NOBUTTON = 0x00U,
		BUTTON_1 = 0x01U,
		BUTTON_2 = 0x02U,
		BUTTON_3 = 0x03U,
		BUTTON_4 = 0x04U,
	} button_input;

/* USER CODE END ET */

/* Exported constants --------------------------------------------------------*/
/* USER CODE BEGIN EC */

/* USER CODE END EC */

/* Exported macro ------------------------------------------------------------*/
/* USER CODE BEGIN EM */

/* USER CODE END EM */

/* Exported functions prototypes ---------------------------------------------*/
void Error_Handler(void);

/* USER CODE BEGIN EFP */
//Private function declaration
HAL_StatusTypeDef send_to_display(			I2C_HandleTypeDef *hi2c,
											char* input_string,
											uint8_t numchar,
											uint16_t address);

HAL_StatusTypeDef clear_screen(				I2C_HandleTypeDef *hi2c,
											uint16_t LCD16x2_ADDR);

HAL_StatusTypeDef uart_interrupt_handler(	char uart_message,
											UART_HandleTypeDef* huart,
											I2C_HandleTypeDef* hi2c,
											uint16_t LCD16x2_ADDR);

HAL_StatusTypeDef timer_interrupt_handler(	UART_HandleTypeDef* huart,
											ADC_HandleTypeDef* hadc,
											I2C_HandleTypeDef *hi2c,
											uint16_t waittime,
											uint16_t* last_time_watered,
											uint16_t LCD16x2_ADDR,
											RTC_HandleTypeDef *hrtc,
											RTC_TimeTypeDef sTime,
											RTC_DateTypeDef sDate);

button_input get_button_input(				I2C_HandleTypeDef *hi2c,
											uint16_t LCD16x2_ADDR);

HAL_StatusTypeDef gpio_interrupt_handler(	UART_HandleTypeDef* huart,
											ADC_HandleTypeDef* hadc,
											I2C_HandleTypeDef *hi2c,
											uint16_t LCD16x2_ADDR,
											RTC_HandleTypeDef *hrtc,
											RTC_TimeTypeDef sTime,
											RTC_DateTypeDef sDate);

void get_time(								char* string,
											RTC_HandleTypeDef *hrtc,
											RTC_TimeTypeDef sTime,
											RTC_DateTypeDef sDate);

void set_bl_lcd(							I2C_HandleTypeDef *hi2c,
											uint16_t LCD16x2_ADDR,
											uint8_t value);

int should_water(							uint16_t* previous_time,
											uint16_t waittime,
											RTC_HandleTypeDef *hrtc,
											RTC_TimeTypeDef sTime,
											RTC_DateTypeDef sDate);

void get_time_in_int(						uint16_t* time,
											RTC_HandleTypeDef *hrtc,
											RTC_TimeTypeDef sTime,
											RTC_DateTypeDef sDate);
/* USER CODE END EFP */

/* Private defines -----------------------------------------------------------*/
#define LD2_Pin GPIO_PIN_5
#define LD2_GPIO_Port GPIOA
#define Optokoppler_Pin GPIO_PIN_6
#define Optokoppler_GPIO_Port GPIOA
#define LCD_Botton_Pin GPIO_PIN_6
#define LCD_Botton_GPIO_Port GPIOC
#define LCD_Botton_EXTI_IRQn EXTI9_5_IRQn
#define TMS_Pin GPIO_PIN_13
#define TMS_GPIO_Port GPIOA
#define TCK_Pin GPIO_PIN_14
#define TCK_GPIO_Port GPIOA

/* USER CODE BEGIN Private defines */

#define MIN_MOISTURE_VOLTAGE 		2.000000 // has to be calibrated
#define TIMEAFTERWATERING_IN_MIN 	1
#define TIMEPUMPISRUNNING_IN_S 		5
#define TIMEBUTTONTIMEOUT	 		10000 	// 10s before timeout in buttoninput
//#define SLEEPTIME 0x708000 //60min
#define SLEEPTIME 0x1e000 //1min
#define ARRAYSIZE 	45

//LCD16x2 Defines
#define SET_TRIS    0x01
#define SET_LAT     0x02
#define GET_PORT    0x03
#define GET_BUT     0x05
#define GET_ID      0x20
#define GET_FRM     0x21
#define LCD_CLR     0x60
#define LCD_WR      0x61
#define SET_BL		0x62
#define UART_EN     0x10

#define BOARD_ID    0x65
#define ADDRESS     0x30
#define BACKLIGHT_OFF 0
#define BACKLIGHT_ON 255

/* USER CODE END Private defines */

#ifdef __cplusplus
}
#endif

#endif /* __MAIN_H */
