# STM32_DCMotor_Demonstration

This project is intended to practice and demonstrate embedded software skills on a modern ARM microcontroller.

Main objectives:
1. Start a blank project and configure the microcontroller through registers utilizing basic drivers and headers provided by the manufacturer.
2. Drive a DC motor using PWM. Utilize timers.
3. Control the motor speed using a rotary encoder. Change the motor direction with the encoder's pushbutton. Utilize interrupts.
4. Measure the motor speed using a quadrature encoder on the motor.
5. Show the motor speed on a small display. Utilize third party API to drive the display.


Components:\
- STM32 Nucleo-G431RB development board\
- KY-040 rotary encoder\
- 12V DC Motor with encoder (https://www.amazon.com/gp/product/B07GNFYGYQ/ref=ppx_yo_dt_b_asin_title_o00_s00?ie=UTF8&psc=1) \
- L298N Motor Driver Controller Board and 12V DC power supply\
- SPI OLED Display, 128x64 resolution


Hardware connections:

| Nucleo Board Pin Label | Signal    		| Hardware Interface |
|------------------------|------------------|--------------------|
| PA4                    | SPI1_NSS  		| Display CS         |
| PA5                    | SPI1_SCK  		| Display D0         |
| PA6                    | Output    		| Display DC         |
| PA7                    | SPI1_MOSI 		| Display D1         |
| PC2                    | Input     		| Motor Encoder A    |
| PC3                    | Input     		| Motor Encoder B    |
| PC10                   | Output    		| Motor Driver In1   |
| PC12                   | Output    		| Motor Driver In2   |
| PA11                   | Input (Timer)	| Rotary Encoder CLK |
| PA12                   | Input (Timer)	| Rotary Encoder DT  |
| PB12                   | Input (Interrupt)| Rotary Encoder SW  |


Issues encountered, learnings:\
- GPIO clock has to be enabled before the configuration registers can be written.\
- Clearing GPIOA MODER register disabled the JTAG. Learned that JTAG is using some pins on GPIO Port A so those pin configurations were left at reset value.\
- Writing clock registers required that flash latency was set to 4 wait states according to ST example code and the manual.\
- Printing to console did not work so had to add a write function using CMSIS drivers, found someone else's solution online.\
- Learned that for clearing pending interrupt flags, it makes the most sense to write the bit directly instead of | or & with a mask. In STM32, these registers are cleared by writing a 0 or 1 depending, and so the remaining bits are unaffected anyway. Example: rc_w0 bit is cleared by writing zero so it can be cleared by TIM4->SR = ~TIM_SR_UIF. 


