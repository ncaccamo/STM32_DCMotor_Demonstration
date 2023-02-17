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
    //interrupts only occur on update (overflow/underflow)
    TIM3->CR1 |= (0x01 << TIM_CR1_URS_Pos);
    //auto-reload preload enabled
    TIM3->CR1 |= (0x01 << TIM_CR1_ARPE_Pos);
    //update interrupt is enabled
    TIM3->DIER |= (0x01 << TIM_DIER_UIE_Pos);
    //prescalar value (set to yield interrupt at 30 Hz)
    TIM3->PSC = 85-1;
    //auto-reload preload
    TIM3->ARR = 0xFFFF;
    //counter is enabled
    TIM3->CR1 |= (0x01 << TIM_CR1_CEN_Pos);

    //Update Frequency = TIM_CLK / (PSC + 1) / (ARR + 1) / (RSR + 1)
    //Update Frequency = 170000000 / 85 / 65535 / 1
    //Update Frequency = 30Hz

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
    //both inputs are active on both rising and falling edges
    TIM4->SMCR |= (0x03 << TIM_SMCR_SMS_Pos);
    //tim_ti1fp1 mapped on tim_ti1
    TIM4->CCMR1 |= (0x01 << TIM_CCMR1_CC1S_Pos);
    //tim_ti2fp2 mapped on tim_ti2
    TIM4->CCMR1 |= (0x01 << TIM_CCMR1_CC2S_Pos);
    //set input filter on capture 1
    TIM4->CCMR1 |= (0x0A << TIM_CCMR1_IC1F_Pos);
    //set input filter on capture 2
    TIM4->CCMR1 |= (0x0A << TIM_CCMR1_IC2F_Pos);
    //tim_ti1fp1 noninverted
    TIM4->CCER &= ~(0x01 << TIM_CCER_CC1P_Pos);
    TIM4->CCER &= ~(0x01 << TIM_CCER_CC1NP_Pos);
    //tim_ti2fp2 noninverted
    TIM4->CCER &= ~(0x01 << TIM_CCER_CC2P_Pos);
    TIM4->CCER &= ~(0x01 << TIM_CCER_CC2NP_Pos);
    //prescalar set to 0
    TIM4->PSC = 1-1;
    //enable auto-reload preload
    TIM4->CR1 |= (0x01 << TIM_CR1_ARPE_Pos);
    //auto-reload register
    TIM4->ARR = 0xFFFF;
    //counter is enabled
    TIM4->CR1 |= (0x01 << TIM_CR1_CEN_Pos);

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
    //set PWM mode 1
    TIM8->CCMR1 |= (0x06 << TIM_CCMR1_OC1M_Pos);
    //preload register is enabled, for duty cycle
    TIM8->CCMR1 |= (0x01 << TIM_CCMR1_OC1PE_Pos);
    //auto-reload preload is enabled, for frequency
    TIM8->CR1 |= (0x01 << TIM_CR1_ARPE_Pos);
    //edge-aligned mode
    TIM8->CR1 &= ~(0x03 << TIM_CR1_CMS_Pos);
    //OC1 active high
    TIM8->CCER &= ~(0x01 << TIM_CCER_CC1P_Pos);
    //OC1 is output on the output pin
    TIM8->CCER |= (0x01 << TIM_CCER_CC1E_Pos);
    //tim_oc1n signal is not output
    TIM8->CCER &= ~(0x01 << TIM_CCER_CC1NE_Pos);
    //main output enabled
    TIM8->BDTR |= (0x01 << TIM_BDTR_MOE_Pos);
    //auto-reload, corresponds with PWM frequency
    TIM8->ARR = 50-1;
    //prescalar of 170, so the input clock is 10Mhz
    TIM8->PSC = 170-1;
    //initialize shadow registers before counter starts
    TIM8->EGR |= (0x01 << TIM_EGR_UG_Pos);
    //counter is enabled
    TIM8->CR1 |= (0x01 << TIM_CR1_CEN_Pos);

    //PWM Frequency = TIM_CLK / (PSC + 1) / (ARR + 1)
    //PWM Frequency = 1700000000 / 170 / 50
    //PWM Frequency = 20Khz

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
    //interrupts only occur on update (overflow/underflow)
    TIM15->CR1 |= (0x01 << TIM_CR1_URS_Pos);
    //update interrupt is enabled
    TIM15->DIER |= (0x01 << TIM_DIER_UIE_Pos);
    //prescalar value, so the input clock is 100Mhz
    TIM15->PSC = 1700-1;
    //auto-reload preload
    TIM15->ARR = 50000-1;
    //enable auto-reload
    TIM15->CR1 |= (0x01 << TIM_CR1_ARPE_Pos);
    //counter is enabled
    TIM15->CR1 |= (0x01 << TIM_CR1_CEN_Pos);

    //Update Frequency = TIM_CLK / (PSC + 1) / (ARR + 1) / (RSR + 1)
    //Update Frequency = 170000000 / 1700 / 50000 / 1
    //Update Frequency = 2Hz (500ms)

}
/************************************************************************************************/



/************************************************************************************************/
/**
 * Function to initialize and start SysTick.
 * Parameters: none
 * Returns: none
 */




/************************************************************************************************/




