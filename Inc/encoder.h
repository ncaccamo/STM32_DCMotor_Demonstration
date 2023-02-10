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


//#define ENCODER_ROTARY_CLK_PORT 			GPIOA
//#define ENCODER_ROTARY_CLK_SIGNAL 			(ENCODER_ROTARY_CLK_PORT->IDR) & (GPIO_IDR_ID11_Pos)
//#define ENCODER_ROTARY_DT_PORT 				GPIOA
//#define ENCODER_ROTARY_DT_SIGNAL 			(ENCODER_ROTARY_DT_PORT->IDR) & GPIO_IDR_ID12_Pos
//#define ENCODER_ROTARY_SW_PORT 				GPIOB
//#define ENCODER_ROTARY_SW_SIGNAL 			(ENCODER_ROTARY_SW_PORT->IDR) & GPIO_IDR_ID12_Pos
//
//#define ENCODER_MOTOR_SELECT_PORT 			GPIOC
//#define ENCODER_MOTOR_A_SIGNAL 				GPIO_IDR_ID2_Pos
//#define ENCODER_MOTOR_B_SIGNAL 				GPIO_IDR_ID3_Pos


//function prototypes
int32_t encoderRotation();


#endif

