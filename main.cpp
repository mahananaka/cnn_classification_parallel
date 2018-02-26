#include <chrono>
#include <iostream>
#include "loader.h"
#include "cnn_image.h"

#define INPUTFILE "inputs.txt"
#define NUM_IMAGES 10000 //number per batch file
#define IMG_SIZE 3072 //CIFAR-10 block size

typedef std::chrono::high_resolution_clock Clock;

int main(int argc, char** argv){
	std::vector<CnnImage*> images;

	load_cifar(images,INPUTFILE,IMG_SIZE,NUM_IMAGES);

	int count = images.size();
	std::cout << "Finished loading " << count << " images" << std::endl;

	for(int i=0;i<count;++i){
		delete images[i];
	}
}
