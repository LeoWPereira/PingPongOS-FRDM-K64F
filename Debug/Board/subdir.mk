################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Board/board.c \
../Board/gpio_pins.c \
../Board/hardware_init.c \
../Board/pin_mux.c 

OBJS += \
./Board/board.o \
./Board/gpio_pins.o \
./Board/hardware_init.o \
./Board/pin_mux.o 

C_DEPS += \
./Board/board.d \
./Board/gpio_pins.d \
./Board/hardware_init.d \
./Board/pin_mux.d 


# Each subdirectory must supply rules for building sources it contributes
Board/%.o: ../Board/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: Cross ARM C Compiler'
	arm-none-eabi-gcc -mcpu=cortex-m4 -mthumb -mfloat-abi=hard -mfpu=fpv4-sp-d16 -O0 -fmessage-length=0 -fsigned-char -ffunction-sections -fdata-sections -Wall  -g3 -DDEBUG -D"CPU_MK64FN1M0VMD12" -I"../Sources" -I"C:\Users\Leonardo\workspace.kds\PingPongOS\include" -I"C:\Users\Leonardo\workspace.kds\PingPongOS" -I"C:\Freescale\KSDK_1.3.0\platform\osa\inc" -I"C:\Freescale\KSDK_1.3.0\platform\hal\inc" -I"C:\Freescale\KSDK_1.3.0\platform\system\inc" -I"C:\Freescale\KSDK_1.3.0\platform\drivers\inc" -I"C:\Users\Leonardo\workspace.kds\PingPongOS\Board" -I"C:\Users\Leonardo\workspace.kds\PingPongOS\Utilities" -I"../Project_Settings/Startup_Code" -I"../SDK/platform/CMSIS/Include" -I"../SDK/platform/devices" -I"../SDK/platform/devices/MK64F12/include" -I"C:\Freescale\KSDK_1.3.0/platform/utilities/inc" -I"C:\Freescale\KSDK_1.3.0/platform/utilities/src" -include"C:\Users\Leonardo\workspace.kds\PingPongOS\config\config.h" -std=c99 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -c -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


