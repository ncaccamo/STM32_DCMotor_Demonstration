/**
 ******************************************************************************
 * @file           : encoder.c
 * @author         : Nicholas Caccamo
 * @brief          : Encoder configuration and driver
 ******************************************************************************
 */

#include <encoder.h>
#include <gpio.h>
#include <stm32g431xx.h>

static rotaryEncoderInstance_t rotaryEncoder;


/**
 * State machine for detecting encoder rotation. Updates counter variable.
 * Noisy encoder requires handling the states while the knob is moving and also when it stops.
 * Parameters: none
 * Returns: none
 */
void rotaryEncoderRotation(){
    rotaryEncoder.currentStateCLK = readPin(ENC_CLK_PORT, ENC_CLK_PIN);
    rotaryEncoder.currentStateDT = readPin(ENC_DT_PORT, ENC_DT_PIN);

    //encoder is moving
    if (rotaryEncoder.currentStateCLK != rotaryEncoder.currentStateDT) {
        //CLK changed first; CW
        if (rotaryEncoder.currentStateCLK != rotaryEncoder.lastStateCLK) {
            rotaryEncoder.rotationDirection = 1;
            //else DT changed first; CCW
        } else {

            rotaryEncoder.rotationDirection = -1;
        }
    //both pins are at same state, so encoder has stopped moving
    } else {
        if (rotaryEncoder.currentStateCLK != rotaryEncoder.lastStateCLK) {
            rotaryEncoder.counter += rotaryEncoder.rotationDirection;
        }
        //update last CLK state to be ready to detect next movement
        rotaryEncoder.lastStateCLK = rotaryEncoder.currentStateCLK;
    }


    //keep counter between 0 and 100
    if (rotaryEncoder.counter < 0){
        rotaryEncoder.counter = 0;
    } else if (rotaryEncoder.counter > 100){
        rotaryEncoder.counter = 100;
    }
}
/************************************************************************************************/

/**
 * Function to query the encoder structure for the encoder count.
 * Parameters: none
 * Returns: Encoder counter value.
 */
int32_t queryRotaryEncoderCount(){
    return rotaryEncoder.counter;
}
/************************************************************************************************/

