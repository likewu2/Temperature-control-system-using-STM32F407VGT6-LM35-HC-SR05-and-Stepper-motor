################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: xPacks arm-none-eabi-gcc
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Core/system/src/cmsis/vectors_stm32f407xx.c 

OBJS += \
./Core/system/src/cmsis/vectors_stm32f407xx.o 

C_DEPS += \
./Core/system/src/cmsis/vectors_stm32f407xx.d 


# Each subdirectory must supply rules for building sources it contributes
Core/system/src/cmsis/%.o Core/system/src/cmsis/%.su: ../Core/system/src/cmsis/%.c Core/system/src/cmsis/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32F407xx -c -I../Core/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc -I../Drivers/STM32F4xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32F4xx/Include -I../Drivers/CMSIS/Include -I../Core/system/include -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfloat-abi=soft -mthumb -o "$@"

clean: clean-Core-2f-system-2f-src-2f-cmsis

clean-Core-2f-system-2f-src-2f-cmsis:
	-$(RM) ./Core/system/src/cmsis/vectors_stm32f407xx.d ./Core/system/src/cmsis/vectors_stm32f407xx.o ./Core/system/src/cmsis/vectors_stm32f407xx.su

.PHONY: clean-Core-2f-system-2f-src-2f-cmsis

