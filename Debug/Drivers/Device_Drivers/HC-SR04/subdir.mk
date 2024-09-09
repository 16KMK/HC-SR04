################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (12.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Drivers/Device_Drivers/HC-SR04/HC-SR04.c 

OBJS += \
./Drivers/Device_Drivers/HC-SR04/HC-SR04.o 

C_DEPS += \
./Drivers/Device_Drivers/HC-SR04/HC-SR04.d 


# Each subdirectory must supply rules for building sources it contributes
Drivers/Device_Drivers/HC-SR04/%.o Drivers/Device_Drivers/HC-SR04/%.su Drivers/Device_Drivers/HC-SR04/%.cyclo: ../Drivers/Device_Drivers/HC-SR04/%.c Drivers/Device_Drivers/HC-SR04/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m3 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32F103xB -c -I../Core/Inc -I../Drivers/STM32F1xx_HAL_Driver/Inc/Legacy -I../Drivers/STM32F1xx_HAL_Driver/Inc -I../Drivers/CMSIS/Device/ST/STM32F1xx/Include -I../Drivers/CMSIS/Include -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfloat-abi=soft -mthumb -o "$@"

clean: clean-Drivers-2f-Device_Drivers-2f-HC-2d-SR04

clean-Drivers-2f-Device_Drivers-2f-HC-2d-SR04:
	-$(RM) ./Drivers/Device_Drivers/HC-SR04/HC-SR04.cyclo ./Drivers/Device_Drivers/HC-SR04/HC-SR04.d ./Drivers/Device_Drivers/HC-SR04/HC-SR04.o ./Drivers/Device_Drivers/HC-SR04/HC-SR04.su

.PHONY: clean-Drivers-2f-Device_Drivers-2f-HC-2d-SR04

