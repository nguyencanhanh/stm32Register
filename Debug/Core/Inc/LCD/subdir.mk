################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (10.3-2021.10)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Core/Inc/LCD/LiquidCrystal_I2C.c 

OBJS += \
./Core/Inc/LCD/LiquidCrystal_I2C.o 

C_DEPS += \
./Core/Inc/LCD/LiquidCrystal_I2C.d 


# Each subdirectory must supply rules for building sources it contributes
Core/Inc/LCD/%.o Core/Inc/LCD/%.su Core/Inc/LCD/%.cyclo: ../Core/Inc/LCD/%.c Core/Inc/LCD/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m3 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32F103xB -c -I../Core/Inc -I../Middlewares/Third_Party/FreeRTOS/Source/CMSIS_RTOS -I../Middlewares/Third_Party/FreeRTOS/Source/include -I../Middlewares/Third_Party/FreeRTOS/Source/portable/GCC/ARM_CM3 -I../Core/Inc/TIM -I../Core/Inc/DMA -I../Core/Inc/ADC -I../Core/Inc/LCD -I../Core/Inc/I2C -I../Core/Inc/GPIO -I../Core/Inc/UART -I../Drivers/STM32F1xx_HAL_Driver/Inc/Legacy -I../Drivers/STM32F1xx_HAL_Driver/Inc -I../Drivers/CMSIS/Device/ST/STM32F1xx/Include -I../Drivers/CMSIS/Include -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfloat-abi=soft -mthumb -o "$@"

clean: clean-Core-2f-Inc-2f-LCD

clean-Core-2f-Inc-2f-LCD:
	-$(RM) ./Core/Inc/LCD/LiquidCrystal_I2C.cyclo ./Core/Inc/LCD/LiquidCrystal_I2C.d ./Core/Inc/LCD/LiquidCrystal_I2C.o ./Core/Inc/LCD/LiquidCrystal_I2C.su

.PHONY: clean-Core-2f-Inc-2f-LCD

