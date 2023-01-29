/*
 * stm32f103x8_SPI_driver.h
 *
 *  Created on: Apr 28, 2021
 *      Author: Keroles Shenouda
 *      Mastering Embedded System Online Diploma
 *      www.learn-in-depth.com
 */

#ifndef STM32F103X8_SPI_DRIVER_H_
#define STM32F103X8_SPI_DRIVER_H_

//includes
#include "STM32F103x8.h"
#include "stm32f103x8_gpio_driver.h"
#include "stm32f103x8_RCC_driver.h"



struct S_IRQ_SRC
{
	uint8_t TXE:1 ;  //Tx buffer empty interrupt
	uint8_t RXNE:1 ; //RX buffer not empty interrupt
	uint8_t ERRI:1 ; //Error interrupt
	uint8_t Reserved:5 ;
};

//Configuration structure
typedef struct
{

	uint16_t        			  	Device_Mode;     		  //  Specifies the SPI operating mode  @ref SPI_Device_Mode

	uint16_t  			      	Communication_Mode ;      // Specifies the SPI bidirectional mode state  @ref SPI_Communication_Mode

	uint16_t 				  	Frame_Format;			  // Specifies LSB or MSB   @ref SPI_Frame_Format

	uint16_t 				  	DataSize ;				  //  @ref SPI_DataSize

	uint16_t 				  	CLKPolarity ;			  // @ref SPI_CLKPolarity

	uint16_t 				  	CLKPhase ;				  //@ref SPI_CLKPhase

	uint16_t					 	NSS;				      //Specifies whether the NSS signal is managed by
	//hardware (NSS pin) or by software using the SSI bitenable
	//@ref SPI_NSS

	uint16_t 					SPI_BAUDRATEPRESCALER;  	/*Specifies the Baud Rate prescaler value which will be
															used to configure the transmit and receive SCK clock.
															This parameter can be a value of @ref SPI_BAUDRATEPRESCALER
															@note The communication clock is derived from the master
															clock. The slave clock does not need to be set.*/
															// Take Care you have to Conigure RCC to enter the correct clock to APB2 >>> to SPI

	uint16_t					 	IRQ_Enable;			//@ref SPI_IRQ_Enable

	void(* P_IRQ_CallBack)(struct S_IRQ_SRC irq_src) ;					//Set the C Function() which will be called once the IRQ  Happen

}SPI_Config;



// * =======================================================================================
//Reference Macros
// * =======================================================================================

// * =======================================================================================


//@ref SPI_Device_Mode
#define SPI_Device_Mode_SLAVE                  (0x00000000U)
#define SPI_Device_Mode_MASTER                 (0x1U<<2) //MSTR :1: Master configuration

//@ref SPI_Communication_Mode
#define SPI_DIRECTION_2LINES           					(0x00000000U)
#define SPI_DIRECTION_2LINES_RXONLY     				(0x1U<<10) //Bit 10 RXONLY: Receive only
#define SPI_DIRECTION_1LINE_receive_only          		((0x1U<<15) ) //Bit 15 BIDIMODE: Bidirectional data mode enable
#define SPI_DIRECTION_1LINE_transmit_only             	((0x1U<<15) | (0x1U<<14)) //Bit 15 BIDIMODE: Bidirectional data mode enable &  Bit 14 BIDIOE: Output enable in bidirectional mode


//@ref SPI_Frame_Format
#define SPI_Frame_Format_MSB_transmitted_first                  (0x00000000U)  //Bit 7 LSBFIRST: Frame format
#define SPI_Frame_Format_LSB_transmitted_first                	(0x1U<<7) 		//Bit 7 LSBFIRST: Frame format


//@ref SPI_DataSize
#define SPI_DataSize_8BIT               (0x00000000U)
#define SPI_DataSize_16BIT              (0x1U<<11)    //Bit 11 DFF: Data frame format



/** @defgroup SPI_Clock_Polarity SPI Clock Polarity
 * @{
 */
#define SPI_CLKPolarity_LOW_when_idle                (0x00000000U)
#define SPI_CLKPolarity_HIGH_when_idle               (0x1U<<1) //Bit1 CPOL: Clock polarity
/**
 * @}
 */
/** @defgroup SPI_Clock_Phase SPI Clock Phase
 * @{
 */
#define SPI_Clock_Phase_1EDGE_first_data_capture_edge                 (0x00000000U)
#define SPI_Clock_Phase_2EDGE_first_data_capture_edge                 (0x1U<<0) //Bit 0 CPHA: Clock phase

//@ref SPI_NSS  SPI Slave Select Management
//======================NSS=================================
///Hardware or Software
#define SPI_NSS_Hard_Slave                    					((uint16_t)0x0000)
#define SPI_NSS_Hard_Master_SS_output_enable                    (0x1U<<2)           //SPI_CR2  Bit 2 SSOE: SS output enable
#define SPI_NSS_Hard_Master_SS_output_disable                     ~(0x1U<<2)           //SPI_CR2  Bit 2 SSOE: SS output enable &=


#define SPI_NSS_Soft_NSSInternalSoft_Reset                    (0x1U<<9)				//for Master & Slave
#define SPI_NSS_Soft_NSSInternalSoft_Set                      ((0x1U<<9) | (0x1U<<8)) 			//for Master & Slave



//=======================================================


//@ref SPI_BAUDRATEPRESCALER
#define SPI_BAUDRATEPRESCALER_2         (0x00000000U)
#define SPI_BAUDRATEPRESCALER_4         (0b001U << 3 )
#define SPI_BAUDRATEPRESCALER_8         (0b010U << 3)
#define SPI_BAUDRATEPRESCALER_16        (0b011U << 3)
#define SPI_BAUDRATEPRESCALER_32        (0b100U << 3)
#define SPI_BAUDRATEPRESCALER_64        (0b101U << 3)
#define SPI_BAUDRATEPRESCALER_128       (0b110U << 3)
#define SPI_BAUDRATEPRESCALER_256       (0b111U << 3)


//@ref SPI_IRQ_Enable_define
#define SPI_IRQ_Enable_NONE                      		(uint32_t)(0)
#define SPI_IRQ_Enable_TXEIE                       		(uint32_t) (1<<7) //SPI_CR2 Bit 7 TXEIE: Tx buffer empty interrupt enable
#define SPI_IRQ_Enable_RXNEIE                    		((uint32_t)(1<<6)) //SPI_CR2 Bit 6 RXNEIE: RX buffer not empty interrupt enable
#define SPI_IRQ_Enable_ERRIE                       	    (uint32_t) (1<<5) //SPI_CR2 Bit 5 ERRIE: Error interrupt enable

enum PollingMechism{
	Pollingenable ,
	Pollingdisable
};


/*
 *
 *
 * =======================================================================================
 * 							APIs Supported by "MCAL SPI DRIVER"
 * =======================================================================================
 */

void MCAL_SPI_Init (SPI_TypeDef *SPIx, SPI_Config* SPI_Config);
void MCAL_SPI_DeInit (SPI_TypeDef *SPIx);

void MCAL_SPI_GPIO_Set_Pins (SPI_TypeDef *SPIx);

void MCAL_SPI_SendData	(SPI_TypeDef *SPIx, uint16_t *pTxBuffer,enum PollingMechism PollingEn );
void MCAL_SPI_ReceiveData	(SPI_TypeDef *SPIx, uint16_t *pTxBuffer ,enum PollingMechism PollingEn );

void MCAL_SPI_TX_RX	(SPI_TypeDef *SPIx, uint16_t *pTxBuffer,enum PollingMechism PollingEn );


#endif /* STM32F103X8_SPI_DRIVER_H_ */
























