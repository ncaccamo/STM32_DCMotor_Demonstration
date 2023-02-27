/**
 ******************************************************************************
 * @file           : gpio.c
 * @author         : Nicholas Caccamo
 * @brief          : Interrupt routine initialization
 ******************************************************************************
 */

#include <interrupt.h>
#include <stm32g431xx.h>
#include <stdio.h>
#include <main.h>
#include <gpio.h>
#include <encoder.h>
#include <motor.h>
#include <timer.h>
#include <display.h>



/************************************************************************************************/
/**
 * Function to initialize interrupts.
 * Parameters: none
 * Returns: none
 */
void interruptInit(){
    //System Configuration clock enabled in clockconfig.c

    //GPIO interrupt for encoder switch
    SYSCFG->EXTICR[3] |= (0x01 << SYSCFG_EXTICR4_EXTI15_Pos);		//EXTI Line15 Interrupt, PB15 (Rotary Encoder SW)
    EXTI->IMR1 |= (0x01 << EXTI_IMR1_IM15_Pos);     				//set interrupt mask register
    EXTI->FTSR1 |= (0x01 << EXTI_FTSR1_FT15_Pos);					//trigger on falling edge
    NVIC_SetPriority(EXTI15_10_IRQn, 0);							//set priority and enable EXTI15_10_IRQHandler
    NVIC_EnableIRQ(EXTI15_10_IRQn);

    //enable timer interrupt for TIM3
    NVIC_SetPriority(TIM3_IRQn, 0);
    NVIC_EnableIRQ(TIM3_IRQn);

    //enable timer interrupt for TIM15
    NVIC_SetPriority(TIM1_BRK_TIM15_IRQn, 0);
    NVIC_EnableIRQ(TIM1_BRK_TIM15_IRQn);


}
/************************************************************************************************/



/************************************************************************************************/
/**
 * IRQ Handler and ISR for EXTI lines 10-15 interrupts.
 * Parameters: none
 * Returns: none
 */
void EXTI15_10_IRQHandler(void){
    //check if the encoder switch pin is the one triggering interrupt
    if ((EXTI->PR1 & (ENC_SW_PIN)) != 0) {
        //clear interrupt pending bit
        EXTI->PR1 = (ENC_SW_PIN);
        //change motor direction based on current setting
        switch (queryMotorDirection()) {
        case MOTOR_FORWARD:
            attemptSetMotorDirection(MOTOR_REVERSE);
            break;
        case MOTOR_REVERSE:
            attemptSetMotorDirection(MOTOR_FORWARD);
            break;
        }
    }
    printf("switch interrupt\n");

    //These don't work? Interrupt keeps firing.
    //NVIC_ClearPendingIRQ(EXTI15_10_IRQn);
    //NVIC_EnableIRQ(EXTI15_10_IRQn);
}

/************************************************************************************************/

/************************************************************************************************/
/**
 * IRQ Handler and ISR for TIM3 interrupts.
 * Parameters: none
 * Returns: none
 */
void TIM3_IRQHandler(void){
    //check if the interrupt is caused by update event
    if ((TIM3->SR & (TIM_SR_UIF)) != 0) {
        //clear interrupt pending bit
        TIM3->SR = ~(TIM_SR_UIF);
        //check encoder movement, update count
        rotaryEncoderRotation();
        //set motor duty cycle based on encoder count
        setMotorDuty(queryRotaryEncoderCount());
        //measure the motor speed
        measureMotorSpeed();
        }
}
/************************************************************************************************/


/************************************************************************************************/
/**
 * IRQ Handler and ISR for "TIM1 Break, Transition error, Index error and TIM15 global interrupt"
 * Parameters: none
 * Returns: none
 */
void TIM1_BRK_TIM15_IRQHandler(void){
    //check if the interrupt is caused by TIM15 update event
    if ((TIM15->SR & (TIM_SR_UIF)) != 0) {
        //clear interrupt pending bit
        TIM15->SR = ~(TIM_SR_UIF);
        //display draw flag set every interrupt
        gDrawFlag = 1;
        //temperature measurement flag set every 20 interrupts
        static int8_t temperatureCount = 0;
        temperatureCount++;
        if (temperatureCount >= 20){
            temperatureCount = 0;
            gTemperatureFlag = 1;
        }
    }

}
/************************************************************************************************/

/************************************************************************************************/
/**
 * IRQ Handler and ISR for SysTick
 * Parameters: none
 * Returns: none
 */
void SysTick_Handler(void)
{
    gMsTicks++;
}
/************************************************************************************************/
