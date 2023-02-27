/**
 ******************************************************************************
 * @file           : gpio.h
 * @author         : Nicholas Caccamo
 * @brief          : GPIO configuration header
 ******************************************************************************
 */

#ifndef GPIO_H
#define GPIO_H

#include <stm32g431xx.h>
#include <stm32g4xx.h>

/************************************************************************************************/
/*
 * GPIO pin positions in GPIO registers, such as GPIO_IDR and GPIO_ODR
 */
#define GPIO_PIN_0                 ((uint16_t)0x0001)  /* Pin 0 selected    */
#define GPIO_PIN_1                 ((uint16_t)0x0002)  /* Pin 1 selected    */
#define GPIO_PIN_2                 ((uint16_t)0x0004)  /* Pin 2 selected    */
#define GPIO_PIN_3                 ((uint16_t)0x0008)  /* Pin 3 selected    */
#define GPIO_PIN_4                 ((uint16_t)0x0010)  /* Pin 4 selected    */
#define GPIO_PIN_5                 ((uint16_t)0x0020)  /* Pin 5 selected    */
#define GPIO_PIN_6                 ((uint16_t)0x0040)  /* Pin 6 selected    */
#define GPIO_PIN_7                 ((uint16_t)0x0080)  /* Pin 7 selected    */
#define GPIO_PIN_8                 ((uint16_t)0x0100)  /* Pin 8 selected    */
#define GPIO_PIN_9                 ((uint16_t)0x0200)  /* Pin 9 selected    */
#define GPIO_PIN_10                ((uint16_t)0x0400)  /* Pin 10 selected   */
#define GPIO_PIN_11                ((uint16_t)0x0800)  /* Pin 11 selected   */
#define GPIO_PIN_12                ((uint16_t)0x1000)  /* Pin 12 selected   */
#define GPIO_PIN_13                ((uint16_t)0x2000)  /* Pin 13 selected   */
#define GPIO_PIN_14                ((uint16_t)0x4000)  /* Pin 14 selected   */
#define GPIO_PIN_15                ((uint16_t)0x8000)  /* Pin 15 selected   */
/************************************************************************************************/

/************************************************************************************************/
/*
 * Pin Name Defines
 */
//Rotary Encoder
#define ENC_CLK_PORT                GPIOB
#define ENC_CLK_PIN                 GPIO_PIN_13
#define ENC_DT_PORT                 GPIOB
#define ENC_DT_PIN                  GPIO_PIN_14
#define ENC_SW_PORT                 GPIOB
#define ENC_SW_PIN                  GPIO_PIN_15

//Motor
#define MOT_ENC_A_PORT              GPIOA
#define MOT_ENC_A_PIN               GPIO_PIN_11
#define MOT_ENC_B_PORT              GPIOA
#define MOT_ENC_B_PIN               GPIO_PIN_12
#define MOT_DR_IN1_PORT             GPIOC
#define MOT_DR_IN1_PIN              GPIO_PIN_7
#define MOT_DR_IN2_PORT             GPIOA
#define MOT_DR_IN2_PIN              GPIO_PIN_9
#define MOT_DR_PWM_PORT             GPIOB
#define MOT_DR_PWM_PIN              GPIO_PIN_6

//Display
#define DIS_RES_PORT                GPIOA
#define DIS_RES_PIN                 GPIO_PIN_15
#define DIS_CS_PORT                 GPIOC
#define DIS_CS_PIN                  GPIO_PIN_11
#define DIS_SCK_PORT                GPIOC
#define DIS_SCK_PIN                 GPIO_PIN_10
#define DIS_MOSI_PORT               GPIOC
#define DIS_MOSI_PIN                GPIO_PIN_12
#define DIS_DC_PORT                 GPIOD
#define DIS_DC_PIN                  GPIO_PIN_2

//Temperature Sensor
#define TMP_PORT                    GPIOA
#define TMP_PIN                     GPIO_PIN_1


//Debugging LED (onboard)
#define DBG_LED_PORT                GPIOA
#define DBG_LED_PIN                 GPIO_PIN_5

/************************************************************************************************/



typedef enum {
    PIN_HIGH = 1,
    PIN_LOW = 0
}pinstate_t;




//function prototypes
void gpioInit();
int16_t readPin(GPIO_TypeDef *GPIOx, uint16_t GPIO_PIN_x);
void setPin(GPIO_TypeDef *GPIOx, uint16_t GPIO_PIN_x, pinstate_t pinState);
void togglePin(GPIO_TypeDef *GPIOx, uint16_t GPIO_PIN_x);


#endif
