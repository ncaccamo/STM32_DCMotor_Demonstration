/**
*******************************************************************************
 * @file           : display.h
 * @author         : Nicholas Caccamo
 * @brief          : Header for display functions and interface with u8g2 library
 ******************************************************************************
 */
#ifndef DISPLAY_H
#define DISPLAY_H

#include <stdint.h>
#include <u8g2.h>





//function prototypes
void displayInit();
uint8_t u8x8_stm32_gpio_and_delay(u8x8_t *u8x8,
    uint8_t msg, uint8_t arg_int,
    void *arg_ptr);
uint8_t u8x8_byte_4wire_hw_spi(u8x8_t *u8x8, uint8_t msg, uint8_t arg_int,
    void *arg_ptr);
void drawDisplay();








#endif
