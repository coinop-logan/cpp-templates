CXX = g++
CXXFLAGS = -g -Wall -std=c++0x

INC=-I/usr/include -I/home/oglog/cpp/common -I./
LIB=-lsfml-graphics -lsfml-system -lsfml-window -lGL -lGLU


%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $^ -o $@ $(INC)

all: main

main: main.o
	$(CXX) $(CXXFLAGS) -o lildudes $^ $(LIB)
