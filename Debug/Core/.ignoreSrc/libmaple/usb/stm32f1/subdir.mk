################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (10.3-2021.10)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Core/.ignoreSrc/libmaple/usb/stm32f1/usb.c \
../Core/.ignoreSrc/libmaple/usb/stm32f1/usb_cdcacm.c \
../Core/.ignoreSrc/libmaple/usb/stm32f1/usb_reg_map.c 

OBJS += \
./Core/.ignoreSrc/libmaple/usb/stm32f1/usb.o \
./Core/.ignoreSrc/libmaple/usb/stm32f1/usb_cdcacm.o \
./Core/.ignoreSrc/libmaple/usb/stm32f1/usb_reg_map.o 

C_DEPS += \
./Core/.ignoreSrc/libmaple/usb/stm32f1/usb.d \
./Core/.ignoreSrc/libmaple/usb/stm32f1/usb_cdcacm.d \
./Core/.ignoreSrc/libmaple/usb/stm32f1/usb_reg_map.d 


# Each subdirectory must supply rules for building sources it contributes
Core/.ignoreSrc/libmaple/usb/stm32f1/%.o Core/.ignoreSrc/libmaple/usb/stm32f1/%.su Core/.ignoreSrc/libmaple/usb/stm32f1/%.cyclo: ../Core/.ignoreSrc/libmaple/usb/stm32f1/%.c Core/.ignoreSrc/libmaple/usb/stm32f1/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m3 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32L152xE -c -I../Core/Inc -I../Drivers/STM32L1xx_HAL_Driver/Inc -I../Drivers/STM32L1xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32L1xx/Include -I../Drivers/CMSIS/Include -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfloat-abi=soft -mthumb -o "$@"

clean: clean-Core-2f--2e-ignoreSrc-2f-libmaple-2f-usb-2f-stm32f1

clean-Core-2f--2e-ignoreSrc-2f-libmaple-2f-usb-2f-stm32f1:
	-$(RM) ./Core/.ignoreSrc/libmaple/usb/stm32f1/usb.cyclo ./Core/.ignoreSrc/libmaple/usb/stm32f1/usb.d ./Core/.ignoreSrc/libmaple/usb/stm32f1/usb.o ./Core/.ignoreSrc/libmaple/usb/stm32f1/usb.su ./Core/.ignoreSrc/libmaple/usb/stm32f1/usb_cdcacm.cyclo ./Core/.ignoreSrc/libmaple/usb/stm32f1/usb_cdcacm.d ./Core/.ignoreSrc/libmaple/usb/stm32f1/usb_cdcacm.o ./Core/.ignoreSrc/libmaple/usb/stm32f1/usb_cdcacm.su ./Core/.ignoreSrc/libmaple/usb/stm32f1/usb_reg_map.cyclo ./Core/.ignoreSrc/libmaple/usb/stm32f1/usb_reg_map.d ./Core/.ignoreSrc/libmaple/usb/stm32f1/usb_reg_map.o ./Core/.ignoreSrc/libmaple/usb/stm32f1/usb_reg_map.su

.PHONY: clean-Core-2f--2e-ignoreSrc-2f-libmaple-2f-usb-2f-stm32f1

