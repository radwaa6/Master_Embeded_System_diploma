################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Free_RTOS/portable/MemMang/heap_4.c 

OBJS += \
./Free_RTOS/portable/MemMang/heap_4.o 

C_DEPS += \
./Free_RTOS/portable/MemMang/heap_4.d 


# Each subdirectory must supply rules for building sources it contributes
Free_RTOS/portable/MemMang/heap_4.o: ../Free_RTOS/portable/MemMang/heap_4.c
	arm-none-eabi-gcc -gdwarf-2 "$<" -mcpu=cortex-m3 -std=gnu11 -g3 -DSTM32 -DSTM32F1 -DSTM32F103C6Tx -DDEBUG -c -I"C:/Users/Compu Market/STM32CubeIDE/workspace_1.4.0/Drivers/HAL/includes" -I"C:/Users/Compu Market/STM32CubeIDE/workspace_1.4.0/Drivers/Free_RTOS/include" -I"C:/Users/Compu Market/STM32CubeIDE/workspace_1.4.0/Drivers/Free_RTOS/portable/GCC/ARM_CM3" -I"C:/Users/Compu Market/STM32CubeIDE/workspace_1.4.0/Drivers/Stm32_F103C6_Drivers/Inc" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"Free_RTOS/portable/MemMang/heap_4.d" -MT"$@" --specs=nano.specs -mfloat-abi=soft -mthumb -o "$@"

