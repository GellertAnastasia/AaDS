CXX = g++
CXXFLAGS = -Wall -Wextra -std=c++17 -Iinclude
GTEST_FLAGS = -lgtest -lgtest_main -lpthread

# Имена программ
MAIN = ascii85
TEST = ascii85_test

# Основная программа
$(MAIN): main.o src/encoder.o src/decoder.o
	$(CXX) $(CXXFLAGS) $^ -o $@

# Тесты
$(TEST): test.o src/encoder.o src/decoder.o
	$(CXX) $(CXXFLAGS) $^ -o $@ $(GTEST_FLAGS)

# Правило для всех .o файлов
%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

src/%.o: src/%.cpp include/%.h
	$(CXX) $(CXXFLAGS) -c $< -o $@

# Цели по умолчанию
all: $(MAIN)

test: $(TEST)
	./$(TEST)

clean:
	rm -f $(MAIN) $(TEST) *.o src/*.o

.PHONY: all clean test
