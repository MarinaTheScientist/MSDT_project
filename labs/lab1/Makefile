CXX = g++
CXXFLAGS = -g -Wall -Wextra

OBJS = build/rect.o build/mystring.o build/barrel.o build/text_wrapper.o build/matrix.o

all: build/debug.exe

build/debug.exe: $(OBJS) src/lab1.cpp
	$(CXX) $(CXXFLAGS) -o build/debug.exe src/lab1.cpp $(OBJS)

build/rect.o: src/rect.cpp src/rect.hpp
	$(CXX) $(CXXFLAGS) -c -o build/rect.o src/rect.cpp

build/mystring.o: src/mystring.cpp src/mystring.hpp
	$(CXX) $(CXXFLAGS) -c -o build/mystring.o src/mystring.cpp

build/barrel.o: src/barrel.cpp src/barrel.hpp
	$(CXX) $(CXXFLAGS) -c -o build/barrel.o src/barrel.cpp

build/text_wrapper.o: src/text_wrapper.cpp src/text_wrapper.hpp
	$(CXX) $(CXXFLAGS) -c -o build/text_wrapper.o src/text_wrapper.cpp

build/matrix.o: src/matrix.cpp src/matrix.hpp
	$(CXX) $(CXXFLAGS) -c -o build/matrix.o src/matrix.cpp

debug: build/debug.exe
	gdb build/debug.exe

build/test_rect_basic_methods.out: tests/test_rect_basic_methods.cpp build/rect.o
	$(CXX) $(CXXFLAGS) -o build/test_rect_basic_methods.out tests/test_rect_basic_methods.cpp build/rect.o

build/test_rect_properties.out: tests/test_rect_properties.cpp build/rect.o
	$(CXX) $(CXXFLAGS) -o build/test_rect_properties.out tests/test_rect_properties.cpp build/rect.o

build/test_rect_operations.out: tests/test_rect_operations.cpp build/rect.o
	$(CXX) $(CXXFLAGS) -o build/test_rect_operations.out tests/test_rect_operations.cpp build/rect.o

build/test_bounding_rect.out: tests/test_bounding_rect.cpp build/rect.o
	$(CXX) $(CXXFLAGS) -o build/test_bounding_rect.out tests/test_bounding_rect.cpp build/rect.o

test: build/test_rect_basic_methods.out build/test_rect_properties.out build/test_rect_operations.out build/test_bounding_rect.out
	./build/test_rect_basic_methods.out
	./build/test_rect_properties.out
	./build/test_rect_operations.out
	./build/test_bounding_rect.out

clean:
	rm -rf build/*
build/leaks.out: src/lab1.cpp src/rect.cpp src/mystring.cpp src/barrel.cpp src/text_wrapper.cpp src/matrix.cpp
	$(CXX) -g -fsanitize=address -o build/leaks.out src/lab1.cpp src/rect.cpp src/mystring.cpp src/barrel.cpp src/text_wrapper.cpp src/matrix.cpp

leaks: build/leaks.out
	./build/leaks.out < tests/input.txt
.PHONY: all debug test leaks clean
