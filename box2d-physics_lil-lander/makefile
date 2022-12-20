CXX = g++
CXXFLAGS = -g -Wall -std=c++0x

INC=-I/usr/include -I../common -I./
LIB=-lsfml-graphics -lsfml-system -lsfml-window -lGL -lGLU -Llib/ -lbox2d

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

bin/main: cpp/obj/main.o cpp/obj/graphics.o cpp/obj/input.o cpp/obj/myvectors.o cpp/obj/common.o cpp/obj/ship.o
	$(CXX) $(CXXFLAGS) -o $@ $^ $(LIB)
