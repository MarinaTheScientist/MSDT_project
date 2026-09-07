all: build/debug.exe

build/debug.exe: build/rect.o build/mystring.o build/barrel.o build/text_wrapper.o build/matrix.o src/lab1.cpp
	g++ -g -o build/debug.exe src/lab1.cpp build/rect.o build/mystring.o build/barrel.o build/text_wrapper.o build/matrix.o

build/rect.o: src/rect.cpp src/rect.hpp
	g++ -g -c -o build/rect.o src/rect.cpp

build/mystring.o: src/mystring.cpp src/mystring.hpp
	g++ -g -c -o build/mystring.o src/mystring.cpp

build/barrel.o: src/barrel.cpp src/barrel.hpp
	g++ -g -c -o build/barrel.o src/barrel.cpp

build/text_wrapper.o: src/text_wrapper.cpp src/text_wrapper.hpp
	g++ -g -c -o build/text_wrapper.o src/text_wrapper.cpp

build/matrix.o: src/matrix.cpp src/matrix.hpp
	g++ -g -c -o build/matrix.o src/matrix.cpp

debug: build/debug.exe
	gdb build/debug.exe

