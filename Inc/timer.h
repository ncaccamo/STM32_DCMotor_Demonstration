/**
 ******************************************************************************
 * @file           : timer.h
 * @author         : Nicholas Caccamo
 * @brief          : Header for timer configuration
 ******************************************************************************
 */
#ifndef TIMER_H
#define TIMER_H

#include <stdint.h>

extern volatile uint16_t gMsTicks;


//function prototypes
void TIM3Init();
void TIM4Init();
void TIM8Init();
void TIM15Init();
void delayMs(uint16_t ms);





#endif
