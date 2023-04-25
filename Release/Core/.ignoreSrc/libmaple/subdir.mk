################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (10.3-2021.10)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Core/.ignoreSrc/libmaple/adc.c \
../Core/.ignoreSrc/libmaple/adc_f1.c \
../Core/.ignoreSrc/libmaple/bkp_f1.c \
../Core/.ignoreSrc/libmaple/dac.c \
../Core/.ignoreSrc/libmaple/dma.c \
../Core/.ignoreSrc/libmaple/dma_f1.c \
../Core/.ignoreSrc/libmaple/exti.c \
../Core/.ignoreSrc/libmaple/exti_f1.c \
../Core/.ignoreSrc/libmaple/flash.c \
../Core/.ignoreSrc/libmaple/fsmc_f1.c \
../Core/.ignoreSrc/libmaple/gpio.c \
../Core/.ignoreSrc/libmaple/gpio_f1.c \
../Core/.ignoreSrc/libmaple/i2c.c \
../Core/.ignoreSrc/libmaple/i2c_f1.c \
../Core/.ignoreSrc/libmaple/iwdg.c \
../Core/.ignoreSrc/libmaple/nvic.c \
../Core/.ignoreSrc/libmaple/pwr.c \
../Core/.ignoreSrc/libmaple/rcc.c \
../Core/.ignoreSrc/libmaple/rcc_f1.c \
../Core/.ignoreSrc/libmaple/spi.c \
../Core/.ignoreSrc/libmaple/spi_f1.c \
../Core/.ignoreSrc/libmaple/systick.c \
../Core/.ignoreSrc/libmaple/timer.c \
../Core/.ignoreSrc/libmaple/timer_f1.c \
../Core/.ignoreSrc/libmaple/usart.c \
../Core/.ignoreSrc/libmaple/usart_f1.c \
../Core/.ignoreSrc/libmaple/usart_private.c \
../Core/.ignoreSrc/libmaple/util.c 

S_UPPER_SRCS += \
../Core/.ignoreSrc/libmaple/exc.S 

OBJS += \
./Core/.ignoreSrc/libmaple/adc.o \
./Core/.ignoreSrc/libmaple/adc_f1.o \
./Core/.ignoreSrc/libmaple/bkp_f1.o \
./Core/.ignoreSrc/libmaple/dac.o \
./Core/.ignoreSrc/libmaple/dma.o \
./Core/.ignoreSrc/libmaple/dma_f1.o \
./Core/.ignoreSrc/libmaple/exc.o \
./Core/.ignoreSrc/libmaple/exti.o \
./Core/.ignoreSrc/libmaple/exti_f1.o \
./Core/.ignoreSrc/libmaple/flash.o \
./Core/.ignoreSrc/libmaple/fsmc_f1.o \
./Core/.ignoreSrc/libmaple/gpio.o \
./Core/.ignoreSrc/libmaple/gpio_f1.o \
./Core/.ignoreSrc/libmaple/i2c.o \
./Core/.ignoreSrc/libmaple/i2c_f1.o \
./Core/.ignoreSrc/libmaple/iwdg.o \
./Core/.ignoreSrc/libmaple/nvic.o \
./Core/.ignoreSrc/libmaple/pwr.o \
./Core/.ignoreSrc/libmaple/rcc.o \
./Core/.ignoreSrc/libmaple/rcc_f1.o \
./Core/.ignoreSrc/libmaple/spi.o \
./Core/.ignoreSrc/libmaple/spi_f1.o \
./Core/.ignoreSrc/libmaple/systick.o \
./Core/.ignoreSrc/libmaple/timer.o \
./Core/.ignoreSrc/libmaple/timer_f1.o \
./Core/.ignoreSrc/libmaple/usart.o \
./Core/.ignoreSrc/libmaple/usart_f1.o \
./Core/.ignoreSrc/libmaple/usart_private.o \
./Core/.ignoreSrc/libmaple/util.o 

S_UPPER_DEPS += \
./Core/.ignoreSrc/libmaple/exc.d 

C_DEPS += \
./Core/.ignoreSrc/libmaple/adc.d \
./Core/.ignoreSrc/libmaple/adc_f1.d \
./Core/.ignoreSrc/libmaple/bkp_f1.d \
./Core/.ignoreSrc/libmaple/dac.d \
./Core/.ignoreSrc/libmaple/dma.d \
./Core/.ignoreSrc/libmaple/dma_f1.d \
./Core/.ignoreSrc/libmaple/exti.d \
./Core/.ignoreSrc/libmaple/exti_f1.d \
./Core/.ignoreSrc/libmaple/flash.d \
./Core/.ignoreSrc/libmaple/fsmc_f1.d \
./Core/.ignoreSrc/libmaple/gpio.d \
./Core/.ignoreSrc/libmaple/gpio_f1.d \
./Core/.ignoreSrc/libmaple/i2c.d \
./Core/.ignoreSrc/libmaple/i2c_f1.d \
./Core/.ignoreSrc/libmaple/iwdg.d \
./Core/.ignoreSrc/libmaple/nvic.d \
./Core/.ignoreSrc/libmaple/pwr.d \
./Core/.ignoreSrc/libmaple/rcc.d \
./Core/.ignoreSrc/libmaple/rcc_f1.d \
./Core/.ignoreSrc/libmaple/spi.d \
./Core/.ignoreSrc/libmaple/spi_f1.d \
./Core/.ignoreSrc/libmaple/systick.d \
./Core/.ignoreSrc/libmaple/timer.d \
./Core/.ignoreSrc/libmaple/timer_f1.d \
./Core/.ignoreSrc/libmaple/usart.d \
./Core/.ignoreSrc/libmaple/usart_f1.d \
./Core/.ignoreSrc/libmaple/usart_private.d \
./Core/.ignoreSrc/libmaple/util.d 


# Each subdirectory must supply rules for building sources it contributes
Core/.ignoreSrc/libmaple/%.o Core/.ignoreSrc/libmaple/%.su Core/.ignoreSrc/libmaple/%.cyclo: ../Core/.ignoreSrc/libmaple/%.c Core/.ignoreSrc/libmaple/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m3 -std=gnu11 -DUSE_HAL_DRIVER -DSTM32L152xE -c -I../Core/Inc -I../Drivers/STM32L1xx_HAL_Driver/Inc -I../Drivers/STM32L1xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32L1xx/Include -I../Drivers/CMSIS/Include -Os -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfloat-abi=soft -mthumb -o "$@"
Core/.ignoreSrc/libmaple/%.o: ../Core/.ignoreSrc/libmaple/%.S Core/.ignoreSrc/libmaple/subdir.mk
	arm-none-eabi-gcc -mcpu=cortex-m3 -c -x assembler-with-cpp -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfloat-abi=soft -mthumb -o "$@" "$<"

clean: clean-Core-2f--2e-ignoreSrc-2f-libmaple

clean-Core-2f--2e-ignoreSrc-2f-libmaple:
	-$(RM) ./Core/.ignoreSrc/libmaple/adc.cyclo ./Core/.ignoreSrc/libmaple/adc.d ./Core/.ignoreSrc/libmaple/adc.o ./Core/.ignoreSrc/libmaple/adc.su ./Core/.ignoreSrc/libmaple/adc_f1.cyclo ./Core/.ignoreSrc/libmaple/adc_f1.d ./Core/.ignoreSrc/libmaple/adc_f1.o ./Core/.ignoreSrc/libmaple/adc_f1.su ./Core/.ignoreSrc/libmaple/bkp_f1.cyclo ./Core/.ignoreSrc/libmaple/bkp_f1.d ./Core/.ignoreSrc/libmaple/bkp_f1.o ./Core/.ignoreSrc/libmaple/bkp_f1.su ./Core/.ignoreSrc/libmaple/dac.cyclo ./Core/.ignoreSrc/libmaple/dac.d ./Core/.ignoreSrc/libmaple/dac.o ./Core/.ignoreSrc/libmaple/dac.su ./Core/.ignoreSrc/libmaple/dma.cyclo ./Core/.ignoreSrc/libmaple/dma.d ./Core/.ignoreSrc/libmaple/dma.o ./Core/.ignoreSrc/libmaple/dma.su ./Core/.ignoreSrc/libmaple/dma_f1.cyclo ./Core/.ignoreSrc/libmaple/dma_f1.d ./Core/.ignoreSrc/libmaple/dma_f1.o ./Core/.ignoreSrc/libmaple/dma_f1.su ./Core/.ignoreSrc/libmaple/exc.d ./Core/.ignoreSrc/libmaple/exc.o ./Core/.ignoreSrc/libmaple/exti.cyclo ./Core/.ignoreSrc/libmaple/exti.d ./Core/.ignoreSrc/libmaple/exti.o ./Core/.ignoreSrc/libmaple/exti.su ./Core/.ignoreSrc/libmaple/exti_f1.cyclo ./Core/.ignoreSrc/libmaple/exti_f1.d ./Core/.ignoreSrc/libmaple/exti_f1.o ./Core/.ignoreSrc/libmaple/exti_f1.su ./Core/.ignoreSrc/libmaple/flash.cyclo ./Core/.ignoreSrc/libmaple/flash.d ./Core/.ignoreSrc/libmaple/flash.o ./Core/.ignoreSrc/libmaple/flash.su ./Core/.ignoreSrc/libmaple/fsmc_f1.cyclo ./Core/.ignoreSrc/libmaple/fsmc_f1.d ./Core/.ignoreSrc/libmaple/fsmc_f1.o ./Core/.ignoreSrc/libmaple/fsmc_f1.su ./Core/.ignoreSrc/libmaple/gpio.cyclo ./Core/.ignoreSrc/libmaple/gpio.d ./Core/.ignoreSrc/libmaple/gpio.o ./Core/.ignoreSrc/libmaple/gpio.su ./Core/.ignoreSrc/libmaple/gpio_f1.cyclo ./Core/.ignoreSrc/libmaple/gpio_f1.d ./Core/.ignoreSrc/libmaple/gpio_f1.o ./Core/.ignoreSrc/libmaple/gpio_f1.su ./Core/.ignoreSrc/libmaple/i2c.cyclo ./Core/.ignoreSrc/libmaple/i2c.d ./Core/.ignoreSrc/libmaple/i2c.o ./Core/.ignoreSrc/libmaple/i2c.su ./Core/.ignoreSrc/libmaple/i2c_f1.cyclo ./Core/.ignoreSrc/libmaple/i2c_f1.d ./Core/.ignoreSrc/libmaple/i2c_f1.o ./Core/.ignoreSrc/libmaple/i2c_f1.su ./Core/.ignoreSrc/libmaple/iwdg.cyclo ./Core/.ignoreSrc/libmaple/iwdg.d ./Core/.ignoreSrc/libmaple/iwdg.o ./Core/.ignoreSrc/libmaple/iwdg.su ./Core/.ignoreSrc/libmaple/nvic.cyclo ./Core/.ignoreSrc/libmaple/nvic.d ./Core/.ignoreSrc/libmaple/nvic.o ./Core/.ignoreSrc/libmaple/nvic.su ./Core/.ignoreSrc/libmaple/pwr.cyclo ./Core/.ignoreSrc/libmaple/pwr.d ./Core/.ignoreSrc/libmaple/pwr.o ./Core/.ignoreSrc/libmaple/pwr.su ./Core/.ignoreSrc/libmaple/rcc.cyclo ./Core/.ignoreSrc/libmaple/rcc.d ./Core/.ignoreSrc/libmaple/rcc.o ./Core/.ignoreSrc/libmaple/rcc.su ./Core/.ignoreSrc/libmaple/rcc_f1.cyclo ./Core/.ignoreSrc/libmaple/rcc_f1.d ./Core/.ignoreSrc/libmaple/rcc_f1.o ./Core/.ignoreSrc/libmaple/rcc_f1.su ./Core/.ignoreSrc/libmaple/spi.cyclo ./Core/.ignoreSrc/libmaple/spi.d ./Core/.ignoreSrc/libmaple/spi.o ./Core/.ignoreSrc/libmaple/spi.su ./Core/.ignoreSrc/libmaple/spi_f1.cyclo ./Core/.ignoreSrc/libmaple/spi_f1.d ./Core/.ignoreSrc/libmaple/spi_f1.o ./Core/.ignoreSrc/libmaple/spi_f1.su ./Core/.ignoreSrc/libmaple/systick.cyclo ./Core/.ignoreSrc/libmaple/systick.d ./Core/.ignoreSrc/libmaple/systick.o ./Core/.ignoreSrc/libmaple/systick.su ./Core/.ignoreSrc/libmaple/timer.cyclo ./Core/.ignoreSrc/libmaple/timer.d ./Core/.ignoreSrc/libmaple/timer.o ./Core/.ignoreSrc/libmaple/timer.su ./Core/.ignoreSrc/libmaple/timer_f1.cyclo ./Core/.ignoreSrc/libmaple/timer_f1.d ./Core/.ignoreSrc/libmaple/timer_f1.o ./Core/.ignoreSrc/libmaple/timer_f1.su ./Core/.ignoreSrc/libmaple/usart.cyclo ./Core/.ignoreSrc/libmaple/usart.d ./Core/.ignoreSrc/libmaple/usart.o ./Core/.ignoreSrc/libmaple/usart.su ./Core/.ignoreSrc/libmaple/usart_f1.cyclo ./Core/.ignoreSrc/libmaple/usart_f1.d ./Core/.ignoreSrc/libmaple/usart_f1.o ./Core/.ignoreSrc/libmaple/usart_f1.su ./Core/.ignoreSrc/libmaple/usart_private.cyclo ./Core/.ignoreSrc/libmaple/usart_private.d ./Core/.ignoreSrc/libmaple/usart_private.o ./Core/.ignoreSrc/libmaple/usart_private.su ./Core/.ignoreSrc/libmaple/util.cyclo ./Core/.ignoreSrc/libmaple/util.d ./Core/.ignoreSrc/libmaple/util.o ./Core/.ignoreSrc/libmaple/util.su

.PHONY: clean-Core-2f--2e-ignoreSrc-2f-libmaple

