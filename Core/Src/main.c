/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.c
  * @brief          : Main program body
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
/* Includes ------------------------------------------------------------------*/
#include "main.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */

/* USER CODE END Includes */

/* Private typedef -----------------------------------------------------------*/
/* USER CODE BEGIN PTD */

/* USER CODE END PTD */

/* Private define ------------------------------------------------------------*/
/* USER CODE BEGIN PD */
//Global Variables
const uint16_t LCD16x2_ADDR = (ADDRESS << 1); // Use 7-bit address shifted to left, to add R/W Bit
inter_mode mode = FIRST_BOOT;
uint16_t last_time_watered = 0;
/* USER CODE END PD */

/* Private macro -------------------------------------------------------------*/
/* USER CODE BEGIN PM */

/* USER CODE END PM */

/* Private variables ---------------------------------------------------------*/
ADC_HandleTypeDef hadc;

I2C_HandleTypeDef hi2c1;

RTC_HandleTypeDef hrtc;

UART_HandleTypeDef huart2;

/* USER CODE BEGIN PV */
//Variables for Real Time Clock (RTC)
RTC_TimeTypeDef sTime = {0};
RTC_DateTypeDef sDate = {0};
/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);
static void MX_GPIO_Init(void);
static void MX_ADC_Init(void);
static void MX_I2C1_Init(void);
static void MX_USART2_UART_Init(void);
static void MX_RTC_Init(void);
/* USER CODE BEGIN PFP */

/* USER CODE END PFP */

/* Private user code ---------------------------------------------------------*/
/* USER CODE BEGIN 0 */

/*
 * Interrupt Handler for serial Connection with PC for manually control pump, can't trigger exti-interrupt to wake up currently. Only nvic
 */
void HAL_UART_RxCpltCallback(UART_HandleTypeDef *huart){
	/*
	 * Restart System Clock after it was disabled in stop mode
	 */
	SystemClock_Config ();
	HAL_ResumeTick();

	mode=KEYBOARD_INTERRUPT;
}


/*
 * Interrupt Handler for RTC WakeUp
 */
void HAL_RTCEx_WakeUpTimerEventCallback(RTC_HandleTypeDef *hrtc){
	/*
	 * Restart System Clock after it was disabled in stop mode
	 */
	SystemClock_Config();
	HAL_ResumeTick();
	/*
	 * RTC Interrupt should not interrupt other interrupt handlers
	 */
	if(mode==UNKNOWN) mode=TIMER_INTERRUPT;

//	HAL_RTCEx_SetWakeUpTimer_IT(hrtc, 0x708000, RTC_WAKEUPCLOCK_RTCCLK_DIV16);
}

/*
 * Interrupt Handler for external gpio interrupt with button on lcd-display
 */
void HAL_GPIO_EXTI_Callback(uint16_t GPIO_Pin){
	/*
	 * Restart System Clock after it was disabled in stop mode
	 */
	SystemClock_Config();
	HAL_ResumeTick();

	if(GPIO_Pin == LCD_Botton_Pin){
		mode=BUTTON_3_INTERRUPT;
	}
}

/* USER CODE END 0 */

/**
  * @brief  The application entry point.
  * @retval int
  */
int main(void)
{
  /* USER CODE BEGIN 1 */
	uint8_t send_message[ARRAYSIZE] = {0};
	HAL_StatusTypeDef returnmessage = HAL_ERROR;
	const uint16_t waittime = TIMEAFTERWATERING_IN_MIN * 60;
	uint8_t receive_message_buf[1] = {2};
	uint16_t countwatering = 0;
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
  MX_ADC_Init();
  MX_I2C1_Init();
  MX_USART2_UART_Init();
  MX_RTC_Init();
  /* USER CODE BEGIN 2 */

  if (HAL_UART_Receive_IT(&huart2, receive_message_buf, sizeof(receive_message_buf)) != HAL_OK) {
    	sprintf((char *) send_message, "Error UART IT!\r\n");
    	HAL_UART_Transmit(&huart2, send_message, strlen((char *) send_message), HAL_MAX_DELAY);
    }



//  if (HAL_RTCEx_SetWakeUpTimer_IT(&hrtc, 0x708000, RTC_WAKEUPCLOCK_RTCCLK_DIV16) != HAL_OK) {
//	sprintf((char *) send_message, "Error WakeUp!\r\n");
//	HAL_UART_Transmit(&huart2, send_message, strlen((char *) send_message), HAL_MAX_DELAY);
//  }

  /*
   * Initialize last_time_watered
   */
  get_time_in_int(&last_time_watered, &hrtc, sTime, sDate);

  /* USER CODE END 2 */

  /* Infinite loop */
  /* USER CODE BEGIN WHILE */
  while (1)
  {
//	  //LCD_Write test message
	  HAL_Delay(100);
	  char* test = "uC is running!";
	  returnmessage = send_to_display(&hi2c1, test, strlen((char *) test), LCD16x2_ADDR);
	  if(returnmessage != HAL_OK){
		  sprintf((char *)send_message,"Error write: 0x%x\r\n", returnmessage);
		  HAL_UART_Transmit(&huart2, send_message, strlen((char*) send_message), HAL_MAX_DELAY);
	  }
////	test rtc
//		HAL_RTC_GetTime(&hrtc, &sTime, RTC_FORMAT_BIN);
//		HAL_RTC_GetDate(&hrtc, &sDate, RTC_FORMAT_BIN);
//		sprintf((char*) send_message, "%02d:%02d:%02d:%02d", sDate.WeekDay, sTime.Hours, sTime.Minutes, sTime.Seconds);
//		send_to_display(&hi2c1, send_message, strlen((char *) send_message), LCD16x2_ADDR);
//		HAL_UART_Transmit(&huart2, send_message, strlen((char*) send_message), HAL_MAX_DELAY);
//		HAL_Delay(100);


//	  if(!should_water(&last_time_watered, (uint16_t) waittime, &hrtc, sTime, sDate)){
//		  sprintf((char *)send_message,"Watering!!!!\r\n");
//		  HAL_UART_Transmit(&huart2, send_message, strlen((char*) send_message), HAL_MAX_DELAY);
//	  }
//	  else{
//		  sprintf((char *)send_message,"Water time: %d\r\n", last_time_watered);
//		  HAL_UART_Transmit(&huart2, send_message, strlen((char*) send_message), HAL_MAX_DELAY);
//	  }

	  /*
	   * Check if Flag was set and which one
	   * On first run this sequence is run, to ensure connection to display
	   */
	  if(mode==FIRST_BOOT){
		  sprintf((char *) send_message, "Controller was restarted or firstly booted\r\n");
		  HAL_UART_Transmit(&huart2, send_message, strlen((char *) send_message), HAL_MAX_DELAY);

		  /*
		   * LCD16x2 get ID to ensure that display is connected correctly, doesn't work on first run??
		   */
		  send_message[0] = GET_ID;

		  returnmessage = HAL_I2C_Master_Transmit(&hi2c1, LCD16x2_ADDR , send_message, 1, HAL_MAX_DELAY);
		  if(returnmessage != HAL_OK){
			  sprintf((char *)send_message,"Error ID Tx: 0x%x\r\n", returnmessage);
		  }
		  else{
			  returnmessage = HAL_I2C_Master_Receive(&hi2c1, LCD16x2_ADDR, send_message, 1, HAL_MAX_DELAY);

			  if(returnmessage != HAL_OK) sprintf((char *)send_message,"Error ID Rx: 0x%x\r\n", returnmessage);
			  if(send_message[0]==0x65) sprintf((char *)send_message,"Display connected correct. LCD-ID: 0x%x\r\n", send_message[0]);
			  else sprintf((char *)send_message,"Display connected incorrect. LCD-ID: 0x%x\r\n", send_message[0]);
		  }
		  HAL_UART_Transmit(&huart2, send_message, strlen((char*) send_message), HAL_MAX_DELAY);
	  }
	  // Sequence for interrupt triggered by rtc-timer
	  else if(mode==TIMER_INTERRUPT){
		  returnmessage = timer_interrupt_routine(&huart2, &hadc, &hi2c1, waittime, &last_time_watered, &countwatering, LCD16x2_ADDR, &hrtc, sTime, sDate);
		  if(returnmessage != HAL_OK){
			  sprintf((char *)send_message,"Error timinthandl: 0x%x\r\n", returnmessage);
			  HAL_UART_Transmit(&huart2, send_message, strlen((char*) send_message), HAL_MAX_DELAY);
		  }

//		  //debugging
//		  uint8_t* timebuf;
//		  get_time((char *) timebuf, &hrtc, sTime, sDate);
//		  sprintf((char *) send_message, "Woke up at: \r\n%s\r\n", timebuf);
//		  HAL_UART_Transmit(&huart2, send_message, strlen((char *) send_message), HAL_MAX_DELAY);
//		  send_to_display(&hi2c1, (uint16_t *) send_message, strlen((char *) send_message)-2, LCD16x2_ADDR);
//		  HAL_Delay(1000);
	  }

	  /*
	   * sequence triggered by buttons on lcd-display, i2c slave cannot trigger interrupt at master.
	   * Solder wire from button to gpio pin of uC to trigger interrupt that way
	   */
	  else if(mode==BUTTON_1_INTERRUPT || mode==BUTTON_2_INTERRUPT || mode==BUTTON_3_INTERRUPT || mode==BUTTON_4_INTERRUPT){
		  returnmessage = gpio_interrupt_routine(&huart2, &hadc, &hi2c1, LCD16x2_ADDR, &countwatering, &hrtc, sTime, sDate);
		  if(returnmessage != HAL_OK){
			  sprintf((char *)send_message,"Error button inthandl: 0x%x\r\n", returnmessage);
			  HAL_UART_Transmit(&huart2, send_message, strlen((char*) send_message), HAL_MAX_DELAY);
		  }
	  }
	  // sequence for UART interrupt, cannot wake up uC, because uses global nvic interrupt not exti line
	  else if(mode==KEYBOARD_INTERRUPT){
		  returnmessage = uart_interrupt_routine(receive_message_buf[0], &countwatering, &huart2, &hi2c1, LCD16x2_ADDR);

		  if(returnmessage != HAL_OK){
			  sprintf((char *)send_message,"Error uartinthandl: 0x%x\r\n", returnmessage);
			  HAL_UART_Transmit(&huart2, send_message, strlen((char*) send_message), HAL_MAX_DELAY);
		  }
		  HAL_UART_Receive_IT(&huart2, receive_message_buf, sizeof(receive_message_buf));
	  }
	  else{
		  sprintf((char *)send_message, "Something unexpected happend!\r\n");
		  HAL_UART_Transmit(&huart2, send_message, strlen((char*)send_message), HAL_MAX_DELAY);
	  }

	  //LCD_Clear Display
	  clear_screen(&hi2c1, LCD16x2_ADDR);

//	  ////LCD16x2 Backlight OFF
//	  send_message[0] = SET_BL;
//	  send_message[1] = BACKLIGHT_OFF;
//
//	  returnmessage = HAL_I2C_Master_Transmit(&hi2c1, LCD16x2_ADDR , send_message, 2, HAL_MAX_DELAY);
//
//	  if(returnmessage != HAL_OK){
//		  sprintf((char *)send_message,"Error BL: 0x%x\r\n", returnmessage);
//		  HAL_UART_Transmit(&huart2, send_message, strlen((char*) send_message), HAL_MAX_DELAY);
//	  }
//
//	  HAL_Delay(100);

	  mode=UNKNOWN; //Reset interrupt_mode typedef

	  sprintf((char *) send_message, "Entering Stop-Mode!\r\n");
	  HAL_UART_Transmit(&huart2, send_message, strlen((char *) send_message), HAL_MAX_DELAY);
	  /*Suspend Sys-Clock, because it would wake uC up on first pulse*/
	  HAL_SuspendTick();
	  /*Enter Stop-Mode*/
	  HAL_PWR_EnterSTOPMode(PWR_LOWPOWERREGULATOR_ON, PWR_STOPENTRY_WFI);
//	  HAL_PWR_EnterSLEEPMode(PWR_LOWPOWERREGULATOR_ON, PWR_STOPENTRY_WFI);
	  HAL_ResumeTick();

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
  RCC_PeriphCLKInitTypeDef PeriphClkInit = {0};

  /** Configure the main internal regulator output voltage
  */
  __HAL_PWR_VOLTAGESCALING_CONFIG(PWR_REGULATOR_VOLTAGE_SCALE1);

  /** Initializes the RCC Oscillators according to the specified parameters
  * in the RCC_OscInitTypeDef structure.
  */
  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSI|RCC_OSCILLATORTYPE_LSE;
  RCC_OscInitStruct.LSEState = RCC_LSE_ON;
  RCC_OscInitStruct.HSIState = RCC_HSI_ON;
  RCC_OscInitStruct.HSICalibrationValue = RCC_HSICALIBRATION_DEFAULT;
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON;
  RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_HSI;
  RCC_OscInitStruct.PLL.PLLMUL = RCC_PLL_MUL6;
  RCC_OscInitStruct.PLL.PLLDIV = RCC_PLL_DIV3;
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
  RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV1;
  RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV1;

  if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_1) != HAL_OK)
  {
    Error_Handler();
  }
  PeriphClkInit.PeriphClockSelection = RCC_PERIPHCLK_RTC;
  PeriphClkInit.RTCClockSelection = RCC_RTCCLKSOURCE_LSE;
  if (HAL_RCCEx_PeriphCLKConfig(&PeriphClkInit) != HAL_OK)
  {
    Error_Handler();
  }
}

/**
  * @brief ADC Initialization Function
  * @param None
  * @retval None
  */
static void MX_ADC_Init(void)
{

  /* USER CODE BEGIN ADC_Init 0 */

  /* USER CODE END ADC_Init 0 */

  ADC_ChannelConfTypeDef sConfig = {0};

  /* USER CODE BEGIN ADC_Init 1 */

  /* USER CODE END ADC_Init 1 */

  /** Configure the global features of the ADC (Clock, Resolution, Data Alignment and number of conversion)
  */
  hadc.Instance = ADC1;
  hadc.Init.ClockPrescaler = ADC_CLOCK_ASYNC_DIV1;
  hadc.Init.Resolution = ADC_RESOLUTION_12B;
  hadc.Init.DataAlign = ADC_DATAALIGN_RIGHT;
  hadc.Init.ScanConvMode = ADC_SCAN_DISABLE;
  hadc.Init.EOCSelection = ADC_EOC_SEQ_CONV;
  hadc.Init.LowPowerAutoWait = ADC_AUTOWAIT_DISABLE;
  hadc.Init.LowPowerAutoPowerOff = ADC_AUTOPOWEROFF_DISABLE;
  hadc.Init.ChannelsBank = ADC_CHANNELS_BANK_A;
  hadc.Init.ContinuousConvMode = DISABLE;
  hadc.Init.NbrOfConversion = 1;
  hadc.Init.DiscontinuousConvMode = DISABLE;
  hadc.Init.ExternalTrigConv = ADC_SOFTWARE_START;
  hadc.Init.ExternalTrigConvEdge = ADC_EXTERNALTRIGCONVEDGE_NONE;
  hadc.Init.DMAContinuousRequests = DISABLE;
  if (HAL_ADC_Init(&hadc) != HAL_OK)
  {
    Error_Handler();
  }

  /** Configure for the selected ADC regular channel its corresponding rank in the sequencer and its sample time.
  */
  sConfig.Channel = ADC_CHANNEL_4;
  sConfig.Rank = ADC_REGULAR_RANK_1;
  sConfig.SamplingTime = ADC_SAMPLETIME_4CYCLES;
  if (HAL_ADC_ConfigChannel(&hadc, &sConfig) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN ADC_Init 2 */

  /* USER CODE END ADC_Init 2 */

}

/**
  * @brief I2C1 Initialization Function
  * @param None
  * @retval None
  */
static void MX_I2C1_Init(void)
{

  /* USER CODE BEGIN I2C1_Init 0 */

  /* USER CODE END I2C1_Init 0 */

  /* USER CODE BEGIN I2C1_Init 1 */

  /* USER CODE END I2C1_Init 1 */
  hi2c1.Instance = I2C1;
  hi2c1.Init.ClockSpeed = 100000;
  hi2c1.Init.DutyCycle = I2C_DUTYCYCLE_2;
  hi2c1.Init.OwnAddress1 = 96;
  hi2c1.Init.AddressingMode = I2C_ADDRESSINGMODE_7BIT;
  hi2c1.Init.DualAddressMode = I2C_DUALADDRESS_DISABLE;
  hi2c1.Init.OwnAddress2 = 0;
  hi2c1.Init.GeneralCallMode = I2C_GENERALCALL_DISABLE;
  hi2c1.Init.NoStretchMode = I2C_NOSTRETCH_DISABLE;
  if (HAL_I2C_Init(&hi2c1) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN I2C1_Init 2 */

  /* USER CODE END I2C1_Init 2 */

}

/**
  * @brief RTC Initialization Function
  * @param None
  * @retval None
  */
static void MX_RTC_Init(void)
{

  /* USER CODE BEGIN RTC_Init 0 */

  /* USER CODE END RTC_Init 0 */

  RTC_TimeTypeDef sTime = {0};
  RTC_DateTypeDef sDate = {0};

  /* USER CODE BEGIN RTC_Init 1 */

  /* USER CODE END RTC_Init 1 */

  /** Initialize RTC Only
  */
  hrtc.Instance = RTC;
  hrtc.Init.HourFormat = RTC_HOURFORMAT_24;
  hrtc.Init.AsynchPrediv = 124;
  hrtc.Init.SynchPrediv = 295;
  hrtc.Init.OutPut = RTC_OUTPUT_DISABLE;
  hrtc.Init.OutPutPolarity = RTC_OUTPUT_POLARITY_HIGH;
  hrtc.Init.OutPutType = RTC_OUTPUT_TYPE_OPENDRAIN;
  if (HAL_RTC_Init(&hrtc) != HAL_OK)
  {
    Error_Handler();
  }

  /* USER CODE BEGIN Check_RTC_BKUP */

  /* USER CODE END Check_RTC_BKUP */

  /** Initialize RTC and set the Time and Date
  */
  sTime.Hours = 0x0;
  sTime.Minutes = 0x0;
  sTime.Seconds = 0x0;
  sTime.DayLightSaving = RTC_DAYLIGHTSAVING_NONE;
  sTime.StoreOperation = RTC_STOREOPERATION_RESET;
  if (HAL_RTC_SetTime(&hrtc, &sTime, RTC_FORMAT_BCD) != HAL_OK)
  {
    Error_Handler();
  }
  sDate.WeekDay = RTC_WEEKDAY_MONDAY;
  sDate.Month = RTC_MONTH_JANUARY;
  sDate.Date = 0x1;
  sDate.Year = 0x0;

  if (HAL_RTC_SetDate(&hrtc, &sDate, RTC_FORMAT_BCD) != HAL_OK)
  {
    Error_Handler();
  }

  /** Enable the WakeUp
  */
  if (HAL_RTCEx_SetWakeUpTimer_IT(&hrtc, SLEEPTIME, RTC_WAKEUPCLOCK_RTCCLK_DIV16) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN RTC_Init 2 */

  HAL_PWR_DisableSleepOnExit();

  /* USER CODE END RTC_Init 2 */

}

/**
  * @brief USART2 Initialization Function
  * @param None
  * @retval None
  */
static void MX_USART2_UART_Init(void)
{

  /* USER CODE BEGIN USART2_Init 0 */

  /* USER CODE END USART2_Init 0 */

  /* USER CODE BEGIN USART2_Init 1 */

  /* USER CODE END USART2_Init 1 */
  huart2.Instance = USART2;
  huart2.Init.BaudRate = 115200;
  huart2.Init.WordLength = UART_WORDLENGTH_8B;
  huart2.Init.StopBits = UART_STOPBITS_1;
  huart2.Init.Parity = UART_PARITY_NONE;
  huart2.Init.Mode = UART_MODE_TX_RX;
  huart2.Init.HwFlowCtl = UART_HWCONTROL_NONE;
  huart2.Init.OverSampling = UART_OVERSAMPLING_16;
  if (HAL_UART_Init(&huart2) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN USART2_Init 2 */

  /* USER CODE END USART2_Init 2 */

}

/**
  * @brief GPIO Initialization Function
  * @param None
  * @retval None
  */
static void MX_GPIO_Init(void)
{
  GPIO_InitTypeDef GPIO_InitStruct = {0};
/* USER CODE BEGIN MX_GPIO_Init_1 */
/* USER CODE END MX_GPIO_Init_1 */

  /* GPIO Ports Clock Enable */
  __HAL_RCC_GPIOC_CLK_ENABLE();
  __HAL_RCC_GPIOH_CLK_ENABLE();
  __HAL_RCC_GPIOA_CLK_ENABLE();
  __HAL_RCC_GPIOB_CLK_ENABLE();
  __HAL_RCC_GPIOD_CLK_ENABLE();

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(GPIOA, LD2_Pin|Optokoppler_Pin, GPIO_PIN_RESET);

  /*Configure GPIO pins : PC13 PC0 PC1 PC2
                           PC3 PC4 PC5 PC7
                           PC8 PC9 PC10 PC11
                           PC12 */
  GPIO_InitStruct.Pin = GPIO_PIN_13|GPIO_PIN_0|GPIO_PIN_1|GPIO_PIN_2
                          |GPIO_PIN_3|GPIO_PIN_4|GPIO_PIN_5|GPIO_PIN_7
                          |GPIO_PIN_8|GPIO_PIN_9|GPIO_PIN_10|GPIO_PIN_11
                          |GPIO_PIN_12;
  GPIO_InitStruct.Mode = GPIO_MODE_ANALOG;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  HAL_GPIO_Init(GPIOC, &GPIO_InitStruct);

  /*Configure GPIO pins : PA0 PA1 PA7 PA8
                           PA9 PA10 PA11 PA12
                           PA15 */
  GPIO_InitStruct.Pin = GPIO_PIN_0|GPIO_PIN_1|GPIO_PIN_7|GPIO_PIN_8
                          |GPIO_PIN_9|GPIO_PIN_10|GPIO_PIN_11|GPIO_PIN_12
                          |GPIO_PIN_15;
  GPIO_InitStruct.Mode = GPIO_MODE_ANALOG;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);

  /*Configure GPIO pins : LD2_Pin Optokoppler_Pin */
  GPIO_InitStruct.Pin = LD2_Pin|Optokoppler_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);

  /*Configure GPIO pins : PB0 PB1 PB2 PB10
                           PB11 PB12 PB13 PB14
                           PB15 PB3 PB4 PB5
                           PB6 PB7 */
  GPIO_InitStruct.Pin = GPIO_PIN_0|GPIO_PIN_1|GPIO_PIN_2|GPIO_PIN_10
                          |GPIO_PIN_11|GPIO_PIN_12|GPIO_PIN_13|GPIO_PIN_14
                          |GPIO_PIN_15|GPIO_PIN_3|GPIO_PIN_4|GPIO_PIN_5
                          |GPIO_PIN_6|GPIO_PIN_7;
  GPIO_InitStruct.Mode = GPIO_MODE_ANALOG;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  HAL_GPIO_Init(GPIOB, &GPIO_InitStruct);

  /*Configure GPIO pin : LCD_Botton_Pin */
  GPIO_InitStruct.Pin = LCD_Botton_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_IT_FALLING;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  HAL_GPIO_Init(LCD_Botton_GPIO_Port, &GPIO_InitStruct);

  /*Configure GPIO pin : PD2 */
  GPIO_InitStruct.Pin = GPIO_PIN_2;
  GPIO_InitStruct.Mode = GPIO_MODE_ANALOG;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  HAL_GPIO_Init(GPIOD, &GPIO_InitStruct);

  /* EXTI interrupt init*/
  HAL_NVIC_SetPriority(EXTI9_5_IRQn, 0, 0);
  HAL_NVIC_EnableIRQ(EXTI9_5_IRQn);

/* USER CODE BEGIN MX_GPIO_Init_2 */
/* USER CODE END MX_GPIO_Init_2 */
}

/* USER CODE BEGIN 4 */

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
