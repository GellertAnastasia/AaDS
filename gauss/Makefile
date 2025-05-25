CXX = g++
CXXFLAGS = -I/usr/include/eigen3 -Wall -Wextra -std=c++17 -Iinclude 
LDFLAGS = -L/usr/local/lib -lgtest -lgtest_main -lpthread

MAIN = gauss
TEST = gauss_test

$(MAIN): main.o src/method.o
	$(CXX) $(CXXFLAGS) $^ -o $@

$(TEST): test.o src/method.o
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
