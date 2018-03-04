CC = g++
CXXFLAGS = -w -Wall -g -std=c++11
LIBS = -fopenmp 
ICC=icc
ICCFLAGS= -g -ltbb -std=c++11

all: main omp_main

main : main.o loader.o
	$(CC) -o $@ $(CXXFLAGS) main.o loader.o

omp_main : main.o omp_loader.o
	$(CC) -o $@ $(CXXFLAGS) $(LIBS) main.o omp_loader.o

omp_loader.o: omp_loader.cpp
	$(CC) -c -o $@ $(CXXFLAGS) omp_loader.cpp $(LIBS)


clean:
	rm -f *.o main omp_main
