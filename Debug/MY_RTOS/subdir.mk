################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (10.3-2021.10)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../MY_RTOS/CortexMX_OS_porting.c \
../MY_RTOS/MYRTOS_FIFO.c \
../MY_RTOS/Scheduler.c 

OBJS += \
./MY_RTOS/CortexMX_OS_porting.o \
./MY_RTOS/MYRTOS_FIFO.o \
./MY_RTOS/Scheduler.o 

C_DEPS += \
./MY_RTOS/CortexMX_OS_porting.d \
./MY_RTOS/MYRTOS_FIFO.d \
./MY_RTOS/Scheduler.d 


# Each subdirectory must supply rules for building sources it contributes
MY_RTOS/%.o MY_RTOS/%.su: ../MY_RTOS/%.c MY_RTOS/subdir.mk
	arm-none-eabi-gcc  -gdwarf-2 "$<" -mcpu=cortex-m3 -std=gnu11 -g3 -DDEBUG -DSTM32 -DSTM32F1 -DSTM32F103C8Tx -c -I"C:/Users/kkhalil/ArmCourse/MYRTOS_Project/ARM_Course/ARM_Course/CMSIS_V5" -I"C:/Users/kkhalil/ArmCourse/MYRTOS_Project/ARM_Course/ARM_Course/MY_RTOS/inc" -I../Inc -I"C:/Users/kkhalil/ArmCourse/MYRTOS_Project/ARM_Course/ARM_Course/HAL/includes" -I"C:/Users/kkhalil/ArmCourse/MYRTOS_Project/ARM_Course/ARM_Course/Stm32_F103C6_Drivers/inc" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfloat-abi=soft -mthumb -o "$@"

clean: clean-MY_RTOS

clean-MY_RTOS:
	-$(RM) ./MY_RTOS/CortexMX_OS_porting.d ./MY_RTOS/CortexMX_OS_porting.o ./MY_RTOS/CortexMX_OS_porting.su ./MY_RTOS/MYRTOS_FIFO.d ./MY_RTOS/MYRTOS_FIFO.o ./MY_RTOS/MYRTOS_FIFO.su ./MY_RTOS/Scheduler.d ./MY_RTOS/Scheduler.o ./MY_RTOS/Scheduler.su

.PHONY: clean-MY_RTOS

