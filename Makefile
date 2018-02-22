CC = g++
CXXFLAGS = -w -Wall -g -std=c++11
LIBS = -fopenmp 
ICC=icc
ICCFLAGS= -g -ltbb -std=c++11

all: main

main : main.o
	$(CC) -o $@ $(CXXFLAGS) main.o

clean:
	rm -f *.o main
