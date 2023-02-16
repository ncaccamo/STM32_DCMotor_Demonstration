/**
 ******************************************************************************
 * @file           : main.h
 * @author         : Nicholas Caccamo
 * @brief          : Header for main
 ******************************************************************************
 */

#ifndef MAIN_H
#define MAIN_H


extern int16_t gRotaryEncoderCount;
extern int16_t gMotorDuty;
extern int16_t gMotorDirection;
extern int16_t gMotorTemperature;
extern int16_t gMotorSpeed;


int _write(int file, char *ptr, int len);







#endif
