################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../src/Card.cpp \
../src/CardDeck.cpp \
../src/CompPlayer.cpp \
../src/HumanPlayer.cpp \
../src/Player.cpp \
../src/PlayerCards.cpp \
../src/PokerHand.cpp \
../src/SokoGame.cpp \
../src/sokopoker.cpp 

OBJS += \
./src/Card.o \
./src/CardDeck.o \
./src/CompPlayer.o \
./src/HumanPlayer.o \
./src/Player.o \
./src/PlayerCards.o \
./src/PokerHand.o \
./src/SokoGame.o \
./src/sokopoker.o 

CPP_DEPS += \
./src/Card.d \
./src/CardDeck.d \
./src/CompPlayer.d \
./src/HumanPlayer.d \
./src/Player.d \
./src/PlayerCards.d \
./src/PokerHand.d \
./src/SokoGame.d \
./src/sokopoker.d 


# Each subdirectory must supply rules for building sources it contributes
src/%.o: ../src/%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	g++ -O0 -g3 -Wall -c -fmessage-length=0 -std=c++11 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


