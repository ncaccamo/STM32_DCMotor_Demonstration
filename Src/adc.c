/**
 ******************************************************************************
 * @file           : adc.c
 * @author         : Nicholas Caccamo
 * @brief          : ADC configuration
 ******************************************************************************
 */

#include <stm32g431xx.h>
#include <timer.h>

void ADC1Init(){
    //system clock for ADC1 and and power control clock enabled in clockconfig.c
    //GPIO for input pin configured in gpio.c

    //this section must be set before ADC is enabled
    //exit deep-power-down mode
    ADC1->CR &= ~(ADC_CR_DEEPPWD);
    //enable voltage regulator
    ADC1->CR |= (ADC_CR_ADVREGEN);
    //wait 12us for reference voltage, according to datasheet
    delayMs(1);
    //channel 2 single ended mode.
    ADC1->DIFSEL &= ~(0x04);
    //ADC clock prescalar divider of 6
    ADC12_COMMON->CCR |= (0x03 << ADC_CCR_PRESC_Pos);
    //calibrate ADC and wait for it to finish
    ADC1->CR &= ~(ADC_CR_ADCALDIF);
    ADC1->CR |= (ADC_CR_ADCAL);
    while(ADC1->CR & (ADC_CR_ADCAL));

    //this section enables the ADC
    //clear ADRDY bit
    ADC1->ISR = (ADC_ISR_ADRDY);
    //ADC enabled
    ADC1->CR |= (ADC_CR_ADEN);
    //wait for ADRDY
    while(!(ADC1->ISR & ADC_ISR_ADRDY));

    //the following section must be set after ADC is enabled
    //12-bit ADC resolution
    ADC1->CFGR &= ~(0x03 << ADC_CFGR_RES_Pos);
    //ADC_SMPR1_SMP2 sampling time?
    //program a sequence length of 1, channel 2 conversion
    ADC1->SQR1 &= ~(0x0A << ADC_SQR1_L_Pos);
    ADC1->SQR1 |= (0x02 << ADC_SQR1_SQ1_Pos);



}

