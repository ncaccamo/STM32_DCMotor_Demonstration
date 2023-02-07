/**
 ******************************************************************************
 * @file           : gpio.c
 * @author         : Nicholas Caccamo
 * @brief          : Header for encoder configuration and driver
 ******************************************************************************
 */
#ifndef ENCODER_H
#define ENCODER_H

#include <stm32g431xx.h>


#define ENCODER_ROTARY_SELECT_PORT 			GPIOA
#define ENCODER_ROTARY_CLK_SIGNAL 			GPIO_IDR_ID13_Pos
#define ENCODER_ROTARY_DT_SIGNAL 			GPIO_IDR_ID14_Pos
#define ENCODER_ROTARY_SW_SIGNAL 			GPIO_IDR_ID15_Pos

#define ENCODER_MOTOR_SELECT_PORT 			GPIOC
#define ENCODER_MOTOR_A_SIGNAL 				GPIO_IDR_ID2_Pos
#define ENCODER_MOTOR_B_SIGNAL 				GPIO_IDR_ID3_Pos





#endif
