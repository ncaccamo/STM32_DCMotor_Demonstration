/**
 ******************************************************************************
 * @file           : display.c
 * @author         : Nicholas Caccamo
 * @brief          : Display functions and interface with u8g2 library
 ******************************************************************************
 */
#include <stdint.h>
#include <stdio.h>
#include <display.h>
#include <gpio.h>
#include <timer.h>
#include <motor.h>
#include <temperature.h>
#include <u8g2.h>
#include <spi.h>

u8g2_t u8g2; // a structure which will contain all the data for one display

/************************************************************************************************/
/**
 * Function to initialize the display using the u8g2 library.
 * Parameters: none
 * Returns: none
 */
void displayInit(){
    //make sure RES is held high during normal operation
    setPin(DIS_RES_PORT, DIS_RES_PIN, PIN_HIGH);
    delayMs(10);

    u8g2_Setup_ssd1306_128x64_noname_f(&u8g2, U8G2_R0, u8x8_byte_4wire_hw_spi, u8x8_stm32_gpio_and_delay);  // init u8g2 structure
    u8g2_InitDisplay(&u8g2); // send init sequence to the display, display is in sleep mode after this,
    u8g2_SetPowerSave(&u8g2, 0); // wake up display
}
/************************************************************************************************/

/************************************************************************************************/
/**
 * Function to identify the GPIO and delay functions that are needed by the u8g2 library.
 * Parameters: none
 * Returns: Confirmation status
 */
uint8_t u8x8_stm32_gpio_and_delay(u8x8_t *u8x8,
    uint8_t msg, uint8_t arg_int,
    void *arg_ptr)
{
  switch (msg)
  {
  case U8X8_MSG_GPIO_AND_DELAY_INIT:
    delayMs(1);
    break;
  case U8X8_MSG_DELAY_10MICRO:      // delay arg_int * 10 micro seconds
    delayMs(1);
    break;
  case U8X8_MSG_DELAY_MILLI:
    delayMs(arg_int);
    break;
  case U8X8_MSG_GPIO_DC:
    setPin(DIS_DC_PORT, DIS_DC_PIN, arg_int);
    break;
  case U8X8_MSG_GPIO_RESET:
    setPin(DIS_RES_PORT, DIS_RES_PIN, arg_int);
    break;
  }
  return 1;
}
/************************************************************************************************/

/************************************************************************************************/
/**
 * Function to identify the SPI functions that will be used by the u8g2 library.
 * Parameters: none
 * Returns: Confirmation status
 */
uint8_t u8x8_byte_4wire_hw_spi(u8x8_t *u8x8, uint8_t msg, uint8_t arg_int,
    void *arg_ptr)
{
uint8_t *data;
  switch (msg)
  {
  case U8X8_MSG_BYTE_SEND:
      data = (uint8_t *)arg_ptr;
      while(arg_int > 0) {
          transferSPIByte((uint8_t)*data);
          data++;
          arg_int--;
      }
      break;
  case U8X8_MSG_BYTE_INIT:
    break;
  case U8X8_MSG_BYTE_SET_DC:
    setPin(DIS_DC_PORT, DIS_DC_PIN, arg_int);
    break;
  case U8X8_MSG_BYTE_START_TRANSFER:
    startTransferSPI();
    break;
  case U8X8_MSG_BYTE_END_TRANSFER:
    endTransferSPI();
    break;
  default:
    return 0;
  }
  return 1;
}
/************************************************************************************************/


/************************************************************************************************/
/**
 * Function that uses the u8g2 library to draw on the display. Motor status data is queried and
 * then updated on the display. This function is intended to be called periodically to keep the data
 * shown on the screen up to date.
 * Parameters: none
 * Returns: none
 */
void drawDisplay(){
    int16_t speed = queryAverageMotorSpeed();
    int8_t speedString[4];
    sprintf((char *)speedString, "%d", speed);

    int16_t duty = queryMotorDuty();
    int8_t dutyString[4];
    sprintf((char *)dutyString, "%d", duty);

    int16_t direction = queryMotorDirection();
    int8_t directionString[4];
    if (direction == MOTOR_FORWARD){
        sprintf((char *)directionString, "%s", "CW");
    } else {
        sprintf((char *)directionString, "%s", "CCW");
    }

    //int16_t temperature = queryMotorTemperature();
    //int8_t temperatureString[4];
    //sprintf((char *)temperatureString, "%d", temperature);

    u8g2_ClearBuffer(&u8g2);
    u8g2_DrawFrame(&u8g2, 0, 0, 128, 64);
    u8g2_SetFont(&u8g2, u8g2_font_7x13_tf);             //7 width, 13 height characters
    u8g2_DrawStr(&u8g2, 3, 14, (char *)speedString);
    u8g2_DrawStr(&u8g2, 30, 14, "RPM");
    u8g2_DrawStr(&u8g2, 3, 28, "Duty: ");
    u8g2_DrawStr(&u8g2, 45, 28, (char *)dutyString);
    u8g2_DrawGlyph(&u8g2, 66, 28, 37);
    u8g2_DrawStr(&u8g2, 3, 42, "Direction: ");
    u8g2_DrawStr(&u8g2, 79, 42, (char *)directionString);
    u8g2_DrawStr(&u8g2, 3, 56, "Temperature: ");
    //u8g2_DrawStr(&u8g2, 87, 56, (char *)temperatureString);
    u8g2_DrawGlyph(&u8g2, 108, 56, 176);
    u8g2_DrawStr(&u8g2, 115, 56, "C");
    u8g2_SendBuffer(&u8g2);
}
/************************************************************************************************/
