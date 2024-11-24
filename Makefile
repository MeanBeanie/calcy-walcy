CC = g++
NAME = calc
CXXFLAGS = -std=c++20 -o $(NAME)

all:
	$(CC) *.cpp $(CXXFLAGS)

debug:
	$(CC) *.cpp $(CXXFLAGS) -g
