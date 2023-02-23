# STM32_DCMotor_Demonstration

This project is intended to practice and demonstrate embedded software skills on a modern ARM microcontroller.

Main objectives:
1. Start a blank project and configure the microcontroller through registers utilizing basic drivers and headers provided by the manufacturer.
2. Drive a DC motor using PWM.
3. Control the motor speed using a rotary encoder. Change the motor direction with the encoder's pushbutton. 
4. Measure the motor speed using a quadrature encoder on the motor.
5. Measure the motor's temperature with a temperature sensor.
6. Show the motor speed and temperature on a small display. Utilize third party API to drive the display.


Components:
- STM32 Nucleo-G431RB development board
- KY-040 rotary encoder
- 12V DC Motor with encoder (https://www.amazon.com/gp/product/B07GNFYGYQ/ref=ppx_yo_dt_b_asin_title_o00_s00?ie=UTF8&psc=1)
- L298N Motor Driver Controller Board and 12V DC power supply
- SPI OLED Display, 128x64 resolution


Hardware connections:

| Nucleo Board Pin Label | Signal    		| Hardware Interface |
|------------------------|------------------|--------------------|
| PC10                   | SPI3_SCK 	 	| Display D0         |
| PC11                   | Output  		    | Display CS         |
| PC12                   | SPI3_MOSI  		| Display D1         |
| PD2                    | Output    		| Display DC         |
| PA15                   | Output        	| Display RES        |
| PA11                   | Timer Input  	| Motor Encoder A    |
| PA12                   | Timer Input  	| Motor Encoder B    |
| PC7                    | Output    		| Motor Driver In1   |
| PA9                    | Output    		| Motor Driver In2   |
| PB6                    | Timer Output 	| Motor Driver PWM   |
| PB13                   | Input        	| Rotary Encoder CLK |
| PB14                   | Input            | Rotary Encoder DT  |
| PB15                   | Input (Interrupt)| Rotary Encoder SW  |
| PA0                    | ADC Input		| Temp Sensor Output |


Issues encountered, learnings, notes:
- GPIO clock has to be enabled before the configuration registers can be written.
- Clearing GPIOA MODER register disabled the JTAG. Learned that JTAG is using some pins on GPIO Port A so those pin configurations were left at reset value.
- Writing clock registers required that flash latency was set to 4 wait states according to ST example code and the manual.
- Printing to console did not work so had to add a write function using CMSIS drivers, found someone else's solution online.
- Learned that for clearing pending interrupt flags, it makes the most sense to write the bit directly instead of | or & with a mask. In STM32, these registers are cleared by writing a 0 or 1 depending, and so the remaining bits are unaffected anyway. Example: rc_w0 bit is cleared by writing zero so it can be cleared by TIM4->SR = ~TIM_SR_UIF.
- The rotary encoder seems noisy so I researched some encoder examples online and adapted a state machine that accounts for when the encoder moves and stops. This will replace using a timer in encoder mode.
- For reference, to calculate the update frequency of a timer: TIM_CLK / (PSC + 1) / (ARR + 1) / (RSR + 1), the terms being prescaler (PSC), auto-reload register (ARR), and repetition counter (RCR). The result is in hertz and must be converted to seconds (1/hz).
- For reference, the frequency of PWM is calculated by TIM_CLK / (PSC + 1) / (ARR + 1), because it is based on a timer. The result is in hertz. Duty cycle is calculated by CCRx/ARRx, where CCRx is the reload value of the capture/compare register. 
- The initial timer interrupt frequency of 200ms (5hz) was much too slow, and there were many errors in detecting the encoder movement, such as missed pulses and failure to switch the direction flag. Polling at 30hz is working better.
- I found the SPI hardware NSS (chip select) automatic control to be confusing and decided to use a GPIO as CS and manually change its state for data transfer.
- The screen drawing function seems to take too long to be safely put in an ISR directly - infinite loop occurs. Setting a flag in the ISR to update the screen in the main loop seems to be stable.



