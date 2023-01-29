/**
 ******************************************************************************
 * @file           :  MYRTOS OS
 * @author         : Keroles Shenouda
 * @brief          : Create Your RTOS (ARM And RTOS Coure) in Master Embedded System Online Diploma
 * www.learn-in-depth.com
 * eng.keroles.karam@gmail.com
 * Mater Embedded System Online Diploma
 ******************************************************************************
 */

#include <stdint.h>

#include "core_cm3.h"
#if !defined(__SOFT_FP__) && defined(__ARM_FP)
#warning "FPU is not initialized, but the project is compiling for an FPU. Please initialize the FPU before use."
#endif


#include <stdint.h>
#include <stdlib.h>
#include <stdio.h>

#include "STM32F103x8.h"
#include "stm32f103x8_gpio_driver.h"
#include "lcd.h"
#include "keypad.h"
#include "stm32f103x8_EXTI_driver.h"
#include "stm32f103x8_USART_driver.h"
#include "stm32f103x8_SPI_driver.h"
#include "stm32f103x8_I2C_driver.h"
#include "I2C_Slave_EEPROM.h"

#include "Scheduler.h"

Task_ref Task1, Task2, Task3, Task4 ;
unsigned char Task1LED,Task2LED,Task3LED,Task4LED ;

void task1()
{
	static int Count = 0 ;
	while (1){
		//Task 1 Code
		Task1LED ^= 1;
		Count++ ;
		if (Count == 30 )
		{
			MYRTOS_ActivateTask(&Task4);
			Count = 0 ;
		} //100 ms
	}
}
void task2()
{
	while (1){
		//Task 2 Code
		Task2LED ^= 1;
		//300 ms
		MYRTOS_TaskWait(300, &Task2);
	}
}
void task3()
{
	while (1){
		//Task 3 Code
		Task3LED ^= 1;
		//500 ms
		MYRTOS_TaskWait(500, &Task3);
	}
}

void task4()
{
	static int Count = 0 ;

	while (1){
		//Task 3 Code
		Task4LED ^= 1;
		Count++ ;
		MYRTOS_TaskWait(1000, &Task4);


	}
}
int main(void)
{

	MYRTOS_errorID error;
	//HW_Init (Initialize ClockTree, RestController)
	HW_init();

	if (MYRTOS_init() != NoError)
		while (1);

	Task1.Stack_Size = 1024 ;
	Task1.p_TaskEntry =task1;
	Task1.priority= 3 ;
	strcpy (Task1.TaskName, "task_1");

	Task2.Stack_Size = 1024 ;
	Task2.p_TaskEntry =task2;
	Task2.priority= 3 ;
	strcpy (Task2.TaskName, "task_2");

	Task3.Stack_Size = 1024 ;
	Task3.p_TaskEntry =task3;
	Task3.priority= 3 ;
	strcpy (Task3.TaskName, "task_3");

	Task4.Stack_Size = 1024 ;
	Task4.p_TaskEntry =task4;
	Task4.priority= 1 ;
	strcpy (Task4.TaskName, "task_4");

	error += MYRTOS_CreateTask(&Task1);
	error += MYRTOS_CreateTask(&Task2);
	error += MYRTOS_CreateTask(&Task3);
	error += MYRTOS_CreateTask(&Task4);


	MYRTOS_ActivateTask(&Task1);
	MYRTOS_ActivateTask(&Task2);
	MYRTOS_ActivateTask(&Task3);

	MYRTOS_STARTOS() ;

	while (1)
	{

	}


}
