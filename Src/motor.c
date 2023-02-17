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
#include <main.h>


motorEncoderInstance_t motorEncoder;




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
	motorEncoder.currentCount = gMotorEncoderCount;
	motorEncoder.counterDirection = (TIM4->CR1 & TIM_CR1_DIR);
	if (motorEncoder.currentCount == motorEncoder.previousCount) {						//motor not moving, speed is zero
		motorEncoder.motorRPM = 0;
		return motorEncoder.motorRPM;
		}


	if (motorEncoder.counterDirection == 0){											//counter is counting up
			if (motorEncoder.currentCount < motorEncoder.previousCount){				//no overflow, counter overflow has occurred
			   motorEncoder.countDifference = motorEncoder.currentCount + (MOTOR_ENCODER_TIMER_ARR - motorEncoder.previousCount);
			}
			else {																		//calculate difference normally
				motorEncoder.countDifference = motorEncoder.currentCount - motorEncoder.previousCount;
			}
	}

	else {																				//counter is counting down
		if (motorEncoder.currentCount > motorEncoder.previousCount){					//counter overflow has occurred
			motorEncoder.countDifference = motorEncoder.previousCount + (MOTOR_ENCODER_TIMER_ARR - motorEncoder.currentCount);
		}
		else {																			//no overflow, calculate difference normally
		   motorEncoder.countDifference = motorEncoder.previousCount - motorEncoder.currentCount;
		}

	}

	motorEncoder.motorRPM = converttoRPM(motorEncoder.countDifference);
	motorEncoder.previousCount = motorEncoder.currentCount;

	return motorEncoder.motorRPM;

}
/************************************************************************************************/


/************************************************************************************************/
/**
 * Function to convert encoder count difference and sampling rate to RPM.
 * Parameters: none
 * Returns: Speed of the motor in RPM
 */
int16_t converttoRPM(int32_t encoderCountDifference){
	int16_t RPM = (encoderCountDifference * 60) / (MOTOR_ENCODER_CPR * MOTOR_GEARBOX_RATIO * MOTOR_ENCODER_SAMPLING_TIME);
	return RPM;
}

/************************************************************************************************/
