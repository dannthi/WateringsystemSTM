################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (10.3-2021.10)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Core/.ignoreSrc/libmaple/usb/usb_lib/usb_core.c \
../Core/.ignoreSrc/libmaple/usb/usb_lib/usb_init.c \
../Core/.ignoreSrc/libmaple/usb/usb_lib/usb_mem.c \
../Core/.ignoreSrc/libmaple/usb/usb_lib/usb_regs.c 

OBJS += \
./Core/.ignoreSrc/libmaple/usb/usb_lib/usb_core.o \
./Core/.ignoreSrc/libmaple/usb/usb_lib/usb_init.o \
./Core/.ignoreSrc/libmaple/usb/usb_lib/usb_mem.o \
./Core/.ignoreSrc/libmaple/usb/usb_lib/usb_regs.o 

C_DEPS += \
./Core/.ignoreSrc/libmaple/usb/usb_lib/usb_core.d \
./Core/.ignoreSrc/libmaple/usb/usb_lib/usb_init.d \
./Core/.ignoreSrc/libmaple/usb/usb_lib/usb_mem.d \
./Core/.ignoreSrc/libmaple/usb/usb_lib/usb_regs.d 


# Each subdirectory must supply rules for building sources it contributes
Core/.ignoreSrc/libmaple/usb/usb_lib/%.o Core/.ignoreSrc/libmaple/usb/usb_lib/%.su Core/.ignoreSrc/libmaple/usb/usb_lib/%.cyclo: ../Core/.ignoreSrc/libmaple/usb/usb_lib/%.c Core/.ignoreSrc/libmaple/usb/usb_lib/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m3 -std=gnu11 -DUSE_HAL_DRIVER -DSTM32L152xE -c -I../Core/Inc -I../Drivers/STM32L1xx_HAL_Driver/Inc -I../Drivers/STM32L1xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32L1xx/Include -I../Drivers/CMSIS/Include -Os -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfloat-abi=soft -mthumb -o "$@"

clean: clean-Core-2f--2e-ignoreSrc-2f-libmaple-2f-usb-2f-usb_lib

clean-Core-2f--2e-ignoreSrc-2f-libmaple-2f-usb-2f-usb_lib:
	-$(RM) ./Core/.ignoreSrc/libmaple/usb/usb_lib/usb_core.cyclo ./Core/.ignoreSrc/libmaple/usb/usb_lib/usb_core.d ./Core/.ignoreSrc/libmaple/usb/usb_lib/usb_core.o ./Core/.ignoreSrc/libmaple/usb/usb_lib/usb_core.su ./Core/.ignoreSrc/libmaple/usb/usb_lib/usb_init.cyclo ./Core/.ignoreSrc/libmaple/usb/usb_lib/usb_init.d ./Core/.ignoreSrc/libmaple/usb/usb_lib/usb_init.o ./Core/.ignoreSrc/libmaple/usb/usb_lib/usb_init.su ./Core/.ignoreSrc/libmaple/usb/usb_lib/usb_mem.cyclo ./Core/.ignoreSrc/libmaple/usb/usb_lib/usb_mem.d ./Core/.ignoreSrc/libmaple/usb/usb_lib/usb_mem.o ./Core/.ignoreSrc/libmaple/usb/usb_lib/usb_mem.su ./Core/.ignoreSrc/libmaple/usb/usb_lib/usb_regs.cyclo ./Core/.ignoreSrc/libmaple/usb/usb_lib/usb_regs.d ./Core/.ignoreSrc/libmaple/usb/usb_lib/usb_regs.o ./Core/.ignoreSrc/libmaple/usb/usb_lib/usb_regs.su

.PHONY: clean-Core-2f--2e-ignoreSrc-2f-libmaple-2f-usb-2f-usb_lib

