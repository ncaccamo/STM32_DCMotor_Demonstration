/**
 ******************************************************************************
 * @file           : main.h
 * @author         : Nicholas Caccamo
 * @brief          : Header for main
 ******************************************************************************
 */

#ifndef MAIN_H
#define MAIN_H


extern volatile int16_t gRotaryEncoderCount;
extern volatile int16_t gMotorDuty;
extern volatile int16_t gMotorEncoderCount;
extern volatile int16_t gMotorDirection;
extern volatile int16_t gMotorTemperature;
extern volatile int16_t gMotorSpeed;


int _write(int file, char *ptr, int len);







#endif
