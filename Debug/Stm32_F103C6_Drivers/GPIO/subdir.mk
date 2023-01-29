################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (10.3-2021.10)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Stm32_F103C6_Drivers/GPIO/stm32f103x8_gpio_driver.c 

OBJS += \
./Stm32_F103C6_Drivers/GPIO/stm32f103x8_gpio_driver.o 

C_DEPS += \
./Stm32_F103C6_Drivers/GPIO/stm32f103x8_gpio_driver.d 


# Each subdirectory must supply rules for building sources it contributes
Stm32_F103C6_Drivers/GPIO/%.o Stm32_F103C6_Drivers/GPIO/%.su: ../Stm32_F103C6_Drivers/GPIO/%.c Stm32_F103C6_Drivers/GPIO/subdir.mk
	arm-none-eabi-gcc  -gdwarf-2 "$<" -mcpu=cortex-m3 -std=gnu11 -g3 -DDEBUG -DSTM32 -DSTM32F1 -DSTM32F103C8Tx -c -I"C:/Users/kkhalil/ArmCourse/MYRTOS_Project/ARM_Course/ARM_Course/CMSIS_V5" -I"C:/Users/kkhalil/ArmCourse/MYRTOS_Project/ARM_Course/ARM_Course/MY_RTOS/inc" -I../Inc -I"C:/Users/kkhalil/ArmCourse/MYRTOS_Project/ARM_Course/ARM_Course/HAL/includes" -I"C:/Users/kkhalil/ArmCourse/MYRTOS_Project/ARM_Course/ARM_Course/Stm32_F103C6_Drivers/inc" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfloat-abi=soft -mthumb -o "$@"

clean: clean-Stm32_F103C6_Drivers-2f-GPIO

clean-Stm32_F103C6_Drivers-2f-GPIO:
	-$(RM) ./Stm32_F103C6_Drivers/GPIO/stm32f103x8_gpio_driver.d ./Stm32_F103C6_Drivers/GPIO/stm32f103x8_gpio_driver.o ./Stm32_F103C6_Drivers/GPIO/stm32f103x8_gpio_driver.su

.PHONY: clean-Stm32_F103C6_Drivers-2f-GPIO

