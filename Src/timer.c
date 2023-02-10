/**
 ******************************************************************************
 * @file           : timer.c
 * @author         : Nicholas Caccamo
 * @brief          : Timer configuration
 ******************************************************************************
 */

#include <timer.h>
#include <stm32g431xx.h>


void TIM4Init(){

	TIM4->SMCR |= (0x03 << TIM_SMCR_SMS_Pos);    //both inputs are active on both rising and falling edges
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
	//TIM4->CR1 |= (0x01 << TIM_CR1_UIFREMAP_Pos);   //remap UIF status bit to TIM_CNT bit 31

	TIM4->CR1 |= (0x01 << TIM_CR1_CEN_Pos);        //counter is enabled

}
