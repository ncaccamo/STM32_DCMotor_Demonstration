/**
 ******************************************************************************
 * @file           : motor.c
 * @author         : Nicholas Caccamo
 * @brief          : Motor control and PWM functions
 ******************************************************************************
 */

#include <motor.h>
#include <gpio.h>


/**
 * Pulse Width Modulation mode allows to generate a signal with a frequency determined by
the value of the TIMx_ARR register and a duty cycle determined by the value of the
TIMx_CCRx register.



 */


/************************************************************************************************/
/**
 * Function to set the desired direction of the motor.
 * Parameters: Direction of the motor, either forward or reverse.
 * Returns: none
 */
void setMotorDirection(motordirection_t direction){				//must check that motor is stopped
	//if (motor)
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
 * Parameters:
 * Returns: none
 */
void setMotorSpeed(){					//input speed, no output
										//set duty cycle by CCR1 register
}
/************************************************************************************************/
