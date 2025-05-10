CXX = g++
CXXFLAGS = -Wall -Wextra -std=c++17 -Iinclude
LDFLAGS = -L/usr/local/lib -lgtest -lgtest_main -lpthread

MAIN = ascii85
TEST = ascii85_test

$(MAIN): main.o src/encoder.o src/decoder.o
	$(CXX) $(CXXFLAGS) $^ -o $@

$(TEST): test.o src/encoder.o src/decoder.o
	$(CXX) $(CXXFLAGS) $^ -o $@ $(LDFLAGS)

%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

src/%.o: src/%.cpp include/%.h
	$(CXX) $(CXXFLAGS) -c $< -o $@

all: $(MAIN)

test: $(TEST)
	./$(TEST)

clean:
	rm -f $(MAIN) $(TEST) *.o src/*.o

.PHONY: all clean test
