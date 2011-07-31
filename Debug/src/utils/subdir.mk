################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../src/utils/StringUtils.cpp 

OBJS += \
./src/utils/StringUtils.o 

CPP_DEPS += \
./src/utils/StringUtils.d 


# Each subdirectory must supply rules for building sources it contributes
src/utils/%.o: ../src/utils/%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	g++ -DUNX -DLINUX -DCPPU_ENV=gcc3 -I/home/mordonez/libreoffice3.3_sdk/mordonez-HP-Pavilion-dv6-Notebook-PC/include -I/usr/lib/libreoffice/basis3.3/sdk/include -O0 -g3 -Wall -c -fmessage-length=0 -export-dynamic -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o"$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


