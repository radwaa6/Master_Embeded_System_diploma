################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../HAL/gps.c 

OBJS += \
./HAL/gps.o 

C_DEPS += \
./HAL/gps.d 


# Each subdirectory must supply rules for building sources it contributes
HAL/gps.o: ../HAL/gps.c
	arm-none-eabi-gcc -gdwarf-2 "$<" -mcpu=cortex-m3 -std=gnu11 -g3 -DSTM32 -DSTM32F1 -DSTM32F103C6Tx -DDEBUG -c -I"C:/Users/Compu Market/STM32CubeIDE/workspace_1.4.0/Drivers/HAL/includes" -I"C:/Users/Compu Market/STM32CubeIDE/workspace_1.4.0/Drivers/Stm32_F103C6_Drivers/Inc" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"HAL/gps.d" -MT"$@" --specs=nano.specs -mfloat-abi=soft -mthumb -o "$@"

