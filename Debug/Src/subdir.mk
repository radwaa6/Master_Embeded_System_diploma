################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Src/main.c \
../Src/syscalls.c \
../Src/sysmem.c 

OBJS += \
./Src/main.o \
./Src/syscalls.o \
./Src/sysmem.o 

C_DEPS += \
./Src/main.d \
./Src/syscalls.d \
./Src/sysmem.d 


# Each subdirectory must supply rules for building sources it contributes
Src/main.o: ../Src/main.c
	arm-none-eabi-gcc -gdwarf-2 "$<" -mcpu=cortex-m3 -std=gnu11 -g3 -DSTM32 -DSTM32F1 -DSTM32F103C6Tx -DDEBUG -c -I"C:/Users/Compu Market/STM32CubeIDE/workspace_1.4.0/Drivers/HAL/includes" -I"C:/Users/Compu Market/STM32CubeIDE/workspace_1.4.0/Drivers/Free_RTOS/include" -I"C:/Users/Compu Market/STM32CubeIDE/workspace_1.4.0/Drivers/Free_RTOS/portable/GCC/ARM_CM3" -I"C:/Users/Compu Market/STM32CubeIDE/workspace_1.4.0/Drivers/Stm32_F103C6_Drivers/Inc" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"Src/main.d" -MT"$@" --specs=nano.specs -mfloat-abi=soft -mthumb -o "$@"
Src/syscalls.o: ../Src/syscalls.c
	arm-none-eabi-gcc -gdwarf-2 "$<" -mcpu=cortex-m3 -std=gnu11 -g3 -DSTM32 -DSTM32F1 -DSTM32F103C6Tx -DDEBUG -c -I"C:/Users/Compu Market/STM32CubeIDE/workspace_1.4.0/Drivers/HAL/includes" -I"C:/Users/Compu Market/STM32CubeIDE/workspace_1.4.0/Drivers/Free_RTOS/include" -I"C:/Users/Compu Market/STM32CubeIDE/workspace_1.4.0/Drivers/Free_RTOS/portable/GCC/ARM_CM3" -I"C:/Users/Compu Market/STM32CubeIDE/workspace_1.4.0/Drivers/Stm32_F103C6_Drivers/Inc" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"Src/syscalls.d" -MT"$@" --specs=nano.specs -mfloat-abi=soft -mthumb -o "$@"
Src/sysmem.o: ../Src/sysmem.c
	arm-none-eabi-gcc -gdwarf-2 "$<" -mcpu=cortex-m3 -std=gnu11 -g3 -DSTM32 -DSTM32F1 -DSTM32F103C6Tx -DDEBUG -c -I"C:/Users/Compu Market/STM32CubeIDE/workspace_1.4.0/Drivers/HAL/includes" -I"C:/Users/Compu Market/STM32CubeIDE/workspace_1.4.0/Drivers/Free_RTOS/include" -I"C:/Users/Compu Market/STM32CubeIDE/workspace_1.4.0/Drivers/Free_RTOS/portable/GCC/ARM_CM3" -I"C:/Users/Compu Market/STM32CubeIDE/workspace_1.4.0/Drivers/Stm32_F103C6_Drivers/Inc" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"Src/sysmem.d" -MT"$@" --specs=nano.specs -mfloat-abi=soft -mthumb -o "$@"

