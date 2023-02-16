/**
 ******************************************************************************
 * @file           : motor.h
 * @author         : Nicholas Caccamo
 * @brief          : Header for motor control and PWM functions
 ******************************************************************************
 */
#ifndef MOTOR_H
#define MOTOR_H

#define MOTOR_GEARBOX_RATIO 		34
#define MOTOR_ENCODER_PPR			12
#define MOTOR_ENCODER_CPR			(MOTOR_ENCODER_PPR * 4)
#define MOTOR_ENCODER_SHAFTPPR      (MOTOR_ENCODER_PPR * MOTOR_GEARBOX_RATIO)
#define MOTOR_ENCODER_SHAFTCPR      (MOTOR_ENCODER_CPR * MOTOR_GEARBOX_RATIO)


typedef enum {
	MOTOR_FORWARD = 0,
	MOTOR_REVERSE = 1
}motordirection_t;


//function prototypes
void setMotorDirection(motordirection_t direction);
void setMotorDuty(int16_t duty);
int16_t measureMotorSpeed();


#endif
