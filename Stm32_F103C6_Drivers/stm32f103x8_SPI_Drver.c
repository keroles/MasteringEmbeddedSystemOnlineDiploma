
/*
 * stm32f103x8_USART_driver.h
 *
 *  Created on: Apr 28, 2021
 *      Author: Keroles Shenouda
 *      Mastering Embedded System Online Diploma
 *      www.learn-in-depth.com
 */

#include "stm32f103x8_SPI_driver.h"



/*
 * =======================================================================================
 * 							Generic Variables
 * =======================================================================================
 */
SPI_Config* Global_SPI_Config[2]  = {NULL,NULL} ;
SPI_Config Global_SPI_Config1 ;
SPI_Config Global_SPI_Config2 ;

/*
 * =======================================================================================
 * 							Generic Macros
 * =======================================================================================
 */

#define 		SPI1_INDEX 				0
#define 		SPI2_INDEX 				1

/*
 * =======================================================================================
 * 							APIs
 * =======================================================================================
 */

/**================================================================
 * @Fn				-MCAL_SPI_Init
 * @brief 			- Initialize the SPI according to the specified parameters
 * @param [in] 		- SPIx: where x can be (1..3 depending on device used)
 * @param [in] 		- SPI_Config: All SPI Configuration EXTI_PinConfig_t
 * @retval 			-none
 * Note				-Support for SPI Full Duplex Master/Slave only  & NSS HW only for slave
 * 					- in case of master you have to configure pin and drive it
 */
void MCAL_SPI_Init (SPI_TypeDef *SPIx, SPI_Config* SPI_Config)
{
	  uint16_t tmpreg_CR1 = 0;
	  uint16_t tmpreg_CR2 = 0;

	if (SPIx == SPI1)
	{
		Global_SPI_Config1 = *SPI_Config ;
		Global_SPI_Config[SPI1_INDEX] =  &Global_SPI_Config1 ;
		RCC_SPI1_CLK_EN();

	}else if (SPIx == SPI2)
	{
		Global_SPI_Config2 = *SPI_Config ;
		Global_SPI_Config[SPI2_INDEX] =  &Global_SPI_Config2 ;
		RCC_SPI2_CLK_EN();

	}


	//Enabe SPI  CR1:Bit 6 SPE: SPI enable
	tmpreg_CR1 = (0x1U<<6) ;

	//Master or Slave
	tmpreg_CR1 |=  SPI_Config->Device_Mode ;

	//SPI_Communication_Mode
	tmpreg_CR1 |=  SPI_Config->Communication_Mode ;

	//SPI_Frame_Format
	tmpreg_CR1 |=  SPI_Config->Frame_Format ;

	//SPI_DataSize
	tmpreg_CR1 |=  SPI_Config->DataSize ;

	//SPI_Clock_Polarity
	tmpreg_CR1 |=  SPI_Config->CLKPolarity ;

	//SPI_Clock_Phase
	tmpreg_CR1 |=  SPI_Config->CLKPhase ;

	//======================NSS=================================

	if (SPI_Config->NSS == SPI_NSS_Hard_Master_SS_output_enable )
	{
		tmpreg_CR2 |=  SPI_Config->NSS ;

	}else	if (SPI_Config->NSS == SPI_NSS_Hard_Master_SS_output_disable )
	{
		tmpreg_CR2 &=  SPI_Config->NSS ;

	}else
	{
		tmpreg_CR1 |=  SPI_Config->NSS ;

	}

	//=======================================================


	//SPI_BAUDRATEPRESCALER
	tmpreg_CR1 |=  SPI_Config->SPI_BAUDRATEPRESCALER ;


	if (SPI_Config->IRQ_Enable  != SPI_IRQ_Enable_NONE)
	{
		// SPI_IRQ_Enable_define
		tmpreg_CR2 |= SPI_Config->IRQ_Enable ;


		if (SPIx == SPI1)
		{
			NVIC_IRQ35_SPI1_Enable ;

		}else if (SPIx == SPI2)
		{
			NVIC_IRQ36_SPI2_Enable ;
		}

	}



	SPIx->SPI_CR1 = tmpreg_CR1 ;
	SPIx->SPI_CR2 = tmpreg_CR2 ;
	  /* Activate the SPI mode (Reset I2SMOD bit in I2SCFGR register) */
	SPIx->SPI_I2SCFGR &= ~(1<<11);

	SPIx->SPI_CRCPR = 0x0 ;
}

void MCAL_SPI_DeInit (SPI_TypeDef *SPIx)
{
	if (SPIx == SPI1)
	{
		NVIC_IRQ35_SPI1_Disable ;
		RCC_SPI1_Reset();

	}else if (SPIx == SPI2)
	{
		NVIC_IRQ36_SPI2_Disable ;
		RCC_SPI2_Reset();
	}



}
#define  SPI_SR_TXE                          ((uint8_t)0x02)               /*!< Transmit buffer Empty */
#define  SPI_SR_RXNE                         ((uint8_t)0x01)               /*!< Receive buffer Not Empty */


void  MCAL_SPI_TX_RX (SPI_TypeDef *SPIx, uint16_t *pTxBuffer,enum PollingMechism PollingEn )
{
	while(!((SPIx)->SPI_SR & SPI_SR_TXE));
	SPIx->SPI_DR = *pTxBuffer;
	while(!((SPIx)->SPI_SR & SPI_SR_RXNE));
	*pTxBuffer = SPIx->SPI_DR;


}

void MCAL_SPI_SendData	(SPI_TypeDef *SPIx, uint16_t *pTxBuffer,enum PollingMechism PollingEn )
{
	uint8_t index = 0 ;
	if (SPIx == SPI1)
	{
		index =  SPI1_INDEX ;

	}else if (SPIx == SPI2)
	{
		index =  SPI2_INDEX ;
	}

	if (Global_SPI_Config[index]->Communication_Mode ==  SPI_DIRECTION_2LINES || Global_SPI_Config[index]->Communication_Mode == SPI_DIRECTION_1LINE_transmit_only) {
		if (PollingEn == Pollingenable) //Bit 1 TXE: Transmit buffer empty
			while(!((SPIx)->SPI_SR & SPI_SR_TXE));

		SPIx->SPI_DR =  (*pTxBuffer ) ;


	}
	else
	{
		//todo
	}

}

void MCAL_SPI_ReceiveData	(SPI_TypeDef *SPIx, uint16_t *pTxBuffer ,enum PollingMechism PollingEn )
{
	uint8_t index = 0 ;
	if (SPIx == SPI1)
	{
		index =  SPI1_INDEX ;

	}else if (SPIx == SPI2)
	{
		index =  SPI2_INDEX ;
	}

	if ( (Global_SPI_Config[index]->Communication_Mode ==  SPI_DIRECTION_2LINES)  || (Global_SPI_Config[index]->Communication_Mode  ==  SPI_DIRECTION_2LINES_RXONLY) )
	{

		if (PollingEn == Pollingenable) //Bit 0 RXNE: Receive buffer not empty
			while(!((SPIx)->SPI_SR & SPI_SR_RXNE));


		*pTxBuffer = 	SPIx->SPI_DR  ;
	}
	else
	{
		//todo
	}
}



/*
 * =======================================================================================
 * 							Generic Functions
 * =======================================================================================
 */
//ISR
void SPI1_IRQHandler (void)
{
	struct S_IRQ_SRC irq_src ;
	irq_src.TXE = ( ( SPI1->SPI_SR &  (1<<1)) >> 1 );
	irq_src.RXNE = ( ( SPI1->SPI_SR &  (1<<0)) >> 0 );
	irq_src.ERRI = ( ( SPI1->SPI_SR &  (1<<4)) >> 4 );


	Global_SPI_Config[SPI1_INDEX]->P_IRQ_CallBack (irq_src) ;

}
void SPI2_IRQHandler (void)
{
	struct S_IRQ_SRC irq_src ;
	irq_src.TXE = ( ( SPI2->SPI_SR &  (1<<1)) >> 1 );
	irq_src.RXNE = ( ( SPI2->SPI_SR &  (1<<0)) >> 0 );
	irq_src.ERRI = ( ( SPI2->SPI_SR &  (1<<4)) >> 4 );
	Global_SPI_Config[SPI2_INDEX]->P_IRQ_CallBack (irq_src) ;
}




void MCAL_SPI_GPIO_Set_Pins (SPI_TypeDef *SPIx)
{
	GPIO_PinConfig_t PinCfg ;

	if (SPIx == SPI1)
	{
		//		PA4 : SPI1_NSS
		//		PA5 : SPI1_SCK
		//		PA6 : SPI1_MISO
		//		PA7 : SPI1_MOSI

		if (Global_SPI_Config[SPI1_INDEX]->Device_Mode == SPI_Device_Mode_MASTER )
		{


			//PA4 : SPI1_NSS

			switch  (Global_SPI_Config[SPI1_INDEX]->NSS)
			{

			case SPI_NSS_Hard_Master_SS_output_disable:
				//Hardware master /slave Input floating
				PinCfg.GPIO_PinNumber = GPIO_PIN_4;
				PinCfg.GPIO_MODE = GPIO_MODE_INPUT_FLO;
				MCAL_GPIO_Init(GPIOA, &PinCfg);
				break ;


			case SPI_NSS_Hard_Master_SS_output_enable:
				//Hardware master/ NSS output enabled Alternate function push-pull
				PinCfg.GPIO_PinNumber = GPIO_PIN_4;
				PinCfg.GPIO_MODE = GPIO_MODE_OUTPUT_AF_PP;
				PinCfg.GPIO_Output_Speed = GPIO_SPEED_10M;
				MCAL_GPIO_Init(GPIOA, &PinCfg);
				break ;
			}


			//		PA5 : SPI1_SCK
			//			Master Alternate function push-pull
			PinCfg.GPIO_PinNumber = GPIO_PIN_5;
			PinCfg.GPIO_MODE = GPIO_MODE_OUTPUT_AF_PP;
			PinCfg.GPIO_Output_Speed = GPIO_SPEED_10M;
			MCAL_GPIO_Init(GPIOA, &PinCfg);


			//		PA6 : SPI1_MISO  (supported only full duplex)
			//			Full duplex / master Input floating

			PinCfg.GPIO_PinNumber = GPIO_PIN_6;
			PinCfg.GPIO_MODE = GPIO_MODE_INPUT_FLO;
			MCAL_GPIO_Init(GPIOA, &PinCfg);

			//todo to suport half duplex and simplex


			//		PA7 : SPI1_MOSI
			//			Full duplex / master Alternate function push-pull
			PinCfg.GPIO_PinNumber = GPIO_PIN_7;
			PinCfg.GPIO_MODE = GPIO_MODE_OUTPUT_AF_PP;
			PinCfg.GPIO_Output_Speed = GPIO_SPEED_10M;
			MCAL_GPIO_Init(GPIOA, &PinCfg);



		}else  //Slave
		{

			//PA4 : SPI1_NSS

			if   (Global_SPI_Config[SPI1_INDEX]->NSS == SPI_NSS_Hard_Slave)
			{

				//Hardware master /slave Input floating
				PinCfg.GPIO_PinNumber = GPIO_PIN_4;
				PinCfg.GPIO_MODE = GPIO_MODE_INPUT_FLO;
				MCAL_GPIO_Init(GPIOA, &PinCfg);

			}

			//		PA5 : SPI1_SCK
			//			Slave Input floating
			PinCfg.GPIO_PinNumber = GPIO_PIN_5;
			PinCfg.GPIO_MODE = GPIO_MODE_INPUT_FLO;
			MCAL_GPIO_Init(GPIOA, &PinCfg);


			//		PA6 : SPI1_MISO  (supported only full duplex)
			//			Full duplex / slave (point to point) Alternate function push-pull
			//todo			Full duplex / slave (multi-slave) Alternate function open drain
			PinCfg.GPIO_PinNumber = GPIO_PIN_6;
			PinCfg.GPIO_MODE = GPIO_MODE_OUTPUT_AF_PP;
			PinCfg.GPIO_Output_Speed = GPIO_SPEED_10M;
			MCAL_GPIO_Init(GPIOA, &PinCfg);

			//		PA7 : SPI1_MOSI
			//			Full duplex / slave Input floating
			PinCfg.GPIO_PinNumber = GPIO_PIN_7;
			PinCfg.GPIO_MODE = GPIO_MODE_INPUT_FLO;
			MCAL_GPIO_Init(GPIOA, &PinCfg);

		}


		//============================================================SPI2
	}else if (SPIx == SPI2)
	{

		//		PB12 : SPI2_NSS
		//		PB13 : SPI2_SCK
		//		PB14 : SPI2_MISO
		//		PB15 : SPI2_MOSI

		if (Global_SPI_Config[SPI2_INDEX]->Device_Mode == SPI_Device_Mode_MASTER )
		{


			//		PB12 : SPI2_NSS

			switch  (Global_SPI_Config[SPI2_INDEX]->NSS)
			{

			case SPI_NSS_Hard_Master_SS_output_disable:
				//Hardware master /slave Input floating
				PinCfg.GPIO_PinNumber = GPIO_PIN_12;
				PinCfg.GPIO_MODE = GPIO_MODE_INPUT_FLO;
				MCAL_GPIO_Init(GPIOB, &PinCfg);
				break ;


			case SPI_NSS_Hard_Master_SS_output_enable:
				//Hardware master/ NSS output enabled Alternate function push-pull
				PinCfg.GPIO_PinNumber = GPIO_PIN_12;
				PinCfg.GPIO_MODE = GPIO_MODE_OUTPUT_AF_PP;
				PinCfg.GPIO_Output_Speed = GPIO_SPEED_10M;
				MCAL_GPIO_Init(GPIOB, &PinCfg);
				break ;
			}


			//		PB13 : SPI2_SCK
			//			Master Alternate function push-pull
			PinCfg.GPIO_PinNumber = GPIO_PIN_13;
			PinCfg.GPIO_MODE = GPIO_MODE_OUTPUT_AF_PP;
			PinCfg.GPIO_Output_Speed = GPIO_SPEED_10M;
			MCAL_GPIO_Init(GPIOB, &PinCfg);


			//		PB14 : SPI1_MISO  (supported only full duplex)
			//			Full duplex / master Input floating

			PinCfg.GPIO_PinNumber = GPIO_PIN_14;
			PinCfg.GPIO_MODE = GPIO_MODE_INPUT_FLO;
			MCAL_GPIO_Init(GPIOB, &PinCfg);

			//todo to suport half duplex and simplex


			//		PB15 : SPI1_MOSI
			//			Full duplex / master Alternate function push-pull
			PinCfg.GPIO_PinNumber = GPIO_PIN_15;
			PinCfg.GPIO_MODE = GPIO_MODE_OUTPUT_AF_PP;
			PinCfg.GPIO_Output_Speed = GPIO_SPEED_10M;
			MCAL_GPIO_Init(GPIOB, &PinCfg);



		}else  //Slave
		{

			//PB12 : SPI1_NSS

			switch  (Global_SPI_Config[SPI2_INDEX]->NSS)
			{

			case SPI_NSS_Hard_Slave:
				//slave Input floating
				PinCfg.GPIO_PinNumber = GPIO_PIN_12;
				PinCfg.GPIO_MODE = GPIO_MODE_INPUT_FLO;
				MCAL_GPIO_Init(GPIOB, &PinCfg);
				break ;

			}

			//		B13 : SPI1_SCK
			//			Slave Input floating
			PinCfg.GPIO_PinNumber = GPIO_PIN_13;
			PinCfg.GPIO_MODE = GPIO_MODE_INPUT_FLO;
			MCAL_GPIO_Init(GPIOB, &PinCfg);


			//		PB14 : SPI1_MISO  (supported only full duplex)
			//			Full duplex / slave (point to point) Alternate function push-pull
			//todo			Full duplex / slave (multi-slave) Alternate function open drain
			PinCfg.GPIO_PinNumber = GPIO_PIN_14;
			PinCfg.GPIO_MODE = GPIO_MODE_OUTPUT_AF_PP;
			PinCfg.GPIO_Output_Speed = GPIO_SPEED_10M;
			MCAL_GPIO_Init(GPIOB, &PinCfg);

			//		PB15 : SPI1_MOSI
			//			Full duplex / slave Input floating
			PinCfg.GPIO_PinNumber = GPIO_PIN_15;
			PinCfg.GPIO_MODE = GPIO_MODE_INPUT_FLO;
			MCAL_GPIO_Init(GPIOB, &PinCfg);

		}


	}

}



