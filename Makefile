CC = g++
CXXFLAGS = -w -Wall -g -std=c++11
LIBS = -lpthread -lX11 -fopenmp
OBJECTS = loader.o convolution_layer.o cnnlayer.o pool_layer.o fully_connected_layer.o cnn.o

all: main

main : main.o $(OBJECTS)
	$(CC) -o $@ main.o $(CXXFLAGS) $(OBJECTS) $(LIBS)

omp_main : main.o omp_loader.o
	$(CC) -o $@ $(CXXFLAGS) $(LIBS) main.o omp_loader.o

omp_loader.o: omp_loader.cpp
	$(CC) -c -o $@ $(CXXFLAGS) omp_loader.cpp $(LIBS)


clean:
	rm -f *.o main omp_main
