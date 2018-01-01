TARGET_EXEC := sokoTest

BUILD_DIR ?= .
SRCS := ../src/Card.cpp ../src/CardDeck.cpp ../src/Player.cpp ../src/PlayerCards.cpp \
		../src/CompPlayer.cpp ../src/HumanPlayer.cpp ../src/PokerHand.cpp \
		CardTest.cpp CardDeckTest.cpp PlayerCardsTest.cpp PlayerTest.cpp HumanPlayerTest.cpp \
		CompPlayerTest.cpp PokerHandTest.cpp sokoTest.cpp

OBJS := $(addsuffix .o,$(basename $(SRCS)))

INC_FLAGS := -I../src -I.

CPPFLAGS ?= $(INC_FLAGS) -MMD -MP
CXXFLAGS := -Wall -std=c++11

$(BUILD_DIR)/$(TARGET_EXEC): $(OBJS)
	$(CXX) $(OBJS) -o $@ $(LDFLAGS)

# c++ source
$(BUILD_DIR)/%.o: %.cpp
	$(CXX) $(CPPFLAGS) $(CXXFLAGS) -c $< -o $@

.PHONY: clean

clean:
	$(RM) *.o

