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

#include "CortexMX_OS_porting.h"

unsigned char SysTickLED ;
void HardFault_Handler (void)
{
	while(1) ;
}
void	MemManage_Handler (void)
{
	while(1) ;
}
void	BusFault_Handler(void)
{
	while(1) ;
}
void	UsageFault_Handler(void)
{
	while(1) ;
}


__attribute ((naked)) void SVC_Handler ()
{
	//	SWITCH_CPU_AccessLevel (privileged);
	__asm ("tst lr, #4 \n\t"
			"ITE EQ \n\t" //To execute Thumb instructions conditionally, you can either use an IT instruction, or a conditional branch instruction.
			"mrseq r0,MSP \n\t "
			"mrsne r0,PSP \n\t"
			"B OS_SVC");
}



void HW_init()
{
	//Initialize Clock Tree (RCC -> SysTick Timer & CPU) 8MHZ
	//init HW
	//Clock tree
	//RCC Default Values makes CPU Clock & SySTick Timer clock = 8 M HZ

	//	8 MHZ
	//	1 count -> 0.125 us
	//	X count -> 1 ms
	//	X = 8000 Count



	//	decrease PenSV  interrupt priority to be  smaller than or equal  SySTICK Timer
	//SysTICK have a priority 14
	__NVIC_SetPriority(PendSV_IRQn, 15) ;

}



void trigger_OS_PendSV()
{
	SCB->ICSR |= SCB_ICSR_PENDSVSET_Msk ;

}

void Start_Ticker()
{
	//	This clock tree should be defined in HW_init()
	//	8 MHZ
	//	1 count -> 0.125 us
	//	X count -> 1 ms
	//	X = 8000 Count

	 SysTick_Config(8000);


}

void SysTick_Handler(void)
{
	SysTickLED ^= 1 ;
	MYRTOS_Update_TasksWaitingTime();
	//Determine Pcurrent & Pnext
	Decide_whatNext();
	//Switch Context & restore
	trigger_OS_PendSV();

}



