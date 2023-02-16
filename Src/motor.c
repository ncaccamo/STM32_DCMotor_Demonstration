/**
 ******************************************************************************
 * @file           : motor.c
 * @author         : Nicholas Caccamo
 * @brief          : Motor control and PWM functions
 ******************************************************************************
 */

#include <stm32g431xx.h>
#include <motor.h>
#include <gpio.h>



/************************************************************************************************/
/**
 * Function to set the desired direction of the motor.
 * Parameters: Direction of the motor, either forward or reverse.
 * Returns: none
 */
void setMotorDirection(motordirection_t direction){
			switch (direction) {
				case MOTOR_FORWARD:
					setPin(MOT_DR_IN1_PORT, MOT_DR_IN1_PIN, PIN_HIGH);		//in1 HIGH, in2 LOW for forward
					setPin(MOT_DR_IN2_PORT, MOT_DR_IN2_PIN, PIN_LOW);
					break;
				case MOTOR_REVERSE:
					setPin(MOT_DR_IN1_PORT, MOT_DR_IN1_PIN, PIN_LOW);		//in1 LOW, in2 HIGH for reverse
					setPin(MOT_DR_IN2_PORT, MOT_DR_IN2_PIN, PIN_HIGH);
					break;
			}
}
/************************************************************************************************/


/************************************************************************************************/
/**
 * Function to set the desired speed of the motor.
 * Parameters: Desired duty cycle from 1-100.
 * Returns: none
 */
void setMotorDuty(int16_t duty){					//input speed, no output
	if (duty <= 100 && duty >= 0){
	   TIM8->CCR1 = duty;							//set duty cycle by CCR1 register
	}
}
/************************************************************************************************/


/************************************************************************************************/
/**
 * Function to measure the speed of the motor.
 * Parameters: none
 * Returns: Speed of the motor in RPM
 */
int16_t measureMotorSpeed(){
	int16_t motorEncCounter = TIM4->CNT;
	return motorEncCounter;
}
/************************************************************************************************/
