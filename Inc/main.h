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
extern volatile int16_t gMotorTemperature;


int _write(int file, char *ptr, int len);







#endif
