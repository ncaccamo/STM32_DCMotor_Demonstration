/**
 ******************************************************************************
 * @file           : timer.c
 * @author         : Nicholas Caccamo
 * @brief          : Timer configuration
 ******************************************************************************
 */

#include <timer.h>
#include <stm32g431xx.h>


/************************************************************************************************/
/**
 * Function to initialize and start Timer 3. An interrupt will be generated periodically.
 * Parameters: none
 * Returns: none
 */
void TIM3Init(){
	//clock enabled in clockconfig.c
	TIM3->CR1 |= (0x01 << TIM_CR1_URS_Pos);		//interrupts only occur on update (overflow/underflow)
	TIM3->DIER |= (0x01 << TIM_DIER_UIE_Pos);	//update interrupt is enabled
	TIM3->PSC = 85-1; 						    //prescalar value (set to yield interrupt at 30 Hz)
	TIM3->CR1 |= (0x01 << TIM_CR1_CEN_Pos);		//counter is enabled


}
/************************************************************************************************/


/************************************************************************************************/
/**
 * Function to initialize and start Timer 4. This timer is used in encoder mode to read the motor encoder.
 * Parameters: none
 * Returns: none
 */
void TIM4Init(){
	//clock enabled in clockconfig.c
	TIM4->SMCR |= (0x03 << TIM_SMCR_SMS_Pos);      //both inputs are active on both rising and falling edges
	TIM4->CCMR1 |= (0x01 << TIM_CCMR1_CC1S_Pos);   //tim_ti1fp1 mapped on tim_ti1
	TIM4->CCMR1 |= (0x01 << TIM_CCMR1_CC2S_Pos);   //tim_ti2fp2 mapped on tim_ti2
	TIM4->CCMR1 |= (0x0A << TIM_CCMR1_IC1F_Pos);   //set input filter on capture 1
	TIM4->CCMR1 |= (0x0A << TIM_CCMR1_IC2F_Pos);   //set input filter on capture 2
	TIM4->CCER &= ~(0x01 << TIM_CCER_CC1P_Pos);    //tim_ti1fp1 noninverted
	TIM4->CCER &= ~(0x01 << TIM_CCER_CC1NP_Pos);
	TIM4->CCER &= ~(0x01 << TIM_CCER_CC2P_Pos);    //tim_ti2fp2 noninverted
	TIM4->CCER &= ~(0x01 << TIM_CCER_CC2NP_Pos);
	//TIM4->CCER |= (0x01 << TIM_CCER_CC1E_Pos);
	//TIM4->CCER |= (0x01 << TIM_CCER_CC2E_Pos);
	TIM4->PSC = 1-1;                           	   //prescalar set to 0
	//TIM4->CR1 |= (0x01 << TIM_CR1_ARPE_Pos);	   //enable auto-reload preload
	TIM4->ARR = 0xFFFF;                     	   //auto-reload register
	TIM4->CR1 |= (0x01 << TIM_CR1_CEN_Pos);        //counter is enabled

}
/************************************************************************************************/


/************************************************************************************************/
/**
 * Function to initialize and start Timer 8. This timer is used to generate PWM output for motor control.
 * Parameters: none
 * Returns: none
 */
void TIM8Init(){
	//clock enabled in clockconfig.c
	TIM8->CCMR1 |= (0x06 << TIM_CCMR1_OC1M_Pos);		//set PWM mode 1
	TIM8->CCMR1 |= (0x01 << TIM_CCMR1_OC1PE_Pos);		//preload register is enabled, for duty cycle
	TIM8->CR1 |= (0x01 << TIM_CR1_ARPE_Pos);			//auto-reload preload is enabled, for frequency
	TIM8->CR1 &= ~(0x03 << TIM_CR1_CMS_Pos);			//edge-aligned mode
	TIM8->CCER &= ~(0x01 << TIM_CCER_CC1P_Pos);			//OC1 active high
	TIM8->CCER |= (0x01 << TIM_CCER_CC1E_Pos);			//OC1 is output on the output pin
	TIM8->CCER &= ~(0x01 << TIM_CCER_CC1NE_Pos);		//tim_oc1n signal is not output
	TIM8->BDTR |= (0x01 << TIM_BDTR_MOE_Pos);			//main output enabled
	TIM8->ARR = 100-1;									//auto-reload, corresponds with PWM frequency
	TIM8->PSC = 170-1;	   								//prescalar of 18, so the input clock is 10Mhz
	TIM8->EGR |= (0x01 << TIM_EGR_UG_Pos);				//initialize shadow registers before counter starts
	TIM8->CR1 |= (0x01 << TIM_CR1_CEN_Pos);             //counter is enabled

}
/************************************************************************************************/


/************************************************************************************************/
/**
 * Function to initialize and start Timer 15. An interrupt will be generated periodically.
 * Parameters: none
 * Returns: none
 */
void TIM15Init(){
	//clock enabled in clockconfig.c
	TIM15->CR1 |= (0x01 << TIM_CR1_URS_Pos);	//interrupts only occur on update (overflow/underflow)
	TIM15->DIER |= (0x01 << TIM_DIER_UIE_Pos);	//update interrupt is enabled
	TIM15->PSC = 1700-1; 						//prescalar value, so the input clock is 100Mhz
	TIM15->ARR = 50000-1;						//auto-reload, so this timer will trigger every 500ms
	TIM15->CR1 |= (0x01 << TIM_CR1_ARPE_Pos);	//enable auto-reload
	TIM15->CR1 |= (0x01 << TIM_CR1_CEN_Pos);	//counter is enabled


}
/************************************************************************************************/



/************************************************************************************************/
/**
 * Function to initialize and start SysTick.
 * Parameters: none
 * Returns: none
 */




/************************************************************************************************/




