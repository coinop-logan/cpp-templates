CXX = g++
CXXFLAGS = -g -Wall -std=c++17

INC=-I/usr/include -I../common -I./
LIB=-L/usr/local/lib -lsfml-graphics -lsfml-system -lsfml-window


%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $^ -o $@ $(INC)

all: bin/main

bin/main: main.o
	$(CXX) $(CXXFLAGS) -o $@ $^ $(LIB)
