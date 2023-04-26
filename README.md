# WateringsystemSTM
Automatic watering system using the STM32 Nucleo L152RE

Hello this is my attempt to an automatic watering system using microcontrollers.

## Basic principles
It uses a low power mode named `stop mode` provided by ST. Advantage is the low power consumption while in stop mode.
The Real-Time-Clock is used to trigger an interrupt after given time. In *timer-trigger-mode* using the voltage from the _Capacitive Soil moisture sensor v1.2_ + an ADC, the controller decides if te pump should be powered.
Also a LCD-Display by Olimex is used to have feedback (and controll).
