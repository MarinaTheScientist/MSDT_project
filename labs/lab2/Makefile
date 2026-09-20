CXX      = g++
CXXFLAGS = -Wall -Wextra -std=c++17 -Isrc

MAIN     = src/lab2.cpp

SRC      = src/mystring.cpp      \
           src/base_file.cpp     \
           src/base32_file.cpp   \
           src/rle_file.cpp      \
           src/base32_file2.cpp  \
           src/rle_file2.cpp

TESTS    = tests/test_base_file    \
           tests/test_base32_file  \
           tests/test_rle_file     \
           tests/test_base32_file2 \
           tests/test_rle_file2

all: lab2

lab2: $(MAIN) $(SRC)
	$(CXX) $(CXXFLAGS) -o $@ $^

test: $(TESTS) tests/data.bin
	@echo "=== запуск тестов ==="
	@for t in $(TESTS); do ./$$t || exit 1; done
	@echo "=== все тесты пройдены ==="

tests/%: tests/%.cpp $(SRC)
	$(CXX) $(CXXFLAGS) -o $@ $^

tests/data.bin: tests/gen_data
	./tests/gen_data

tests/gen_data: tests/gen_data.cpp
	$(CXX) $(CXXFLAGS) -o $@ tests/gen_data.cpp

clean:
	rm -f lab2 lab2.exe $(TESTS) tests/gen_data tests/data.bin tests/tmp_*.bin
	rm -f src/*.exe src/t2*.txt src/t3*.txt src/test.*

.PHONY: all test clean
