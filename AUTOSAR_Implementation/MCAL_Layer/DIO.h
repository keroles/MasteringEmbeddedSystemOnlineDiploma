/*
 * DIO.h
 *
 *  Created on: Feb 23, 2022
 *      Author: kkhalil
 */

#ifndef MCAL_LAYER_DIO_H_
#define MCAL_LAYER_DIO_H_
#include "stm32f103x8_gpio_driver.h"

unsigned char Dio_ReadChannel	(unsigned char ID);
void 		  Dio_WriteChannel	(unsigned char ID,unsigned char Level);

//DIO IDs (PORT A)
#define 	DIO_Door 	GPIO_PIN_3
#define 	LED_ID	 	GPIO_PIN_7

//Port Used
#define GPIO_Port_Used  GPIOA

#endif /* MCAL_LAYER_DIO_H_ */
