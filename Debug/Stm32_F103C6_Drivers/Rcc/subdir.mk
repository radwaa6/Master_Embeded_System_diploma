################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Stm32_F103C6_Drivers/Rcc/RCC.c 

OBJS += \
./Stm32_F103C6_Drivers/Rcc/RCC.o 

C_DEPS += \
./Stm32_F103C6_Drivers/Rcc/RCC.d 


# Each subdirectory must supply rules for building sources it contributes
Stm32_F103C6_Drivers/Rcc/RCC.o: ../Stm32_F103C6_Drivers/Rcc/RCC.c
	arm-none-eabi-gcc -gdwarf-2 "$<" -mcpu=cortex-m3 -std=gnu11 -g3 -DSTM32 -DSTM32F1 -DSTM32F103C6Tx -DDEBUG -c -I"C:/Users/Compu Market/STM32CubeIDE/workspace_1.4.0/Drivers/HAL/includes" -I"C:/Users/Compu Market/STM32CubeIDE/workspace_1.4.0/Drivers/Free_RTOS/include" -I"C:/Users/Compu Market/STM32CubeIDE/workspace_1.4.0/Drivers/Free_RTOS/portable/GCC/ARM_CM3" -I"C:/Users/Compu Market/STM32CubeIDE/workspace_1.4.0/Drivers/Stm32_F103C6_Drivers/Inc" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"Stm32_F103C6_Drivers/Rcc/RCC.d" -MT"$@" --specs=nano.specs -mfloat-abi=soft -mthumb -o "$@"

