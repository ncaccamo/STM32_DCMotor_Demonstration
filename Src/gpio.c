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
    GPIOA->MODER &= ~(0x03FFFFFF);
    GPIOB->MODER &= ~(0xFFFFFC3F);
    GPIOC->MODER &= ~(0xFFFFFFFF);
    GPIOD->MODER &= ~(0xFFFFFFFF);



    //set PB13, PB14, PB15 set as inputs (rotary encoder)
    GPIOB->MODER &= ~(0x03 << GPIO_MODER_MODE13_Pos);
    GPIOB->MODER &= ~(0x03 << GPIO_MODER_MODE14_Pos);
    GPIOB->MODER &= ~(0x03 << GPIO_MODER_MODE15_Pos);

    //set pull-up pull-down register for inputs
    GPIOB->PUPDR |= (0x01 << GPIO_PUPDR_PUPD13_Pos);  //PU
    GPIOB->PUPDR |= (0x01 << GPIO_PUPDR_PUPD14_Pos);  //PU
    GPIOB->PUPDR |= (0x01 << GPIO_PUPDR_PUPD15_Pos);  //PU


    //set outputs
    GPIOA->MODER |= (0x01 << GPIO_MODER_MODE15_Pos);     //Display_RES
    GPIOC->MODER |= (0x01 << GPIO_MODER_MODE11_Pos);     //Display_CS
    GPIOD->MODER |= (0x01 << GPIO_MODER_MODE2_Pos);      //Display_DC
    GPIOA->MODER |= (0x01 << GPIO_MODER_MODE9_Pos);      //Motor Driver In2
    GPIOC->MODER |= (0x01 << GPIO_MODER_MODE7_Pos);      //Motor Driver In1

    //set outputs as push-pull
    GPIOA->OTYPER &= ~(0x01 << GPIO_MODER_MODE15_Pos);
    GPIOC->OTYPER &= ~(0x01 << GPIO_MODER_MODE11_Pos);
    GPIOD->OTYPER &= ~(0x01 << GPIO_MODER_MODE2_Pos);
    GPIOA->OTYPER &= ~(0x01 << GPIO_MODER_MODE9_Pos);
    GPIOC->OTYPER &= ~(0x01 << GPIO_MODER_MODE7_Pos);



    //set PA11, PA12 to alternate function mode (TIM4)
    GPIOA->MODER |= (0x02 << GPIO_MODER_MODE11_Pos);
    GPIOA->MODER |= (0x02 << GPIO_MODER_MODE12_Pos);

    //set PA11, P12 alternate function to AF10 (TIM4)
    GPIOA->AFR[1] |= (0x0A << GPIO_AFRH_AFSEL11_Pos);       //TIM4_CH1
    GPIOA->AFR[1] |= (0x0A << GPIO_AFRH_AFSEL12_Pos);       //TIM4_CH2

    //set PB6 to alternate function mode AF5 (TIM8)
    GPIOB->MODER |= (0x02 << GPIO_MODER_MODE6_Pos);
    GPIOB->AFR[0] |= (0x05 << GPIO_AFRL_AFSEL6_Pos);        //TIM8_CH1

    //set PC10, PC12 alternate function mode (SPI3)
    GPIOC->MODER |= (0x02 << GPIO_MODER_MODE10_Pos);
    GPIOC->MODER |= (0x02 << GPIO_MODER_MODE12_Pos);

    //set PC10, PC12 alternate function to AF6 (SPI3)
    GPIOC->AFR[1] |= (0x06 << GPIO_AFRH_AFSEL10_Pos);       //SPI3_SCK
    GPIOC->AFR[1] |= (0x06 << GPIO_AFRH_AFSEL12_Pos);       //SPI3_MOSI

    //set PA1 to analog input
    GPIOA->MODER |= (0x03 << GPIO_MODER_MODE1_Pos);

    //set PA5 as output for onboard debug LED
    GPIOA->MODER |= (0x01 << GPIO_MODER_MODE5_Pos);
    GPIOA->OTYPER &= ~(0x01 << GPIO_MODER_MODE5_Pos);
}
/************************************************************************************************/





/************************************************************************************************/
/**
 * Function to read the state of an input GPIO pin, adopted from STM32 HAL.
 * Parameters: GPIOx is the GPIO port, where x can be A..E.
 * 			   GPIO_PIN_x is the GPIO pin number, where x can be 0...15. This is the pin's position in the register.
 * Returns: PIN_LOW or PIN_HIGH for state of pin.
 */
int16_t readPin(GPIO_TypeDef *GPIOx, uint16_t GPIO_PIN_x){
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
void setPin(GPIO_TypeDef *GPIOx, uint16_t GPIO_PIN_x, pinstate_t pinState){
    if (pinState == PIN_LOW){
        //set pin LOW
        GPIOx->BSRR = (GPIO_PIN_x << 16U);
    }
    else if (pinState == PIN_HIGH){
        //set pin HIGH
        GPIOx->BSRR = GPIO_PIN_x;
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
        //set pin LOW
        GPIOx->BSRR = (GPIO_PIN_x << 16U);
    }
    else {
        //set pin HIGH
        GPIOx->BSRR = GPIO_PIN_x;
    }
}
/************************************************************************************************/


