/**
 ******************************************************************************
 * @file           : gpio.c
 * @author         : Nicholas Caccamo
 * @brief          : Encoder configuration and driver
 ******************************************************************************
 */

#include <encoder.h>
#include <gpio.h>
#include <stm32g431xx.h>

static int16_t lastStateCLK = 0;
int8_t currentStateCLK = 0;
int8_t currentStateDT = 0;
static int32_t counter = 0;
int8_t rotationDirection = 0;


/**
 * State machine for detecting encoder rotation.
 * Noisy encoder requires handling the states while the knob is moving and also when it stops.
 *
 */
int32_t rotaryEncoderRotation()
{

currentStateCLK = readPin(ENC_CLK_PORT, ENC_CLK_PIN);
currentStateDT = readPin(ENC_DT_PORT, ENC_DT_PIN);

  if (currentStateCLK != currentStateDT) { 			//encoder is moving
    if (currentStateCLK != lastStateCLK) { 			//CLK changed first; CW
    	rotationDirection = 1;
    }
     else {											//else DT changed first; CCW
    	rotationDirection = -1;
    }
  }
    else { 							    		    //both pins are at same state, so encoder has stopped moving
       if (currentStateCLK != lastStateCLK) {
          counter += rotationDirection;
       }
       lastStateCLK = currentStateCLK;			    //update last CLK state to be ready to detect next movement
    }



  if (counter < 0) 								    //keep counter between 0 and 100
    counter = 0;
  else if (counter > 100)
   counter = 100;

 return counter;
}
