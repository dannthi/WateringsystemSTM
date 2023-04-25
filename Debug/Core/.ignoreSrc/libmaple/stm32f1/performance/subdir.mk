################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (10.3-2021.10)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
S_UPPER_SRCS += \
../Core/.ignoreSrc/libmaple/stm32f1/performance/isrs.S \
../Core/.ignoreSrc/libmaple/stm32f1/performance/vector_table.S 

OBJS += \
./Core/.ignoreSrc/libmaple/stm32f1/performance/isrs.o \
./Core/.ignoreSrc/libmaple/stm32f1/performance/vector_table.o 

S_UPPER_DEPS += \
./Core/.ignoreSrc/libmaple/stm32f1/performance/isrs.d \
./Core/.ignoreSrc/libmaple/stm32f1/performance/vector_table.d 


# Each subdirectory must supply rules for building sources it contributes
Core/.ignoreSrc/libmaple/stm32f1/performance/%.o: ../Core/.ignoreSrc/libmaple/stm32f1/performance/%.S Core/.ignoreSrc/libmaple/stm32f1/performance/subdir.mk
	arm-none-eabi-gcc -mcpu=cortex-m3 -g3 -DDEBUG -c -x assembler-with-cpp -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfloat-abi=soft -mthumb -o "$@" "$<"

clean: clean-Core-2f--2e-ignoreSrc-2f-libmaple-2f-stm32f1-2f-performance

clean-Core-2f--2e-ignoreSrc-2f-libmaple-2f-stm32f1-2f-performance:
	-$(RM) ./Core/.ignoreSrc/libmaple/stm32f1/performance/isrs.d ./Core/.ignoreSrc/libmaple/stm32f1/performance/isrs.o ./Core/.ignoreSrc/libmaple/stm32f1/performance/vector_table.d ./Core/.ignoreSrc/libmaple/stm32f1/performance/vector_table.o

.PHONY: clean-Core-2f--2e-ignoreSrc-2f-libmaple-2f-stm32f1-2f-performance

