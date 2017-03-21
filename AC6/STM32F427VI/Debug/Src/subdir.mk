################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Src/ad7779.c \
../Src/main.c \
../Src/platform_drivers.c \
../Src/stm32f4xx_hal_msp.c \
../Src/stm32f4xx_it.c \
../Src/system_stm32f4xx.c 

OBJS += \
./Src/ad7779.o \
./Src/main.o \
./Src/platform_drivers.o \
./Src/stm32f4xx_hal_msp.o \
./Src/stm32f4xx_it.o \
./Src/system_stm32f4xx.o 

C_DEPS += \
./Src/ad7779.d \
./Src/main.d \
./Src/platform_drivers.d \
./Src/stm32f4xx_hal_msp.d \
./Src/stm32f4xx_it.d \
./Src/system_stm32f4xx.d 


# Each subdirectory must supply rules for building sources it contributes
Src/%.o: ../Src/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: MCU GCC Compiler'
	@echo $(PWD)
	arm-none-eabi-gcc -mcpu=cortex-m4 -mthumb -mfloat-abi=hard -mfpu=fpv4-sp-d16 -D__weak="__attribute__((weak))" -D__packed="__attribute__((__packed__))" -DUSE_HAL_DRIVER -DSTM32F427xx -I../../Inc -I../../Drivers/STM32F4xx_HAL_Driver/Inc -I../../Drivers/STM32F4xx_HAL_Driver/Inc/Legacy -I../../Drivers/CMSIS/Device/ST/STM32F4xx/Include -I../../Drivers/CMSIS/Include -I../../Inc -I"/home/dmitryneuro/workspace_stm32/STM32F427VI/Inc" -I"/home/dmitryneuro/workspace_stm32/STM32F427VI/Drivers/STM32F4xx_HAL_Driver/Inc" -I"/home/dmitryneuro/workspace_stm32/STM32F427VI/Drivers/STM32F4xx_HAL_Driver/Inc/Legacy" -I"/home/dmitryneuro/workspace_stm32/STM32F427VI/Drivers/CMSIS/Device/ST/STM32F4xx/Include" -I"/home/dmitryneuro/workspace_stm32/STM32F427VI/Drivers/CMSIS/Include"  -Os -g3 -Wall -fmessage-length=0 -ffunction-sections -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


