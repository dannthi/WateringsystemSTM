/*
 * additional_functions.c
 *
 *  Created on: 20.04.2023
 *      Author: Thilo Danner
 */


#include "main.h"

/**
  * @brief Send string to LCD-Display
  * @note If \r or \n are detected the string is contiued in the second line.
  * @retval HAL status
  */
HAL_StatusTypeDef send_to_display(I2C_HandleTypeDef *hi2c, char* input_string, uint8_t numchar, uint16_t address){
	HAL_StatusTypeDef returnmessage = HAL_ERROR;
	uint8_t send_message[ARRAYSIZE] = {0};
	uint8_t upordown = 1;
	uint8_t offset = 16;

	clear_screen(hi2c, address);

	send_message[0] = LCD_WR;

	for(uint8_t i=0; i<numchar; i++){
		if((input_string[i] == '\r') || (input_string[i] == '\n')){
			offset = i;
			i++;
			upordown = 0;
		}
		else{
			if(i <= 15){
				send_message[1] = upordown;
				if(upordown) send_message[2] = i;
				else send_message[2] = i-offset;
			}
			else if(i <= 30){
				send_message[1] = 0;
				send_message[2] = i-offset;
			}
			else return HAL_ERROR;

			send_message[3]=input_string[i];
			returnmessage = HAL_I2C_Master_Transmit(hi2c, address , send_message, 4, HAL_MAX_DELAY);
			if(returnmessage != HAL_OK){
				return returnmessage;
			}
			HAL_Delay(50);
		}
	}
	HAL_Delay(100);
	return HAL_OK;
}

/**
  * @brief Interrupt routine for RTC
  * @retval HAL status
  */
HAL_StatusTypeDef timer_interrupt_routine(	UART_HandleTypeDef* huart, ADC_HandleTypeDef* hadc, I2C_HandleTypeDef *hi2c,
											uint16_t waittime, uint16_t* last_time_watered, uint16_t* countwatering,
											uint16_t LCD16x2_ADDR, RTC_HandleTypeDef *hrtc, RTC_TimeTypeDef sTime, RTC_DateTypeDef sDate){
	uint8_t send_message[ARRAYSIZE] = {0};
	uint16_t adc_value = 0;
	HAL_StatusTypeDef returnmessage = HAL_ERROR;
	float voltage;

//	HAL_GPIO_TogglePin(LD2_GPIO_Port, LD2_Pin);

	sprintf((char *) send_message, "Leaving Stop-Mode!\r\n");
	HAL_UART_Transmit(huart, send_message, strlen((char *) send_message), HAL_MAX_DELAY);

	get_time((char *) send_message, hrtc, sTime, sDate);
	send_to_display(hi2c, (char*) send_message, strlen((char *) send_message), LCD16x2_ADDR);

	  //Get Voltage from Moisture Sensor
	  if(HAL_ADC_Start(hadc) != HAL_OK){
		  sprintf((char *) send_message, "ADC not OK!\r\n");
		  HAL_UART_Transmit(huart, send_message, strlen((char *) send_message), HAL_MAX_DELAY);
		  return HAL_ERROR;
	  }
	  else{
		  returnmessage = HAL_ADC_PollForConversion(hadc, HAL_MAX_DELAY);

		  if (returnmessage == HAL_OK){
			  adc_value = HAL_ADC_GetValue(hadc);
			  voltage = (adc_value / 4096.0f) * 3.3f;
			  sprintf((char *)send_message, "Voltage:\r\n%lfV\r\n", voltage);
			  HAL_UART_Transmit(huart, send_message, strlen((char*)send_message), HAL_MAX_DELAY);
			  send_to_display(hi2c, (char*) send_message, strlen((char *) send_message)-2, LCD16x2_ADDR);
		  }
		  else{
			  sprintf((char *)send_message,"Error! ADC returned: 0x%x\r\n", returnmessage);
			  HAL_UART_Transmit(huart, send_message, strlen((char*) send_message), HAL_MAX_DELAY);
		  }
		  //HAL_Delay(1000);
	  }

	  /* Logic to power pump on low moisture voltage. Also don't water to often :)
	   *
	   * Moisture ~ 1/U
	   */
	  if(voltage > MIN_MOISTURE_VOLTAGE && !should_water(last_time_watered, (uint16_t) waittime, hrtc, sTime, sDate)){
		  //start pump, also led for debugging reasons
		  HAL_GPIO_WritePin(Optokoppler_GPIO_Port, Optokoppler_Pin, GPIO_PIN_SET);
		  HAL_GPIO_WritePin(LD2_GPIO_Port, LD2_Pin, GPIO_PIN_SET);

		  sprintf((char *)send_message, "Pump: ON\r\n\n");
		  HAL_UART_Transmit(huart, send_message, strlen((char*)send_message), HAL_MAX_DELAY);
		  send_to_display(hi2c, (char*) send_message, strlen((char *) send_message)-3, LCD16x2_ADDR);

		  HAL_Delay(1000 * TIMEPUMPISRUNNING_IN_S);

		  //stop pump
		  HAL_GPIO_WritePin(Optokoppler_GPIO_Port, Optokoppler_Pin, GPIO_PIN_RESET);
		  HAL_GPIO_WritePin(LD2_GPIO_Port, LD2_Pin, GPIO_PIN_RESET);

		  sprintf((char *)send_message, "Pump: OFF\r\n\n");
		  HAL_UART_Transmit(huart, send_message, strlen((char*)send_message), HAL_MAX_DELAY);
		  send_to_display(hi2c, (char*) send_message, strlen((char *) send_message)-3, LCD16x2_ADDR);

		  *countwatering = *countwatering + 1;
	  }

	  return HAL_OK;
}

/**
  * @brief Interrupt routine for UART
  * @note UART cannot wake up uC from stop mode
  * @retval HAL status
  */
HAL_StatusTypeDef uart_interrupt_routine(char uart_message, uint16_t* countwatering, UART_HandleTypeDef* huart, I2C_HandleTypeDef* hi2c, uint16_t LCD16x2_ADDR){
	uint8_t send_message[ARRAYSIZE] = {0};

	if(uart_message == 'y'){
		HAL_GPIO_WritePin(Optokoppler_GPIO_Port, Optokoppler_Pin, GPIO_PIN_SET);
		HAL_GPIO_WritePin(LD2_GPIO_Port, LD2_Pin, GPIO_PIN_SET);
		sprintf((char *) send_message, "Pump: on\r\n");
		HAL_UART_Transmit(huart, send_message, strlen((char*)send_message), HAL_MAX_DELAY);
		send_to_display(hi2c, (char*) send_message, strlen((char *) send_message)-2, LCD16x2_ADDR);

		*countwatering = *countwatering + 1;
	}
	else if (uart_message == 'n'){
		HAL_GPIO_WritePin(Optokoppler_GPIO_Port, Optokoppler_Pin, GPIO_PIN_RESET);
		HAL_GPIO_WritePin(LD2_GPIO_Port, LD2_Pin, GPIO_PIN_RESET);
		sprintf((char *)send_message, "Pump: off\r\n");
		HAL_UART_Transmit(huart, send_message, strlen((char*)send_message), HAL_MAX_DELAY);
		send_to_display(hi2c, (char*) send_message, strlen((char *) send_message)-2, LCD16x2_ADDR);
	}
	else{
		HAL_GPIO_WritePin(Optokoppler_GPIO_Port, Optokoppler_Pin, GPIO_PIN_RESET);
		HAL_GPIO_WritePin(LD2_GPIO_Port, LD2_Pin, GPIO_PIN_RESET);
		sprintf((char *)send_message, "Couldn't recognize command.\r\n");
		HAL_UART_Transmit(huart, send_message, strlen((char*)send_message), HAL_MAX_DELAY);
		sprintf((char *)send_message, "Received: %d, Pump: off\r\n", uart_message);
		HAL_UART_Transmit(huart, send_message, strlen((char*)send_message), HAL_MAX_DELAY);
		send_to_display(hi2c, (char*) send_message, strlen((char *) send_message)-2, LCD16x2_ADDR);
		return HAL_ERROR;
	}

	  return HAL_OK;
}

/**
  * @brief Interrupt routine for external GPIO
  * @note Buttons on Display:
  * 		Button 1: Show time running
  * 		Button 2: Show Voltage from ADC
  * 		Button 3: Run pump for 10s
  * 		Butten 4: Trigger interrupt. Has to be pressed before using other buttons. Show times watered.
  * 	  One Button has to be pressed after feedback
  * 	  Timeout after 10s.
  * @note Other features can freely be added. Maybe a FSM could be useful
  * @retval HAL status
  */
HAL_StatusTypeDef gpio_interrupt_routine(	UART_HandleTypeDef* huart, ADC_HandleTypeDef* hadc, I2C_HandleTypeDef *hi2c,
											uint16_t LCD16x2_ADDR, uint16_t* countwatering, RTC_HandleTypeDef *hrtc, RTC_TimeTypeDef sTime, RTC_DateTypeDef sDate){
	uint32_t reftime = HAL_GetTick();
	button_input button = NOBUTTON;
	uint8_t send_message[ARRAYSIZE] = {0};

	set_bl_lcd(hi2c, LCD16x2_ADDR, BACKLIGHT_ON);

	sprintf((char *) send_message, "Wait for input\r\n");
	HAL_UART_Transmit(huart, send_message, strlen((char*)send_message), HAL_MAX_DELAY);
	send_to_display(hi2c, (char*) send_message, strlen((char *) send_message)-2, LCD16x2_ADDR);

	while(reftime + TIMEBUTTONTIMEOUT > HAL_GetTick()){
		/*
		 * get state of buttons till timeout is reached
		 */
		button = get_button_input(hi2c, LCD16x2_ADDR);
		if(button != NOBUTTON){
			if(button == BUTTON_1){
				uint8_t timebuf[1];
				get_time((char*) timebuf, hrtc, sTime, sDate);
				sprintf((char *)send_message, "%s\r\n", timebuf);
			}
			else if(button == BUTTON_2){
				float voltage;
				uint16_t adc_value = 0;

				HAL_ADC_Start(hadc);
				HAL_ADC_PollForConversion(hadc, HAL_MAX_DELAY);
				adc_value = HAL_ADC_GetValue(hadc);
				voltage = (adc_value / 4096.0f) * 3.3f;
				sprintf((char *)send_message, "%lfV\r\n", voltage);
			}
			else if(button == BUTTON_3){
				//start pump
				HAL_GPIO_WritePin(Optokoppler_GPIO_Port, Optokoppler_Pin, GPIO_PIN_SET);
				HAL_GPIO_WritePin(LD2_GPIO_Port, LD2_Pin, GPIO_PIN_SET);

				sprintf((char *)send_message, "Pump: ON\r\n");
				HAL_UART_Transmit(huart, send_message, strlen((char*)send_message), HAL_MAX_DELAY);
				send_to_display(hi2c, (char*) send_message, strlen((char *) send_message), LCD16x2_ADDR);

				HAL_Delay(1000 * TIMEPUMPISRUNNING_IN_S);

				//stop pump
				HAL_GPIO_WritePin(Optokoppler_GPIO_Port, Optokoppler_Pin, GPIO_PIN_RESET);
				HAL_GPIO_WritePin(LD2_GPIO_Port, LD2_Pin, GPIO_PIN_RESET);

				sprintf((char *)send_message, "Pump: OFF\r\n");
				HAL_UART_Transmit(huart, send_message, strlen((char*)send_message), HAL_MAX_DELAY);
				send_to_display(hi2c, (char*) send_message, strlen((char *) send_message), LCD16x2_ADDR);

				*countwatering = *countwatering + 1;
			}
			else if(button == BUTTON_4){
				sprintf((char *)send_message, "Watered: %d\r\n", *countwatering);
				HAL_UART_Transmit(huart, send_message, strlen((char*)send_message), HAL_MAX_DELAY);
				send_to_display(hi2c, (char*) send_message, strlen((char *) send_message)-2, LCD16x2_ADDR);
			}

			/*
			 * Buffers bouncing button
			 */
			get_button_input(hi2c, LCD16x2_ADDR);

			HAL_UART_Transmit(huart, send_message, strlen((char*)send_message), HAL_MAX_DELAY);
			send_to_display(hi2c, (char*) send_message, strlen((char *) send_message)-2, LCD16x2_ADDR);

			while(1){
				if(get_button_input(hi2c, LCD16x2_ADDR) != NOBUTTON) break;
			}

			/*
			 * Buffers bouncing button
			 */
			get_button_input(hi2c, LCD16x2_ADDR);

			/*
			 * Backlight off, clears screen and return
			 */
			clear_screen(hi2c, LCD16x2_ADDR);
			set_bl_lcd(hi2c, LCD16x2_ADDR, BACKLIGHT_OFF);
			return HAL_OK;
		}
	}

	sprintf((char *) send_message, "Timeout.\r\n");
	HAL_UART_Transmit(huart, send_message, strlen((char*)send_message), HAL_MAX_DELAY);
	send_to_display(hi2c, (char*) send_message, strlen((char *) send_message)-2, LCD16x2_ADDR);

//	while(1){
//		if(get_button_input(hi2c, LCD16x2_ADDR) != NOBUTTON) break;
//		else HAL_Delay(10);
//	}

	/*
	 * Backlight off, clears screen and return
	 */
	clear_screen(hi2c, LCD16x2_ADDR);
	set_bl_lcd(hi2c, LCD16x2_ADDR, BACKLIGHT_OFF);
	return HAL_TIMEOUT; //Timeout
}

/**
  * @brief Request status of buttons
  * @note Can only decode one button at a time
  * @retval Code of button
  */
button_input get_button_input(I2C_HandleTypeDef *hi2c, uint16_t LCD16x2_ADDR){
	uint8_t send_message[] = {GET_BUT};
	int buttonstate[] = {0xf};

	/*
	 * request and receive button states
	 */
	HAL_I2C_Master_Transmit(hi2c, LCD16x2_ADDR , send_message, 1, HAL_MAX_DELAY);
	HAL_I2C_Master_Receive(hi2c, LCD16x2_ADDR , (uint8_t *) buttonstate, 1, HAL_MAX_DELAY);

	HAL_Delay(100);

	if(buttonstate[0] == 0xe) return BUTTON_1;
	else if(buttonstate[0] == 0xd) return BUTTON_2;
	else if(buttonstate[0] == 0xb) return BUTTON_3;
	else if(buttonstate[0] == 0x7) return BUTTON_4;
	else return NOBUTTON;
}

/**
  * @brief Set Background of LCD-Display
  * @note value should be in range from 0 to 255
  * @retval none
  */
void set_bl_lcd(I2C_HandleTypeDef *hi2c, uint16_t LCD16x2_ADDR, uint8_t value){
	uint8_t send_message[2];

	send_message[0] = SET_BL;
	send_message[1] = value;

	HAL_I2C_Master_Transmit(hi2c, LCD16x2_ADDR, send_message, 2, HAL_MAX_DELAY);
	HAL_Delay(100);
}

/**
  * @brief Get time
  * @note Format: dd:hh:mm:ss
  * @retval none
  */
void get_time(char* string, RTC_HandleTypeDef *hrtc, RTC_TimeTypeDef sTime, RTC_DateTypeDef sDate){
	/*Calculations from: https://stackoverflow.com/questions/10874048/from-milliseconds-to-hour-minutes-seconds-and-milliseconds
	* HAL_GetTick() doesn't work in stop/sleep mode due to the deactivated sysclock
	*/
//	uint32_t milliseconds = HAL_GetTick();
//	uint8_t seconds = (uint8_t) (milliseconds / 1000) % 60 ;
//	uint8_t minutes = (uint8_t) ((milliseconds / (1000*60)) % 60);
//	uint8_t hours   = (uint8_t) ((milliseconds / (1000*60*60)) % 24);
//	uint8_t days   = (uint8_t) ((milliseconds / (1000*60*60*24)));
//	//sprintf(string, "%d:%d:%d:%d:%d", days, hours, minutes, seconds, milliseconds); //with milliseconds
//	sprintf(string, "%02d:%02d:%02d:%02d", days, hours, minutes, seconds);	//without milliseconds

	/*Use feature from stm. Realtime clock, counts even in stop/sleep mode*/
	HAL_RTC_GetTime(hrtc, &sTime, RTC_FORMAT_BIN);
	HAL_RTC_GetDate(hrtc, &sDate, RTC_FORMAT_BIN);
	sprintf(string, "%02d:%02d:%02d:%02d", sDate.WeekDay-1, sTime.Hours, sTime.Minutes, sTime.Seconds);	//without milliseconds
}

/**
  * @brief Get time in seconds
  * @note Better to be compared to other times
  * @retval none
  */
void get_time_in_int(uint16_t* time, RTC_HandleTypeDef *hrtc, RTC_TimeTypeDef sTime, RTC_DateTypeDef sDate){
	HAL_RTC_GetTime(hrtc, &sTime, RTC_FORMAT_BIN);
	HAL_RTC_GetDate(hrtc, &sDate, RTC_FORMAT_BIN);
	*time = sTime.Seconds + sTime.Minutes*60 + sTime.Hours*60*60;
	// maybe weekday and month have also be added or rtc reset after some time
}

/**
  * @brief Decides if plant should be watered based on the time of last watering
  * @retval bool
  */
int should_water(uint16_t* previous_time, uint16_t waittime, RTC_HandleTypeDef *hrtc, RTC_TimeTypeDef sTime, RTC_DateTypeDef sDate){
	uint16_t currenttime=0;

	get_time_in_int(&currenttime, hrtc, sTime, sDate);

	if(*previous_time + waittime < currenttime){
		get_time_in_int(previous_time, hrtc, sTime, sDate); // write current time in variable previous_time of watering
		return 0;
	}
//	else if(sTime.Hours>20) return 0; //dont't water after 20:00. Real time has to be initialized.
	else return 1;
}

/**
  * @brief Clears all contents of screen
  * @retval Hal status
  */
HAL_StatusTypeDef clear_screen(I2C_HandleTypeDef *hi2c, uint16_t LCD16x2_ADDR){
	  uint8_t send_message[] = {LCD_CLR};
	  if(HAL_I2C_Master_Transmit(hi2c, LCD16x2_ADDR , send_message, 1, HAL_MAX_DELAY) != HAL_OK) return HAL_ERROR;
	  HAL_Delay(100);
	  return HAL_OK;
}
