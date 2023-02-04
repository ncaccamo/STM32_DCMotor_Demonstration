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
	GPIOC->MODER &= ~(0xFFFFFFFF);

	//set PA4, PA5, PA7 to alternate function mode, set PA6 to output
	GPIOA->MODER |= (0x2 << GPIO_MODER_MODE4_Pos);
	GPIOA->MODER |= (0x2 << GPIO_MODER_MODE5_Pos);
	GPIOA->MODER |= (0x1 << GPIO_MODER_MODE6_Pos);
	GPIOA->MODER |= (0x2 << GPIO_MODER_MODE7_Pos);

	//set PC10, PC12 as output
	GPIOC->MODER |= (0x1 << GPIO_MODER_MODE10_Pos);
	GPIOC->MODER |= (0x1 << GPIO_MODER_MODE12_Pos);
	//PC2, PC3, PC13, PC14, PC15 will be used as inputs. Already set by clearing MODER register above.
	//PC10, PC12 push-pull output, leaving OTYPER register as reset

	//pull-up pull-down register for inputs? PUPDR
	//PC2,PC3,PC13,PC14,PC15

	//set PA4, PA5, PA7 alternate function to AF5 (SPI1)
	GPIOA->AFR[0] |= (0x5 << GPIO_AFRL_AFSEL4_Pos);
	GPIOA->AFR[0] |= (0x5 << GPIO_AFRL_AFSEL5_Pos);
	GPIOA->AFR[0] |= (0x5 << GPIO_AFRL_AFSEL7_Pos);

}

