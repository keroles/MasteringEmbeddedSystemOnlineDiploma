################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (10.3-2021.10)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
S_SRCS += \
../Startup/startup_stm32f103c8tx.s 

OBJS += \
./Startup/startup_stm32f103c8tx.o 

S_DEPS += \
./Startup/startup_stm32f103c8tx.d 


# Each subdirectory must supply rules for building sources it contributes
Startup/%.o: ../Startup/%.s Startup/subdir.mk
	arm-none-eabi-gcc  -gdwarf-2 -mcpu=cortex-m3 -g3 -DDEBUG -c -I"C:/Users/kkhalil/ArmCourse/MYRTOS_Project/ARM_Course/ARM_Course/Stm32_F103C6_Drivers/inc" -I"C:/Users/kkhalil/ArmCourse/MYRTOS_Project/ARM_Course/ARM_Course/MY_RTOS/inc" -I"C:/Users/kkhalil/ArmCourse/MYRTOS_Project/ARM_Course/ARM_Course/HAL/includes" -x assembler-with-cpp -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfloat-abi=soft -mthumb -o "$@" "$<"

clean: clean-Startup

clean-Startup:
	-$(RM) ./Startup/startup_stm32f103c8tx.d ./Startup/startup_stm32f103c8tx.o

.PHONY: clean-Startup

