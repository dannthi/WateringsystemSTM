################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (10.3-2021.10)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Core/.ignoreSrc/avr/dtostrf.c 

OBJS += \
./Core/.ignoreSrc/avr/dtostrf.o 

C_DEPS += \
./Core/.ignoreSrc/avr/dtostrf.d 


# Each subdirectory must supply rules for building sources it contributes
Core/.ignoreSrc/avr/%.o Core/.ignoreSrc/avr/%.su Core/.ignoreSrc/avr/%.cyclo: ../Core/.ignoreSrc/avr/%.c Core/.ignoreSrc/avr/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m3 -std=gnu11 -DUSE_HAL_DRIVER -DSTM32L152xE -c -I../Core/Inc -I../Drivers/STM32L1xx_HAL_Driver/Inc -I../Drivers/STM32L1xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32L1xx/Include -I../Drivers/CMSIS/Include -Os -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfloat-abi=soft -mthumb -o "$@"

clean: clean-Core-2f--2e-ignoreSrc-2f-avr

clean-Core-2f--2e-ignoreSrc-2f-avr:
	-$(RM) ./Core/.ignoreSrc/avr/dtostrf.cyclo ./Core/.ignoreSrc/avr/dtostrf.d ./Core/.ignoreSrc/avr/dtostrf.o ./Core/.ignoreSrc/avr/dtostrf.su

.PHONY: clean-Core-2f--2e-ignoreSrc-2f-avr

