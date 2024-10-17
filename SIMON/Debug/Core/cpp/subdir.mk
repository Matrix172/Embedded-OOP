################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (12.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../Core/cpp/maincpp.cpp 

OBJS += \
./Core/cpp/maincpp.o 

CPP_DEPS += \
./Core/cpp/maincpp.d 


# Each subdirectory must supply rules for building sources it contributes
Core/cpp/%.o Core/cpp/%.su Core/cpp/%.cyclo: ../Core/cpp/%.cpp Core/cpp/subdir.mk
	arm-none-eabi-g++ "$<" -mcpu=cortex-m3 -std=gnu++14 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32L152xE -c -I../Core/Inc -I../Drivers/STM32L1xx_HAL_Driver/Inc -I../Drivers/STM32L1xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32L1xx/Include -I../Drivers/CMSIS/Include -I"C:/Users/mdejeante/STM32CubeIDE/workspace_1.16.0/Embedded-OOP/SIMON/Core/cpp" -I"C:/Users/mdejeante/STM32CubeIDE/workspace_1.16.0/Embedded-OOP/SIMON/Drivers/display" -I"C:/Users/mdejeante/STM32CubeIDE/workspace_1.16.0/Embedded-OOP/SIMON/Drivers" -O0 -ffunction-sections -fdata-sections -fno-exceptions -fno-rtti -fno-use-cxa-atexit -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfloat-abi=soft -mthumb -o "$@"

clean: clean-Core-2f-cpp

clean-Core-2f-cpp:
	-$(RM) ./Core/cpp/maincpp.cyclo ./Core/cpp/maincpp.d ./Core/cpp/maincpp.o ./Core/cpp/maincpp.su

.PHONY: clean-Core-2f-cpp

