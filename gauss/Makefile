CXX = g++
CXXFLAGS = -I/usr/include/eigen3 -Wall -Wextra -std=c++17 -Iinclude -O3 -march=native -ffast-math -fopt-info-vec-optimized
LDFLAGS = -L/usr/local/lib -lgtest -lgtest_main -lpthread

MAIN = gauss
TEST = gauss_test

$(MAIN): main.o src/rwCSV.o src/method.o
	$(CXX) $(CXXFLAGS) $^ -o $@

$(TEST): test.o src/rwCSV.o src/method.o
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
	rm -f solution.csv

.PHONY: all clean test
