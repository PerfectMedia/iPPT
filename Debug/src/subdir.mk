################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../src/PPTSocket.cpp 

OBJS += \
./src/PPTSocket.o 

CPP_DEPS += \
./src/PPTSocket.d 


# Each subdirectory must supply rules for building sources it contributes
src/%.o: ../src/%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	g++ -DLINUX -DUNX -DCPPU_ENV=gcc3 -I/home/mordonez/libreoffice3.3_sdk/mordonez-HP-Pavilion-dv6-Notebook-PC/include -I/usr/lib/libreoffice/basis3.3/sdk/include -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o"$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


