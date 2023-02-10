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


/**
To configure a line as an interrupt source, use the following procedure:
1. Configure the corresponding mask bit in the EXTI_IMR register.
2. Configure the Trigger Selection bits of the Interrupt line (EXTI_RTSR and EXTI_FTSR).
3. Configure the enable and mask bits that control the NVIC IRQ channel mapped to the
EXTI so that an interrupt coming from one of the EXTI lines can be correctly
acknowledged.
**/

void interruptInit(){
//System Configuration clock enabled in clockconfig.c
//EXTI12, EXTI Line12 Interrupt, SYSCFG_EXTICR4 - PB15 (Rotary Encoder SW)
SYSCFG->EXTICR[3] |= (0x01 << SYSCFG_EXTICR4_EXTI15_Pos);
//EXTI0, EXTI Line0 Interrupt, SYSCFG_EXTICR1 - PF0 (Rotary Encoder SW)
//SYSCFG->EXTICR[0] |= (0x05 << SYSCFG_EXTICR1_EXTI0_Pos);

//set interrupts to maskable
EXTI->IMR1 &= ~(0x01 << EXTI_IMR1_IM15_Pos);
//EXTI->IMR1 |= (0x00 << EXTI_IMR1_IM0_Pos);

//set interrupts to trigger on rising edge
//EXTI->RTSR1 |= (0x01 << EXTI_RTSR1_RT12_Pos);
//EXTI->RTSR1 |= (0x01 << EXTI_RTSR1_RT0_Pos);

//set interrupts to trigger on falling edge
EXTI->FTSR1 |= (0x01 << EXTI_FTSR1_FT15_Pos);
//EXTI->FTSR1 |= (0x01 << EXTI_FTSR1_FT0_Pos);


NVIC_SetPriority(EXTI15_10_IRQn, 0);
NVIC_EnableIRQ(EXTI15_10_IRQn);


}





void EXTI15_10_IRQHander(void){
	NVIC_ClearPendingIRQ(EXTI15_10_IRQn);	    //ext interrupt cleared by writing one
	printf("switch interrupt\n");
	fflush(stdout);


}



