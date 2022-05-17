################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: xPacks arm-none-eabi-gcc
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Core/system/src/diag/trace-impl.c \
../Core/system/src/diag/trace.c 

OBJS += \
./Core/system/src/diag/trace-impl.o \
./Core/system/src/diag/trace.o 

C_DEPS += \
./Core/system/src/diag/trace-impl.d \
./Core/system/src/diag/trace.d 


# Each subdirectory must supply rules for building sources it contributes
Core/system/src/diag/%.o Core/system/src/diag/%.su: ../Core/system/src/diag/%.c Core/system/src/diag/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32F407xx -c -I../Core/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32F4xx/Include -I../Drivers/CMSIS/Include -I../Core/system/include -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfloat-abi=soft -mthumb -o "$@"

clean: clean-Core-2f-system-2f-src-2f-diag

clean-Core-2f-system-2f-src-2f-diag:
	-$(RM) ./Core/system/src/diag/trace-impl.d ./Core/system/src/diag/trace-impl.o ./Core/system/src/diag/trace-impl.su ./Core/system/src/diag/trace.d ./Core/system/src/diag/trace.o ./Core/system/src/diag/trace.su

.PHONY: clean-Core-2f-system-2f-src-2f-diag

