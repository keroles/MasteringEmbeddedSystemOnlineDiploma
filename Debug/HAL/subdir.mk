################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (10.3-2021.10)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../HAL/I2C_Slave_EEPROM.c \
../HAL/keypad.c \
../HAL/lcd.c 

OBJS += \
./HAL/I2C_Slave_EEPROM.o \
./HAL/keypad.o \
./HAL/lcd.o 

C_DEPS += \
./HAL/I2C_Slave_EEPROM.d \
./HAL/keypad.d \
./HAL/lcd.d 


# Each subdirectory must supply rules for building sources it contributes
HAL/%.o HAL/%.su: ../HAL/%.c HAL/subdir.mk
	arm-none-eabi-gcc  -gdwarf-2 "$<" -mcpu=cortex-m3 -std=gnu11 -g3 -DDEBUG -DSTM32 -DSTM32F1 -DSTM32F103C8Tx -c -I"C:/Users/kkhalil/ArmCourse/MYRTOS_Project/ARM_Course/ARM_Course/CMSIS_V5" -I"C:/Users/kkhalil/ArmCourse/MYRTOS_Project/ARM_Course/ARM_Course/MY_RTOS/inc" -I../Inc -I"C:/Users/kkhalil/ArmCourse/MYRTOS_Project/ARM_Course/ARM_Course/HAL/includes" -I"C:/Users/kkhalil/ArmCourse/MYRTOS_Project/ARM_Course/ARM_Course/Stm32_F103C6_Drivers/inc" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfloat-abi=soft -mthumb -o "$@"

clean: clean-HAL

clean-HAL:
	-$(RM) ./HAL/I2C_Slave_EEPROM.d ./HAL/I2C_Slave_EEPROM.o ./HAL/I2C_Slave_EEPROM.su ./HAL/keypad.d ./HAL/keypad.o ./HAL/keypad.su ./HAL/lcd.d ./HAL/lcd.o ./HAL/lcd.su

.PHONY: clean-HAL

