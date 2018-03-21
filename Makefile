CC = g++
CXXFLAGS = -w -Wall -g -std=c++11
LIBS = -lpthread -lX11 -fopenmp 

all: clean main

main : main.o loader.o cnn.o convolution_layer.o cnnlayer.o
	$(CC) -o $@ $(CXXFLAGS) main.o loader.o cnn.o convolution_layer.o cnnlayer.o $(LIBS)

omp_main : main.o omp_loader.o
	$(CC) -o $@ $(CXXFLAGS) $(LIBS) main.o omp_loader.o

omp_loader.o: omp_loader.cpp
	$(CC) -c -o $@ $(CXXFLAGS) omp_loader.cpp $(LIBS)


clean:
	rm -f *.o main omp_main
