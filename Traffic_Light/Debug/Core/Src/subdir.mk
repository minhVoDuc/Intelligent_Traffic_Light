################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (9-2020-q2-update)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Core/Src/main.c \
../Core/Src/stm32f1xx_hal_msp.c \
../Core/Src/stm32f1xx_it.c \
../Core/Src/syscalls.c \
../Core/Src/sysmem.c \
../Core/Src/system_stm32f1xx.c \
../Core/Src/u_fsm_pedestrian.c \
../Core/Src/u_fsm_traffic.c \
../Core/Src/u_global.c \
../Core/Src/u_i_button.c \
../Core/Src/u_i_buzzer.c \
../Core/Src/u_i_duration.c \
../Core/Src/u_i_led.c \
../Core/Src/u_i_timer.c \
../Core/Src/u_i_uart.c \
../Core/Src/u_test_IO.c 

OBJS += \
./Core/Src/main.o \
./Core/Src/stm32f1xx_hal_msp.o \
./Core/Src/stm32f1xx_it.o \
./Core/Src/syscalls.o \
./Core/Src/sysmem.o \
./Core/Src/system_stm32f1xx.o \
./Core/Src/u_fsm_pedestrian.o \
./Core/Src/u_fsm_traffic.o \
./Core/Src/u_global.o \
./Core/Src/u_i_button.o \
./Core/Src/u_i_buzzer.o \
./Core/Src/u_i_duration.o \
./Core/Src/u_i_led.o \
./Core/Src/u_i_timer.o \
./Core/Src/u_i_uart.o \
./Core/Src/u_test_IO.o 

C_DEPS += \
./Core/Src/main.d \
./Core/Src/stm32f1xx_hal_msp.d \
./Core/Src/stm32f1xx_it.d \
./Core/Src/syscalls.d \
./Core/Src/sysmem.d \
./Core/Src/system_stm32f1xx.d \
./Core/Src/u_fsm_pedestrian.d \
./Core/Src/u_fsm_traffic.d \
./Core/Src/u_global.d \
./Core/Src/u_i_button.d \
./Core/Src/u_i_buzzer.d \
./Core/Src/u_i_duration.d \
./Core/Src/u_i_led.d \
./Core/Src/u_i_timer.d \
./Core/Src/u_i_uart.d \
./Core/Src/u_test_IO.d 


# Each subdirectory must supply rules for building sources it contributes
Core/Src/%.o: ../Core/Src/%.c Core/Src/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m3 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32F103xB -c -I../Core/Inc -I../Drivers/STM32F1xx_HAL_Driver/Inc -I../Drivers/STM32F1xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32F1xx/Include -I../Drivers/CMSIS/Include -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfloat-abi=soft -mthumb -o "$@"

