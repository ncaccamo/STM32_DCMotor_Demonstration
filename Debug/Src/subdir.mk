################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (10.3-2021.10)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Src/clockconfig.c \
../Src/encoder.c \
../Src/gpio.c \
../Src/interrupt.c \
../Src/main.c \
../Src/syscalls.c \
../Src/sysmem.c \
../Src/system_stm32g4xx.c \
../Src/timer.c 

OBJS += \
./Src/clockconfig.o \
./Src/encoder.o \
./Src/gpio.o \
./Src/interrupt.o \
./Src/main.o \
./Src/syscalls.o \
./Src/sysmem.o \
./Src/system_stm32g4xx.o \
./Src/timer.o 

C_DEPS += \
./Src/clockconfig.d \
./Src/encoder.d \
./Src/gpio.d \
./Src/interrupt.d \
./Src/main.d \
./Src/syscalls.d \
./Src/sysmem.d \
./Src/system_stm32g4xx.d \
./Src/timer.d 


# Each subdirectory must supply rules for building sources it contributes
Src/%.o Src/%.su: ../Src/%.c Src/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DDEBUG -DSTM32 -DSTM32G4 -DNUCLEO_G431RB -DSTM32G431RBTx -DSTM32G431xx -c -I"C:/Users/Nicholas/STM32CubeIDE/workspace_1.11.2/STM32_DCMotor_Encoder_Display/Drivers/CMSIS/Device/ST/STM32G4xx/Include" -I"C:/Users/Nicholas/STM32CubeIDE/workspace_1.11.2/STM32_DCMotor_Encoder_Display/Drivers/CMSIS/Include" -I../Inc -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"

clean: clean-Src

clean-Src:
	-$(RM) ./Src/clockconfig.d ./Src/clockconfig.o ./Src/clockconfig.su ./Src/encoder.d ./Src/encoder.o ./Src/encoder.su ./Src/gpio.d ./Src/gpio.o ./Src/gpio.su ./Src/interrupt.d ./Src/interrupt.o ./Src/interrupt.su ./Src/main.d ./Src/main.o ./Src/main.su ./Src/syscalls.d ./Src/syscalls.o ./Src/syscalls.su ./Src/sysmem.d ./Src/sysmem.o ./Src/sysmem.su ./Src/system_stm32g4xx.d ./Src/system_stm32g4xx.o ./Src/system_stm32g4xx.su ./Src/timer.d ./Src/timer.o ./Src/timer.su

.PHONY: clean-Src

