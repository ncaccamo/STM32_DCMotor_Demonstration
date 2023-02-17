/**
 ******************************************************************************
 * @file           : encoder.h
 * @author         : Nicholas Caccamo
 * @brief          : Header for encoder configuration and driver
 ******************************************************************************
 */
#ifndef ENCODER_H
#define ENCODER_H

#include <stm32g431xx.h>


typedef struct{
    int16_t lastStateCLK;
    int8_t currentStateCLK;
    int8_t currentStateDT;
    int32_t counter;
    int8_t rotationDirection;
}rotaryEncoderInstance_t;


//function prototypes
void rotaryEncoderRotation();
int32_t queryRotaryEncoderCount();


#endif

