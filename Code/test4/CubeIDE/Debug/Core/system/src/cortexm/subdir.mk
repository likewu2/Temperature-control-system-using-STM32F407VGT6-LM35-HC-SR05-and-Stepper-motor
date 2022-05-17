################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (10.3-2021.10)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Core/system/src/cortexm/exception-handlers.c \
../Core/system/src/cortexm/initialize-hardware.c \
../Core/system/src/cortexm/reset-hardware.c 

OBJS += \
./Core/system/src/cortexm/exception-handlers.o \
./Core/system/src/cortexm/initialize-hardware.o \
./Core/system/src/cortexm/reset-hardware.o 

C_DEPS += \
./Core/system/src/cortexm/exception-handlers.d \
./Core/system/src/cortexm/initialize-hardware.d \
./Core/system/src/cortexm/reset-hardware.d 


# Each subdirectory must supply rules for building sources it contributes
Core/system/src/cortexm/%.o Core/system/src/cortexm/%.su: ../Core/system/src/cortexm/%.c Core/system/src/cortexm/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32F407xx -c -I../Core/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32F4xx/Include -I../Drivers/CMSIS/Include -I../Core/system/include -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"

clean: clean-Core-2f-system-2f-src-2f-cortexm

clean-Core-2f-system-2f-src-2f-cortexm:
	-$(RM) ./Core/system/src/cortexm/exception-handlers.d ./Core/system/src/cortexm/exception-handlers.o ./Core/system/src/cortexm/exception-handlers.su ./Core/system/src/cortexm/initialize-hardware.d ./Core/system/src/cortexm/initialize-hardware.o ./Core/system/src/cortexm/initialize-hardware.su ./Core/system/src/cortexm/reset-hardware.d ./Core/system/src/cortexm/reset-hardware.o ./Core/system/src/cortexm/reset-hardware.su

.PHONY: clean-Core-2f-system-2f-src-2f-cortexm

