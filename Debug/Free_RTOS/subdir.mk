################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Free_RTOS/croutine.c \
../Free_RTOS/event_groups.c \
../Free_RTOS/list.c \
../Free_RTOS/queue.c \
../Free_RTOS/stream_buffer.c \
../Free_RTOS/tasks.c \
../Free_RTOS/timers.c 

OBJS += \
./Free_RTOS/croutine.o \
./Free_RTOS/event_groups.o \
./Free_RTOS/list.o \
./Free_RTOS/queue.o \
./Free_RTOS/stream_buffer.o \
./Free_RTOS/tasks.o \
./Free_RTOS/timers.o 

C_DEPS += \
./Free_RTOS/croutine.d \
./Free_RTOS/event_groups.d \
./Free_RTOS/list.d \
./Free_RTOS/queue.d \
./Free_RTOS/stream_buffer.d \
./Free_RTOS/tasks.d \
./Free_RTOS/timers.d 


# Each subdirectory must supply rules for building sources it contributes
Free_RTOS/croutine.o: ../Free_RTOS/croutine.c
	arm-none-eabi-gcc -gdwarf-2 "$<" -mcpu=cortex-m3 -std=gnu11 -g3 -DSTM32 -DSTM32F1 -DSTM32F103C6Tx -DDEBUG -c -I"C:/Users/Compu Market/STM32CubeIDE/workspace_1.4.0/Drivers/HAL/includes" -I"C:/Users/Compu Market/STM32CubeIDE/workspace_1.4.0/Drivers/Free_RTOS/include" -I"C:/Users/Compu Market/STM32CubeIDE/workspace_1.4.0/Drivers/Free_RTOS/portable/GCC/ARM_CM3" -I"C:/Users/Compu Market/STM32CubeIDE/workspace_1.4.0/Drivers/Stm32_F103C6_Drivers/Inc" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"Free_RTOS/croutine.d" -MT"$@" --specs=nano.specs -mfloat-abi=soft -mthumb -o "$@"
Free_RTOS/event_groups.o: ../Free_RTOS/event_groups.c
	arm-none-eabi-gcc -gdwarf-2 "$<" -mcpu=cortex-m3 -std=gnu11 -g3 -DSTM32 -DSTM32F1 -DSTM32F103C6Tx -DDEBUG -c -I"C:/Users/Compu Market/STM32CubeIDE/workspace_1.4.0/Drivers/HAL/includes" -I"C:/Users/Compu Market/STM32CubeIDE/workspace_1.4.0/Drivers/Free_RTOS/include" -I"C:/Users/Compu Market/STM32CubeIDE/workspace_1.4.0/Drivers/Free_RTOS/portable/GCC/ARM_CM3" -I"C:/Users/Compu Market/STM32CubeIDE/workspace_1.4.0/Drivers/Stm32_F103C6_Drivers/Inc" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"Free_RTOS/event_groups.d" -MT"$@" --specs=nano.specs -mfloat-abi=soft -mthumb -o "$@"
Free_RTOS/list.o: ../Free_RTOS/list.c
	arm-none-eabi-gcc -gdwarf-2 "$<" -mcpu=cortex-m3 -std=gnu11 -g3 -DSTM32 -DSTM32F1 -DSTM32F103C6Tx -DDEBUG -c -I"C:/Users/Compu Market/STM32CubeIDE/workspace_1.4.0/Drivers/HAL/includes" -I"C:/Users/Compu Market/STM32CubeIDE/workspace_1.4.0/Drivers/Free_RTOS/include" -I"C:/Users/Compu Market/STM32CubeIDE/workspace_1.4.0/Drivers/Free_RTOS/portable/GCC/ARM_CM3" -I"C:/Users/Compu Market/STM32CubeIDE/workspace_1.4.0/Drivers/Stm32_F103C6_Drivers/Inc" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"Free_RTOS/list.d" -MT"$@" --specs=nano.specs -mfloat-abi=soft -mthumb -o "$@"
Free_RTOS/queue.o: ../Free_RTOS/queue.c
	arm-none-eabi-gcc -gdwarf-2 "$<" -mcpu=cortex-m3 -std=gnu11 -g3 -DSTM32 -DSTM32F1 -DSTM32F103C6Tx -DDEBUG -c -I"C:/Users/Compu Market/STM32CubeIDE/workspace_1.4.0/Drivers/HAL/includes" -I"C:/Users/Compu Market/STM32CubeIDE/workspace_1.4.0/Drivers/Free_RTOS/include" -I"C:/Users/Compu Market/STM32CubeIDE/workspace_1.4.0/Drivers/Free_RTOS/portable/GCC/ARM_CM3" -I"C:/Users/Compu Market/STM32CubeIDE/workspace_1.4.0/Drivers/Stm32_F103C6_Drivers/Inc" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"Free_RTOS/queue.d" -MT"$@" --specs=nano.specs -mfloat-abi=soft -mthumb -o "$@"
Free_RTOS/stream_buffer.o: ../Free_RTOS/stream_buffer.c
	arm-none-eabi-gcc -gdwarf-2 "$<" -mcpu=cortex-m3 -std=gnu11 -g3 -DSTM32 -DSTM32F1 -DSTM32F103C6Tx -DDEBUG -c -I"C:/Users/Compu Market/STM32CubeIDE/workspace_1.4.0/Drivers/HAL/includes" -I"C:/Users/Compu Market/STM32CubeIDE/workspace_1.4.0/Drivers/Free_RTOS/include" -I"C:/Users/Compu Market/STM32CubeIDE/workspace_1.4.0/Drivers/Free_RTOS/portable/GCC/ARM_CM3" -I"C:/Users/Compu Market/STM32CubeIDE/workspace_1.4.0/Drivers/Stm32_F103C6_Drivers/Inc" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"Free_RTOS/stream_buffer.d" -MT"$@" --specs=nano.specs -mfloat-abi=soft -mthumb -o "$@"
Free_RTOS/tasks.o: ../Free_RTOS/tasks.c
	arm-none-eabi-gcc -gdwarf-2 "$<" -mcpu=cortex-m3 -std=gnu11 -g3 -DSTM32 -DSTM32F1 -DSTM32F103C6Tx -DDEBUG -c -I"C:/Users/Compu Market/STM32CubeIDE/workspace_1.4.0/Drivers/HAL/includes" -I"C:/Users/Compu Market/STM32CubeIDE/workspace_1.4.0/Drivers/Free_RTOS/include" -I"C:/Users/Compu Market/STM32CubeIDE/workspace_1.4.0/Drivers/Free_RTOS/portable/GCC/ARM_CM3" -I"C:/Users/Compu Market/STM32CubeIDE/workspace_1.4.0/Drivers/Stm32_F103C6_Drivers/Inc" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"Free_RTOS/tasks.d" -MT"$@" --specs=nano.specs -mfloat-abi=soft -mthumb -o "$@"
Free_RTOS/timers.o: ../Free_RTOS/timers.c
	arm-none-eabi-gcc -gdwarf-2 "$<" -mcpu=cortex-m3 -std=gnu11 -g3 -DSTM32 -DSTM32F1 -DSTM32F103C6Tx -DDEBUG -c -I"C:/Users/Compu Market/STM32CubeIDE/workspace_1.4.0/Drivers/HAL/includes" -I"C:/Users/Compu Market/STM32CubeIDE/workspace_1.4.0/Drivers/Free_RTOS/include" -I"C:/Users/Compu Market/STM32CubeIDE/workspace_1.4.0/Drivers/Free_RTOS/portable/GCC/ARM_CM3" -I"C:/Users/Compu Market/STM32CubeIDE/workspace_1.4.0/Drivers/Stm32_F103C6_Drivers/Inc" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"Free_RTOS/timers.d" -MT"$@" --specs=nano.specs -mfloat-abi=soft -mthumb -o "$@"

