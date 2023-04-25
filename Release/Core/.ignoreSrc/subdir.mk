################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (10.3-2021.10)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Core/.ignoreSrc/hooks.c \
../Core/.ignoreSrc/itoa.c \
../Core/.ignoreSrc/main.c \
../Core/.ignoreSrc/stm32l1xx_hal_msp.c \
../Core/.ignoreSrc/stm32l1xx_it.c \
../Core/.ignoreSrc/syscalls.c \
../Core/.ignoreSrc/sysmem.c \
../Core/.ignoreSrc/system_stm32l1xx.c 

OBJS += \
./Core/.ignoreSrc/hooks.o \
./Core/.ignoreSrc/itoa.o \
./Core/.ignoreSrc/main.o \
./Core/.ignoreSrc/stm32l1xx_hal_msp.o \
./Core/.ignoreSrc/stm32l1xx_it.o \
./Core/.ignoreSrc/syscalls.o \
./Core/.ignoreSrc/sysmem.o \
./Core/.ignoreSrc/system_stm32l1xx.o 

C_DEPS += \
./Core/.ignoreSrc/hooks.d \
./Core/.ignoreSrc/itoa.d \
./Core/.ignoreSrc/main.d \
./Core/.ignoreSrc/stm32l1xx_hal_msp.d \
./Core/.ignoreSrc/stm32l1xx_it.d \
./Core/.ignoreSrc/syscalls.d \
./Core/.ignoreSrc/sysmem.d \
./Core/.ignoreSrc/system_stm32l1xx.d 


# Each subdirectory must supply rules for building sources it contributes
Core/.ignoreSrc/%.o Core/.ignoreSrc/%.su Core/.ignoreSrc/%.cyclo: ../Core/.ignoreSrc/%.c Core/.ignoreSrc/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m3 -std=gnu11 -DUSE_HAL_DRIVER -DSTM32L152xE -c -I../Core/Inc -I../Drivers/STM32L1xx_HAL_Driver/Inc -I../Drivers/STM32L1xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32L1xx/Include -I../Drivers/CMSIS/Include -Os -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfloat-abi=soft -mthumb -o "$@"

clean: clean-Core-2f--2e-ignoreSrc

clean-Core-2f--2e-ignoreSrc:
	-$(RM) ./Core/.ignoreSrc/hooks.cyclo ./Core/.ignoreSrc/hooks.d ./Core/.ignoreSrc/hooks.o ./Core/.ignoreSrc/hooks.su ./Core/.ignoreSrc/itoa.cyclo ./Core/.ignoreSrc/itoa.d ./Core/.ignoreSrc/itoa.o ./Core/.ignoreSrc/itoa.su ./Core/.ignoreSrc/main.cyclo ./Core/.ignoreSrc/main.d ./Core/.ignoreSrc/main.o ./Core/.ignoreSrc/main.su ./Core/.ignoreSrc/stm32l1xx_hal_msp.cyclo ./Core/.ignoreSrc/stm32l1xx_hal_msp.d ./Core/.ignoreSrc/stm32l1xx_hal_msp.o ./Core/.ignoreSrc/stm32l1xx_hal_msp.su ./Core/.ignoreSrc/stm32l1xx_it.cyclo ./Core/.ignoreSrc/stm32l1xx_it.d ./Core/.ignoreSrc/stm32l1xx_it.o ./Core/.ignoreSrc/stm32l1xx_it.su ./Core/.ignoreSrc/syscalls.cyclo ./Core/.ignoreSrc/syscalls.d ./Core/.ignoreSrc/syscalls.o ./Core/.ignoreSrc/syscalls.su ./Core/.ignoreSrc/sysmem.cyclo ./Core/.ignoreSrc/sysmem.d ./Core/.ignoreSrc/sysmem.o ./Core/.ignoreSrc/sysmem.su ./Core/.ignoreSrc/system_stm32l1xx.cyclo ./Core/.ignoreSrc/system_stm32l1xx.d ./Core/.ignoreSrc/system_stm32l1xx.o ./Core/.ignoreSrc/system_stm32l1xx.su

.PHONY: clean-Core-2f--2e-ignoreSrc

