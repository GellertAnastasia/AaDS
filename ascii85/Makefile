CXX = g++
CXXFLAGS = -Wall -Wextra -std=c++17 -I.
GTEST_FLAGS = -lgtest -lgtest_main -lpthread

MAIN_TARGET = ascii85
TEST_TARGET = ascii85_test

SRCS = $(wildcard *.cpp)
MAIN_SRC = main.cpp
LIB_SRCS = $(filter-out $(MAIN_SRC), $(SRCS))

LIB_OBJS = $(LIB_SRCS:.cpp=.o)
MAIN_OBJ = $(MAIN_SRC:.cpp=.o)
TEST_OBJS = $(LIB_SRCS:.cpp=.o)

all: $(MAIN_TARGET)

$(MAIN_TARGET): $(MAIN_OBJ) $(LIB_OBJS)
	$(CXX) $(CXXFLAGS) $^ -o $@

$(TEST_TARGET): $(TEST_OBJS)
	$(CXX) $(CXXFLAGS) $^ -o $@ $(GTEST_FLAGS)

%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

test: $(TEST_TARGET)
	./$(TEST_TARGET)

clean:
	rm -f $(MAIN_TARGET) $(TEST_TARGET) *.o

.PHONY: all clean test
