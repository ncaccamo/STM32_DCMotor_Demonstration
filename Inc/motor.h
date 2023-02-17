/**
 ******************************************************************************
 * @file           : motor.h
 * @author         : Nicholas Caccamo
 * @brief          : Header for motor control and PWM functions
 ******************************************************************************
 */
#ifndef MOTOR_H
#define MOTOR_H


#define MOTOR_GEARBOX_RATIO           34
#define MOTOR_ENCODER_PPR             12
#define MOTOR_ENCODER_CPR             (MOTOR_ENCODER_PPR * 4)
#define MOTOR_ENCODER_SHAFTPPR        (MOTOR_ENCODER_PPR * MOTOR_GEARBOX_RATIO)
#define MOTOR_ENCODER_SHAFTCPR        (MOTOR_ENCODER_CPR * MOTOR_GEARBOX_RATIO)
#define MOTOR_ENCODER_SAMPLING_TIME   0.03333    //time per cycle in seconds
#define MOTOR_ENCODER_TIMER_ARR       TIM4->ARR
#define MOTOR_ENCODER_TIMER_CNT       TIM4->CNT
#define MOTOR_ENCODER_TIMER_CNT_DIR   (TIM4->CR1 & TIM_CR1_DIR)
#define MOTOR_PWM_TIMER_CRR           TIM8->CCR1



typedef enum {
    MOTOR_FORWARD = 0,
    MOTOR_REVERSE = 1
}motordirection_t;

typedef struct {
    int32_t currentCount;
    int32_t previousCount;
    int32_t countDifference;
    int16_t counterDirection;
}motorEncoderInstance_t;

typedef struct {
    int16_t motorDuty;
    int16_t motorDirection;
    int16_t motorSpeed;
}motorStatus_t;


//function prototypes
void attemptSetMotorDirection(motordirection_t direction);
void setMotorDuty(int16_t duty);
void measureMotorSpeed();
int16_t converttoRPM(int32_t encoderCountDifference);
int16_t queryMotorDirection();
void updateMotorDirectionState(int16_t direction);
int16_t queryMotorSpeed();
int16_t queryMotorDuty();

#endif
