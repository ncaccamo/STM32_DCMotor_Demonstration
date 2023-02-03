/**
 ******************************************************************************
 * @file           : gpio.c
 * @author         : Nicholas Caccamo
 * @brief          : GPIO configuration
 ******************************************************************************
 */

#include <gpio.h>
#include <stm32g431xx.h>


void gpioInit(){
	//enable clock for GPIO ports A, B, C
	RCC->AHB2ENR |= (0x01 << RCC_AHB2ENR_GPIOAEN_Pos);
	RCC->AHB2ENR |= (0x01 << RCC_AHB2ENR_GPIOBEN_Pos);
	RCC->AHB2ENR |= (0x01 << RCC_AHB2ENR_GPIOCEN_Pos);

	for (int i=0; i < 1000; i++){}



	GPIOA->MODER = 0x0;
	//GPIOA->MODER |= (0x10 << GPIO_MODER_MODE5_Pos);
	//GPIOA->MODER |= (0x10 << GPIO_MODER_MODE6_Pos);
	//GPIOA->MODER |= (0x10 << GPIO_MODER_MODE7_Pos);

}

