################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (10.3-2021.10)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Core/.ignoreSrc/stm32f1/util_hooks.c 

OBJS += \
./Core/.ignoreSrc/stm32f1/util_hooks.o 

C_DEPS += \
./Core/.ignoreSrc/stm32f1/util_hooks.d 


# Each subdirectory must supply rules for building sources it contributes
Core/.ignoreSrc/stm32f1/%.o Core/.ignoreSrc/stm32f1/%.su Core/.ignoreSrc/stm32f1/%.cyclo: ../Core/.ignoreSrc/stm32f1/%.c Core/.ignoreSrc/stm32f1/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m3 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32L152xE -c -I../Core/Inc -I../Drivers/STM32L1xx_HAL_Driver/Inc -I../Drivers/STM32L1xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32L1xx/Include -I../Drivers/CMSIS/Include -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfloat-abi=soft -mthumb -o "$@"

clean: clean-Core-2f--2e-ignoreSrc-2f-stm32f1

clean-Core-2f--2e-ignoreSrc-2f-stm32f1:
	-$(RM) ./Core/.ignoreSrc/stm32f1/util_hooks.cyclo ./Core/.ignoreSrc/stm32f1/util_hooks.d ./Core/.ignoreSrc/stm32f1/util_hooks.o ./Core/.ignoreSrc/stm32f1/util_hooks.su

.PHONY: clean-Core-2f--2e-ignoreSrc-2f-stm32f1

