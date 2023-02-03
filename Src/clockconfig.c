/**
 ******************************************************************************
 * @file           : clockconfig.c
 * @author         : Nicholas Caccamo
 * @brief          : System clock configuration
 ******************************************************************************
 */

/*************>>>>>>> STEPS FOLLOWED <<<<<<<<************

	1. ENABLE HSE and wait for the HSE to become Ready
	2. Set the POWER ENABLE CLOCK and VOLTAGE REGULATOR
	3. Configure the FLASH PREFETCH and the LATENCY Related Settings
	4. Configure the PRESCALARS HCLK, PCLK1, PCLK2
	5. Configure the MAIN PLL
	6. Enable the PLL and wait for it to become ready
	7. Select the Clock Source and wait for it to be set

	********************************************************/

#include <clockconfig.h>
#include <stm32g431xx.h>

void sysClockConfig(){
	//Enable HSE oscillator and then wait for clock ready flag
	RCC->CR |= (0x01 << RCC_CR_HSEON_Pos);
	while (!(RCC->CR & (0x01 << RCC_CR_HSERDY_Pos)));

	RCC->APB1ENR1 |= (0x01 << RCC_APB1ENR1_PWREN_Pos);


}
