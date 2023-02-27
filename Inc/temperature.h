/**
*******************************************************************************
 * @file           : temperature.h
 * @author         : Nicholas Caccamo
 * @brief          : Header for temperature sensor functions
 ******************************************************************************
 */
#ifndef TEMPERATURE_H
#define TEMPERATURE_H

#include <stdint.h>

#define TMP_SENSOR_ADC                       ADC1
#define TMP_SENSOR_ADC_RES                   4096       //12-bit
#define TMP_SENSOR_ADC_VREF_MV               3250       //3.25V
#define TMP_SENSOR_MV_TO_C                   10         //10mV per degree C, per TMP36 datasheet
#define TMP_SENSOR_OFFSET                    500        //500mv, per TMP36 datasheet



typedef struct {
    int8_t temperatureCelsius;
}temperature_t;


void measureTemperature(void);
int8_t queryTemperature(void);



#endif
