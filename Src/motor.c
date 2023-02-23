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




static motorStatus_t motorStatus;
static motorEncoderInstance_t motorEncoder;
const int8_t sizeBuffer = 50;

/************************************************************************************************/
/**
 * Function to attempt setting the desired direction of the motor. The direction can only be changed when
 * the motor is stopped, so this function will not change the motor direction if the motor is moving.
 * Parameters: Desired direction of the motor, either forward or reverse.
 * Returns: Direction of the motor, either forward or reverse.
 */
void attemptSetMotorDirection(motordirection_t direction){
    //check that motor is stopped before changing direction
    if (TIM8->CCR1 == 0) {
        switch (direction) {
        case MOTOR_FORWARD:
            //in1 HIGH, in2 LOW for forward
            setPin(MOT_DR_IN1_PORT, MOT_DR_IN1_PIN, PIN_HIGH);
            setPin(MOT_DR_IN2_PORT, MOT_DR_IN2_PIN, PIN_LOW);
            motorStatus.motorDirection = MOTOR_FORWARD;
            break;
        case MOTOR_REVERSE:
            //in1 LOW, in2 HIGH for reverse
            setPin(MOT_DR_IN1_PORT, MOT_DR_IN1_PIN, PIN_LOW);
            setPin(MOT_DR_IN2_PORT, MOT_DR_IN2_PIN, PIN_HIGH);
            motorStatus.motorDirection = MOTOR_REVERSE;
            break;
        }
    } else {
        //blink screen
    }
}
/************************************************************************************************/


/************************************************************************************************/
/**
 * Function to set the desired speed of the motor. Writes to capture/compare register used by PWM. Updates duty variable.
 * Parameters: Desired duty cycle from 1-100.
 * Returns: none
 */
void setMotorDuty(int16_t duty){
    if (duty <= 100 && duty >= 0){
        //set duty cycle by setting CCR1 register
        MOTOR_PWM_TIMER_CRR = duty;
        motorStatus.motorDuty = duty;
    }
}
/************************************************************************************************/


/************************************************************************************************/
/**
 * Function to measure the speed of the motor. Updates motor speed variable.
 * Parameters: none
 * Returns: none
 */
void measureMotorSpeed(){

    motorEncoder.currentCount = MOTOR_ENCODER_TIMER_CNT;
    motorEncoder.counterDirection = MOTOR_ENCODER_TIMER_CNT_DIR;
    //motor not moving, speed is zero
    if (motorEncoder.currentCount == motorEncoder.previousCount) {
        motorStatus.motorSpeed = 0;
        motorStatus.motorSpeedAverage = calcAverageRPM();
        return;
    }

    //counter is counting up
    if (motorEncoder.counterDirection == 0){
        //no overflow, counter overflow has occurred
        if (motorEncoder.currentCount < motorEncoder.previousCount){
            motorEncoder.countDifference = motorEncoder.currentCount + (MOTOR_ENCODER_TIMER_ARR - motorEncoder.previousCount);
        //calculate difference normally
        } else {
            motorEncoder.countDifference = motorEncoder.currentCount - motorEncoder.previousCount;
        }
    //counter is counting down
    } else {
        //counter overflow has occurred
        if (motorEncoder.currentCount > motorEncoder.previousCount){
            motorEncoder.countDifference = motorEncoder.previousCount + (MOTOR_ENCODER_TIMER_ARR - motorEncoder.currentCount);
        }
        //no overflow, calculate difference normally
        else {
            motorEncoder.countDifference = motorEncoder.previousCount - motorEncoder.currentCount;
        }

    }

    motorStatus.motorSpeed = converttoRPM(motorEncoder.countDifference);
    motorStatus.motorSpeedAverage = calcAverageRPM();
    motorEncoder.previousCount = motorEncoder.currentCount;


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

/************************************************************************************************/
/**
 * Function to calculate average speed of the motor over a number of measurements in a rotating buffer. Used to display
 * an RPM that does not fluctuate as much as direct polling of measurements. Uses the latest motor speed calculation in the
 * status struct to update the buffer and recalculate average.
 * Parameters: none
 * Returns: Average speed of the motor in RPM.
 */
int16_t calcAverageRPM(){
    //add latest measurement to buffer
    static int8_t bufferIndex = 0;
    motorStatus.motorSpeedBuffer[bufferIndex] = motorStatus.motorSpeed;
    bufferIndex++;
    if (bufferIndex > sizeBuffer-1) bufferIndex = 0;

    //calculate sum of speed measurements in buffer
    int16_t sum = 0;
    for (int8_t i = 0; i < sizeBuffer; i++){
        sum += motorStatus.motorSpeedBuffer[i];
    }

    //calculate and return average
    int16_t average;
    average = sum / sizeBuffer;
    return average;
}
/************************************************************************************************/

/************************************************************************************************/
/**
 * Function to query motor direction state variable.
 * Parameters: none
 * Returns: Motor direction state, either forward or reverse.
 */
int16_t queryMotorDirection(){
    return motorStatus.motorDirection;
}
/************************************************************************************************/

/************************************************************************************************/
/**
 * Function to update the motor direction state variable.
 * Parameters: Direction of the motor, either forward or reverse.
 * Returns: none
 */
void updateMotorDirectionState(int16_t direction){
    if (direction == MOTOR_FORWARD || direction == MOTOR_REVERSE){
    motorStatus.motorDirection = direction;
    }
}
/************************************************************************************************/

/************************************************************************************************/
/**
 * Function to query the average motor speed variable.
 * Parameters: none
 * Returns: Speed of the motor in RPM.
 */
int16_t queryAverageMotorSpeed(){
    return motorStatus.motorSpeedAverage;
}
/************************************************************************************************/

/************************************************************************************************/
/**
 * Function to query the motor duty variable.
 * Parameters: none
 * Returns: Duty cycle of the PWM driving the motor.
 */
int16_t queryMotorDuty(){
    return motorStatus.motorDuty;
}
/************************************************************************************************/
