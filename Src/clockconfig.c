/**
 ******************************************************************************
 * @file           : clockconfig.c
 * @author         : Nicholas Caccamo
 * @brief          : System clock configuration
 ******************************************************************************
 */

#include <clockconfig.h>
#include <stm32g431xx.h>

void sysClockConfig(){
    //set flash latency to 4
    FLASH->ACR |= (FLASH_ACR_LATENCY_4WS << FLASH_ACR_LATENCY_Pos);


    //enable HSI oscillator and then wait for clock ready flag
    RCC->CR |= (0x01 << RCC_CR_HSION_Pos);
    while (!(RCC->CR & (0x01 << RCC_CR_HSIRDY_Pos)));

    //set AHB, APB2, APB1 prescalar
    RCC->CFGR |= (0x00 << RCC_CFGR_HPRE_Pos);   //AHB prescalar no division
    RCC->CFGR |= (0x00 << RCC_CFGR_PPRE2_Pos);  //APB2 prescalar no division
    RCC->CFGR |= (0x00 << RCC_CFGR_PPRE1_Pos);  //APB1 prescalar no division

    //set PLL configuration register
    RCC->PLLCFGR |= (0x2 << RCC_PLLCFGR_PLLSRC_Pos);   //HSI16 as PLL clock entry
    RCC->PLLCFGR |= (0x3 << RCC_PLLCFGR_PLLM_Pos);     //PLLM division /4
    RCC->PLLCFGR |= (0x55 << RCC_PLLCFGR_PLLN_Pos);    //PLLN multiplication *85
    RCC->PLLCFGR |= (0x00 << RCC_PLLCFGR_PLLPEN_Pos);  //PLLP disabled
    RCC->PLLCFGR |= (0x00 << RCC_PLLCFGR_PLLP_Pos);    //PLLP division factor not used
    RCC->PLLCFGR |= (0x00 << RCC_PLLCFGR_PLLQEN_Pos);  //PLLQ disabled
    RCC->PLLCFGR |= (0x00 << RCC_PLLCFGR_PLLQ_Pos);    //PLLQ division /2
    RCC->PLLCFGR |= (0x01 << RCC_PLLCFGR_PLLREN_Pos);  //PLLR enabled (output of PLL)
    RCC->PLLCFGR |= (0x00 << RCC_PLLCFGR_PLLR_Pos);    //PLLR division /2
    RCC->PLLCFGR |= (0x02 << RCC_PLLCFGR_PLLPDIV_Pos); //PLLP division /2

    //enable PLL and wait for ready
    RCC->CR |= (0x01 << RCC_CR_PLLON_Pos);
    while(!(RCC->CR & (0x01 << RCC_CR_PLLRDY_Pos)));

    //set PLL as system clock and wait for ready
    RCC->CFGR |= (0x03 << RCC_CFGR_SW_Pos);
    while (!(RCC->CFGR & (0x03 << RCC_CFGR_SWS_Pos)));

    //enable clock for Power Control
    RCC->APB1ENR1 |= (0x01 << RCC_APB1ENR1_PWREN_Pos);

    //enable clock for System Configuration controller
    RCC->APB2ENR |= (0x01 << RCC_APB2SMENR_SYSCFGSMEN_Pos);

    //enable clock for GPIO ports A, B, C, D
    RCC->AHB2ENR |= (0x01 << RCC_AHB2ENR_GPIOAEN_Pos);
    RCC->AHB2ENR |= (0x01 << RCC_AHB2ENR_GPIOBEN_Pos);
    RCC->AHB2ENR |= (0x01 << RCC_AHB2ENR_GPIOCEN_Pos);
    RCC->AHB2ENR |= (0x01 << RCC_AHB2ENR_GPIODEN_Pos);

    //enable clock for TIM3, TIM4, TIM8, TIM15
    RCC->APB1ENR1 |= (0x01 << RCC_APB1ENR1_TIM3EN_Pos);
    RCC->APB1ENR1 |= (0x01 << RCC_APB1ENR1_TIM4EN_Pos);
    RCC->APB2ENR |= (0x01 << RCC_APB2ENR_TIM8EN_Pos);
    RCC->APB2ENR |= (0x01 << RCC_APB2ENR_TIM15EN_Pos);

    //enable clock for SPI3
    RCC->APB1ENR1 |= (0x01 << RCC_APB1ENR1_SPI3EN_Pos);

    //enable clock for ADC1
    RCC->AHB2ENR |= (0x01 << RCC_AHB2ENR_ADC12EN_Pos);
    //system clock selected as ADC1/2 clock
    RCC->CCIPR |= (0x02 << RCC_CCIPR_ADC12SEL_Pos);


}
