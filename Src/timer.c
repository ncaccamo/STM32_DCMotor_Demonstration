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
	TIM3->DIER |= (0x01 << TIM_DIER_UIE_Pos);	//interrupt is enabled
	TIM3->PSC = 518; 							//prescalar value (set to yield interrupt every 200ms)
	TIM3->CR1 |= (0x01 << TIM_CR1_CEN_Pos);		//counter is enabled


}
/************************************************************************************************/


/************************************************************************************************/
/**
 * Function to initialize and start Timer 4.
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
	TIM4->PSC &= ~(0x01 << TIM_PSC_PSC_Pos);	   //prescalar set to 0
	TIM4->CR1 |= (0x01 << TIM_CR1_ARPE_Pos);	   //enable auto-reload preload
	TIM4->ARR |= (0x00FF << TIM_ARR_ARR_Pos);	   //auto-reload register
	TIM4->CR1 |= (0x01 << TIM_CR1_CEN_Pos);        //counter is enabled

}
/************************************************************************************************/


/************************************************************************************************/
/**
 * Function to initialize and start Timer 8.
 * Parameters: none
 * Returns: none
 */
void TIM8Init(){
	//clock enabled in clockconfig.c
	TIM8->CCMR1 |= (0x06 << TIM_CCMR1_OC1M_Pos);		//set PWM mode 1   //check manual for register bits

					/**
					 * The PWM mode can be selected independently on each channel (one PWM per tim_ocx
					output) by writing ‘0110’ (PWM mode 1) or ‘0111’ (PWM mode 2) in the OCxM bits in the
					TIMx_CCMRx register. The corresponding preload register must be enabled by setting the
					OCxPE bit in the TIMx_CCMRx register, and eventually the auto-reload preload register (in
					upcounting or center-aligned modes) by setting the ARPE bit in the TIMx_CR1 register.
					As the preload registers are transferred to the shadow registers only when an update event
					occurs, before starting the counter, all registers must be initialized by setting the UG bit in
					the TIMx_EGR register.
					tim_ocx polarity is software programmable using the CCxP bit in the TIMx_CCER register. It
					can be programmed as active high or active low. tim_ocx output is enabled by a
					combination of the CCxE, CCxNE, MOE, OSSI and OSSR bits (TIMx_CCER and
					TIMx_BDTR registers). Refer to the TIMx_CCER register description for more details.
					In PWM mode (1 or 2), TIMx_CNT and TIMx_CCRx are always compared to determine
					whether TIMx_CCRx ≤ TIMx_CNT or TIMx_CNT ≤ TIMx_CCRx (depending on the direction
					of the counter).
					The timer is able to generate PWM in edge-aligned mode or center-aligned mode
					depending on the CMS bits in the TIMx_CR1 register.
					 */


//	TIM8->PSC &= ~(0x01 << TIM_PSC_PSC_Pos);	   //prescalar set to 0
//	TIM8->CR1 |= (0x01 << TIM_CR1_ARPE_Pos);	   //enable auto-reload preload
//	TIM8->ARR |= (0x00FF << TIM_ARR_ARR_Pos);	   //auto-reload register
//	TIM8->CR1 |= (0x01 << TIM_CR1_CEN_Pos);        //counter is enabled

}
/************************************************************************************************/




/************************************************************************************************/
/**
 * Function to initialize and start SysTick.
 * Parameters: none
 * Returns: none
 */




/************************************************************************************************/




