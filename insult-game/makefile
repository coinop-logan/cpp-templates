CXX = g++
CXXFLAGS = -g -Wall -std=c++17

INC=-I/usr/include -I../common -I./
LIB=-L/usr/local/lib 

all: pre-build main-build

main-build: bin/main

clean:
	rm -f cpp/obj/*
	rm -rf bin/*
	rm -rf dist/*

pre-build:
	mkdir -p cpp/obj
	mkdir -p bin/
	mkdir -p dist/

cpp/obj/%.o: cpp/src/%.cpp
	$(CXX) $(CXXFLAGS) -c $^ -o $@ $(INC)

bin/main: cpp/obj/main.o
	$(CXX) $(CXXFLAGS) -o $@ $^ $(LIB)
