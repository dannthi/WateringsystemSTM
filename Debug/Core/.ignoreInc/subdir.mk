################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (10.3-2021.10)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Core/.ignoreInc/hooks.c 

OBJS += \
./Core/.ignoreInc/hooks.o 

C_DEPS += \
./Core/.ignoreInc/hooks.d 


# Each subdirectory must supply rules for building sources it contributes
Core/.ignoreInc/%.o Core/.ignoreInc/%.su Core/.ignoreInc/%.cyclo: ../Core/.ignoreInc/%.c Core/.ignoreInc/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m3 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32L152xE -c -I../Core/Inc -I../Drivers/STM32L1xx_HAL_Driver/Inc -I../Drivers/STM32L1xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32L1xx/Include -I../Drivers/CMSIS/Include -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfloat-abi=soft -mthumb -o "$@"

clean: clean-Core-2f--2e-ignoreInc

clean-Core-2f--2e-ignoreInc:
	-$(RM) ./Core/.ignoreInc/hooks.cyclo ./Core/.ignoreInc/hooks.d ./Core/.ignoreInc/hooks.o ./Core/.ignoreInc/hooks.su

.PHONY: clean-Core-2f--2e-ignoreInc

