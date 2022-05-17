################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (10.3-2021.10)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Core/system/src/newlib/assert.c \
../Core/system/src/newlib/exit.c \
../Core/system/src/newlib/sbrk.c \
../Core/system/src/newlib/startup.c \
../Core/system/src/newlib/syscalls.c 

OBJS += \
./Core/system/src/newlib/assert.o \
./Core/system/src/newlib/exit.o \
./Core/system/src/newlib/sbrk.o \
./Core/system/src/newlib/startup.o \
./Core/system/src/newlib/syscalls.o 

C_DEPS += \
./Core/system/src/newlib/assert.d \
./Core/system/src/newlib/exit.d \
./Core/system/src/newlib/sbrk.d \
./Core/system/src/newlib/startup.d \
./Core/system/src/newlib/syscalls.d 


# Each subdirectory must supply rules for building sources it contributes
Core/system/src/newlib/%.o Core/system/src/newlib/%.su: ../Core/system/src/newlib/%.c Core/system/src/newlib/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32F407xx -c -I../Core/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32F4xx/Include -I../Drivers/CMSIS/Include -I../Core/system/include -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfloat-abi=soft -mthumb -o "$@"

clean: clean-Core-2f-system-2f-src-2f-newlib

clean-Core-2f-system-2f-src-2f-newlib:
	-$(RM) ./Core/system/src/newlib/assert.d ./Core/system/src/newlib/assert.o ./Core/system/src/newlib/assert.su ./Core/system/src/newlib/exit.d ./Core/system/src/newlib/exit.o ./Core/system/src/newlib/exit.su ./Core/system/src/newlib/sbrk.d ./Core/system/src/newlib/sbrk.o ./Core/system/src/newlib/sbrk.su ./Core/system/src/newlib/startup.d ./Core/system/src/newlib/startup.o ./Core/system/src/newlib/startup.su ./Core/system/src/newlib/syscalls.d ./Core/system/src/newlib/syscalls.o ./Core/system/src/newlib/syscalls.su

.PHONY: clean-Core-2f-system-2f-src-2f-newlib

