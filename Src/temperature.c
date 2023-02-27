/**
*******************************************************************************
 * @file           : temperature.c
 * @author         : Nicholas Caccamo
 * @brief          : Temperature sensor functions
 ******************************************************************************
 */
#include <temperature.h>
#include <stm32g431xx.h>


static temperature_t temperatureSensor;



/************************************************************************************************/
/**
 * Function to initiate the ADC measurement, retrieve the value, and convert to degrees Celsius. Updates temperature variable
 * in the temperature sensor's data structure.
 * Parameters: none
 * Returns: none
 */
void measureTemperature(void){
    volatile uint32_t adcRawMeasurement;
    float adcMvMeasurement;

    //start conversion
    TMP_SENSOR_ADC->CR |= (0x01 << ADC_CR_ADSTART_Pos);
    //wait until conversion complete
    while(!(TMP_SENSOR_ADC->ISR & ADC_ISR_EOC));
    //read measurement values from register
    adcRawMeasurement = TMP_SENSOR_ADC->DR;
    //scale raw measurement to mV
    adcMvMeasurement = (adcRawMeasurement * ((float)TMP_SENSOR_ADC_VREF_MV / (float)TMP_SENSOR_ADC_RES));
    //convert mV to degrees C
    temperatureSensor.temperatureCelsius = (adcMvMeasurement - TMP_SENSOR_OFFSET) / TMP_SENSOR_MV_TO_C;

}
/************************************************************************************************/



/************************************************************************************************/
/**
 * Function to return the temperature variable in the temperature sensor's data structure.
 * Parameters: none
 * Returns: none
 */
int8_t queryTemperature(void){
    return temperatureSensor.temperatureCelsius;
}
/************************************************************************************************/
