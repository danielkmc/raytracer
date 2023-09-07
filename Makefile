# set compiler
CC = g++

CFLAGS = -g -Wall -std=c++20

all: main
	$(RM) image.ppm

clean:
	$(RM) *.o
	$(RM) *.gch
	$(RM) image.ppm

main: main.o
	$(CC) $(CFLAGS) -o main main.o

main.o: main.cpp color.hpp vec3.hpp
	$(CC) $(CFLAGS) -c main.cpp