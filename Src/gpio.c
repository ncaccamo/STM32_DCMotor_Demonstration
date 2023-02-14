/**
 ******************************************************************************
 * @file           : gpio.c
 * @author         : Nicholas Caccamo
 * @brief          : GPIO configuration
 ******************************************************************************
 */

#include <gpio.h>
#include <stm32g431xx.h>

/**
 * Function to set the GPIO registers.
 * Parameters: none
 * Returns: none
 */

void gpioInit(){
	//clock for GPIO enabled in clockconfig.c

	//clear MODER registers, but leave JTAG pins in reset state
	GPIOA->MODER &= ~(0x00FFFFFF);
	GPIOB->MODER &= ~(0xFFFFF00F);
	GPIOC->MODER &= ~(0xFFFFFFFF);



	//set PB13, PB14, PB15 set as inputs (rotary encoder)
	GPIOB->MODER &= ~(0x03 << GPIO_MODER_MODE13_Pos);
	GPIOB->MODER &= ~(0x03 << GPIO_MODER_MODE14_Pos);
	GPIOB->MODER &= ~(0x03 << GPIO_MODER_MODE15_Pos);

	//set pull-up pull-down register for inputs
	GPIOB->PUPDR |= (0x01 << GPIO_PUPDR_PUPD13_Pos);  //PU
	GPIOB->PUPDR |= (0x01 << GPIO_PUPDR_PUPD14_Pos);  //PU
	GPIOB->PUPDR |= (0x01 << GPIO_PUPDR_PUPD15_Pos);  //PU



	//set PA6, PA9, PC7 as output
	GPIOA->MODER |= (0x01 << GPIO_MODER_MODE6_Pos);  //Display_DC
	GPIOA->MODER |= (0x01 << GPIO_MODER_MODE9_Pos);  //Motor Driver In2
	GPIOC->MODER |= (0x01 << GPIO_MODER_MODE7_Pos);  //Motor Driver In1

	//set PA6, PA9, PC7 as push-pull output
	GPIOA->OTYPER &= ~(0x01 << GPIO_MODER_MODE6_Pos);
	GPIOA->OTYPER &= ~(0x01 << GPIO_MODER_MODE9_Pos);
	GPIOC->OTYPER &= ~(0x01 << GPIO_MODER_MODE7_Pos);



	//set PA11, PA12 to alternate function mode (TIM4)
	GPIOA->MODER |= (0x02 << GPIO_MODER_MODE11_Pos);
	GPIOA->MODER |= (0x02 << GPIO_MODER_MODE12_Pos);

	//set PA11, P12 alternate function to AF10 (TIM4)
	GPIOA->AFR[1] |= (0x0A << GPIO_AFRH_AFSEL11_Pos);		//TIM4_CH1
	GPIOA->AFR[1] |= (0x0A << GPIO_AFRH_AFSEL12_Pos);		//TIM4_CH2

	//set PB6 to alternate function mode AF5 (TIM8)
	GPIOB->MODER |= (0x02 << GPIO_MODER_MODE6_Pos);
	GPIOB->AFR[0] |= (0x05 << GPIO_AFRL_AFSEL6_Pos);		//TIM8_CH1

	//set PA4, PA5, PA7 to alternate function mode (SPI1)
	GPIOA->MODER |= (0x02 << GPIO_MODER_MODE4_Pos);
	GPIOA->MODER |= (0x02 << GPIO_MODER_MODE5_Pos);
	GPIOA->MODER |= (0x02 << GPIO_MODER_MODE7_Pos);

	//set PA4, PA5, PA7 alternate function to AF5 (SPI1)
	GPIOA->AFR[0] |= (0x05 << GPIO_AFRL_AFSEL4_Pos);		//SPI1_NSS
	GPIOA->AFR[0] |= (0x05 << GPIO_AFRL_AFSEL5_Pos);		//SPI1_SCK
	GPIOA->AFR[0] |= (0x05 << GPIO_AFRL_AFSEL7_Pos);		//SPI1_MOSI

	//set PA0? to ADC input



	//set PB1 as output for LED debugging
	GPIOB->MODER |= (0x01 << GPIO_MODER_MODE1_Pos);
	GPIOB->OTYPER &= ~(0x01 << GPIO_MODER_MODE1_Pos);
}
/************************************************************************************************/





/************************************************************************************************/
/**
 * Function to read the state of an input GPIO pin, adopted from STM32 HAL.
 * Parameters: GPIOx is the GPIO port, where x can be A..E.
 * 			   GPIO_PIN_x is the GPIO pin number, where x can be 0...15. This is the pin's position in the register.
 * Returns: PIN_LOW or PIN_HIGH for state of pin.
 */

int32_t readPin(GPIO_TypeDef *GPIOx, uint16_t GPIO_PIN_x){
	if ((GPIOx->IDR & GPIO_PIN_x) != PIN_LOW) {
		return PIN_HIGH;
	}
	else {
		return PIN_LOW;
	}
}
/************************************************************************************************/



/************************************************************************************************/
/**
 * Function to set the state of an output GPIO pin using the bit set/reset register (BSRR).
 * Parameters: GPIOx is the GPIO port, where x can be A..E.
 * 			   GPIO_PIN_x is the GPIO pin number, where x can be 0...15. This is the pin's position in the register.
 *             pinState is the desired pin setting and can be PIN_HIGH or PIN_LOW.
 * Returns: none
 */

void setPin(GPIO_TypeDef *GPIOx, uint16_t GPIO_PIN_x, pinState_t pinState){
	if (pinState == PIN_LOW){
	GPIOx->BSRR = (GPIO_PIN_x << 16U);          //set pin LOW
	}
	else if (pinState == PIN_HIGH){
	GPIOx->BSRR = GPIO_PIN_x;                  //set pin HIGH
	}
}
/************************************************************************************************/

/************************************************************************************************/
/**
 * Function to toggle the state of an output GPIO pin using the bit set/reset register (BSRR).
 * Parameters: GPIOx is the GPIO port, where x can be A..E.
 * 			   GPIO_PIN_x is the GPIO pin number, where x can be 0...15. This is the pin's position in the register.
 *             pinState is the desired pin setting and can be PIN_HIGH or PIN_LOW.
 * Returns: none
 */

void togglePin(GPIO_TypeDef *GPIOx, uint16_t GPIO_PIN_x){

	if ((GPIOx->ODR & GPIO_PIN_x) != PIN_LOW) {
		GPIOx->BSRR = (GPIO_PIN_x << 16U);    //set pin LOW
	}
	else {
		GPIOx->BSRR = GPIO_PIN_x;            //set pin HIGH
	}
}
/************************************************************************************************/


