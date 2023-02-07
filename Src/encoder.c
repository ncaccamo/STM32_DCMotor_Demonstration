/**
 ******************************************************************************
 * @file           : gpio.c
 * @author         : Nicholas Caccamo
 * @brief          : Encoder configuration and driver
 ******************************************************************************
 */

#include <encoder.h>

int8_t lastCount = 0;
volatile int8_t currentCount = 0;



/**encoder function, to be implemented
if (ENCODER_ROTARY_DT_SIGNAL == 0){
	 currentCount--;
}
else {
	currentCount++;
}
lastCount = currentCount;
**/
