################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../src/EvoSim.cpp \
../src/genome.cpp \
../src/population.cpp \
../src/random.cpp 

OBJS += \
./src/EvoSim.o \
./src/genome.o \
./src/population.o \
./src/random.o 

CPP_DEPS += \
./src/EvoSim.d \
./src/genome.d \
./src/population.d \
./src/random.d 


# Each subdirectory must supply rules for building sources it contributes
src/%.o: ../src/%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	g++ -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


