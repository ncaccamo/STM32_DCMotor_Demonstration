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
	//clock for GPIO enabled in clockconfig.c

	//clear MODER registers, but leave JTAG pins in reset state
	GPIOA->MODER &= ~(0x00FFFFFF);
	GPIOB->MODER &= ~(0xFFFFF00F);
	GPIOC->MODER &= ~(0xFFFFFFFF);

	//set PA11, PA12 to alternate function mode
	GPIOA->MODER |= (0x02 << GPIO_MODER_MODE11_Pos);
	GPIOA->MODER |= (0x02 << GPIO_MODER_MODE12_Pos);

	//set PA4, PA5, PA7 to alternate function mode, set PA6 to output
	//GPIOA->MODER |= (0x2 << GPIO_MODER_MODE4_Pos);	//not needed because of software NSS control
	GPIOA->MODER |= (0x02 << GPIO_MODER_MODE5_Pos);
	GPIOA->MODER |= (0x01 << GPIO_MODER_MODE6_Pos);
	GPIOA->MODER |= (0x02 << GPIO_MODER_MODE7_Pos);

	//set PA6, PC10, PC12 as output
	GPIOA->MODER |= (0x01 << GPIO_MODER_MODE6_Pos);
	GPIOC->MODER |= (0x01 << GPIO_MODER_MODE10_Pos);
	GPIOC->MODER |= (0x01 << GPIO_MODER_MODE12_Pos);
	//PB12, PC2, PC3 will be used as inputs. Already set by clearing MODER register above.
	//PA6, PC10, PC12 push-pull output, leaving OTYPER register as reset

	//pull-up pull-down register for inputs? PUPDR
	//PC2,PC3,PC13,PC14,PF0

	//set PA11, P12 alternate function to AF10 (TIM4)
	GPIOA->AFR[1] |= (0x0A << GPIO_AFRH_AFSEL11_Pos);		//TIM4_CH1
	GPIOA->AFR[1] |= (0x0A << GPIO_AFRH_AFSEL12_Pos);		//TIM4_CH2

	//set PA4, PA5, PA7 alternate function to AF5 (SPI1)
	//GPIOA->AFR[0] |= (0x05 << GPIO_AFRL_AFSEL4_Pos);		//SPI1_NSS  //not needed because of software NSS control
	GPIOA->AFR[0] |= (0x05 << GPIO_AFRL_AFSEL5_Pos);		//SPI1_SCK
	GPIOA->AFR[0] |= (0x05 << GPIO_AFRL_AFSEL7_Pos);		//SPI1_MOSI

}

