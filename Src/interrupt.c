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






}
/************************************************************************************************/




void EXTI15_10_IRQHandler(void){

	if ((EXTI->PR1 & (ENC_SW_PIN)) != 0) {				//check if the encoder switch pin is the one triggering interrupt
		EXTI->PR1 = (ENC_SW_PIN);						//clear interrupt pending bit
		togglePin(DBG_LED_PORT, DBG_LED_PIN);
		printf("switch interrupt\n");
		//fflush(stdout);

		//These don't work? Interrupt keeps firing.
		//NVIC_ClearPendingIRQ(EXTI15_10_IRQn);
		//NVIC_EnableIRQ(EXTI15_10_IRQn);
	}



}


void TIM3_IRQHandler(void){
	TIM3->SR = ~(TIM_SR_UIF);					//clear interrupt pending bit
	togglePin(DBG_LED_PORT, DBG_LED_PIN);
	encoderCount = encoderRotation();
	printf("timer interrupt\n");
}



