/*
 * additional_functions.c
 *
 *  Created on: 20.04.2023
 *      Author: Thilo Danner
 */


#include "main.h"


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
	HAL_Delay(5000);
	return HAL_OK;
}


HAL_StatusTypeDef timer_interrupt_handler(	UART_HandleTypeDef* huart, ADC_HandleTypeDef* hadc, I2C_HandleTypeDef *hi2c,
											uint16_t waittime, uint16_t* last_time_watered,
											uint16_t LCD16x2_ADDR, RTC_HandleTypeDef *hrtc, RTC_TimeTypeDef sTime, RTC_DateTypeDef sDate){
	uint8_t send_message[ARRAYSIZE] = {0};
	uint16_t adc_value = 0;
	HAL_StatusTypeDef returnmessage = HAL_ERROR;
	float voltage;

//	HAL_GPIO_TogglePin(LD2_GPIO_Port, LD2_Pin);

	sprintf((char *) send_message, "Leaving Stop-Mode!\r\n");
	HAL_UART_Transmit(huart, send_message, strlen((char *) send_message), HAL_MAX_DELAY);


	  //Get Voltage from Moisture Sensor
	  if(HAL_ADC_Start(hadc) != HAL_OK){
		  sprintf((char *) send_message, "ADC not OK!\r\n");
		  HAL_UART_Transmit(huart, send_message, strlen((char *) send_message), HAL_MAX_DELAY);
		  return HAL_ERROR;
	  }
	  else{
		  returnmessage = HAL_ADC_PollForConversion(hadc, 2*1000);

		  if (returnmessage == HAL_OK){
			  adc_value = HAL_ADC_GetValue(hadc);
			  voltage = (adc_value / 4096.0f) * 3.3f;
			  sprintf((char *)send_message, "Voltage:\t\r\n%lfV\r\n", voltage);
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
	  if(voltage > MIN_MOISTURE_VOLTAGE && !should_water((uint16_t*) last_time_watered, (uint16_t) waittime, hrtc, sTime, sDate)){
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
	  }

	  return HAL_OK;
}

HAL_StatusTypeDef uart_interrupt_handler(char uart_message, UART_HandleTypeDef* huart, I2C_HandleTypeDef* hi2c, uint16_t LCD16x2_ADDR){
	uint8_t send_message[ARRAYSIZE] = {0};

	if(uart_message == 'y'){
		HAL_GPIO_WritePin(Optokoppler_GPIO_Port, Optokoppler_Pin, GPIO_PIN_SET);
		HAL_GPIO_WritePin(LD2_GPIO_Port, LD2_Pin, GPIO_PIN_SET);
		sprintf((char *) send_message, "Pump: on\r\n");
		HAL_UART_Transmit(huart, send_message, strlen((char*)send_message), HAL_MAX_DELAY);
		send_to_display(hi2c, (char*) send_message, strlen((char *) send_message)-2, LCD16x2_ADDR);
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

void get_time(char* string, RTC_HandleTypeDef *hrtc, RTC_TimeTypeDef sTime, RTC_DateTypeDef sDate){
	/*Calculations from: https://stackoverflow.com/questions/10874048/from-milliseconds-to-hour-minutes-seconds-and-milliseconds
	HAL_GetTick() doesn't work in stop/sleep mode due to the deactivated sysclock
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
	sprintf(string, "%02d:%02d:%02d:%02d", sDate.WeekDay, sTime.Hours, sTime.Minutes, sTime.Seconds);	//without milliseconds
}

void get_time_in_int(uint16_t* time, RTC_HandleTypeDef *hrtc, RTC_TimeTypeDef sTime, RTC_DateTypeDef sDate){
	HAL_RTC_GetTime(hrtc, &sTime, RTC_FORMAT_BIN);
	HAL_RTC_GetDate(hrtc, &sDate, RTC_FORMAT_BIN);
	*time = sTime.Seconds + sTime.Minutes*60 + sTime.Hours*60*60;
	// maybe weekday and month have also be added or rtc reset after some time
}

int should_water(uint16_t* previous_time, uint16_t waittime, RTC_HandleTypeDef *hrtc, RTC_TimeTypeDef sTime, RTC_DateTypeDef sDate){
	uint16_t* currenttime=0;
	HAL_RTC_GetTime(hrtc, &sTime, RTC_FORMAT_BIN);
	HAL_RTC_GetDate(hrtc, &sDate, RTC_FORMAT_BIN);

	get_time_in_int((uint16_t*) currenttime, hrtc, sTime, sDate);

	if(*previous_time + waittime > *currenttime) return 1;
//	else if(sTime.Hours>20) return 0; //dont't water after 20:00. Real time has to be initialized
	else {
		get_time_in_int(previous_time, hrtc, sTime, sDate); // write current time in variable previous_time
		return 0;
	}
}

HAL_StatusTypeDef clear_screen(I2C_HandleTypeDef *hi2c, uint16_t LCD16x2_ADDR){
	  uint8_t send_message[] = {LCD_CLR};
	  if(HAL_I2C_Master_Transmit(hi2c, LCD16x2_ADDR , send_message, 1, HAL_MAX_DELAY) != HAL_OK) return HAL_ERROR;
	  return HAL_OK;
}
