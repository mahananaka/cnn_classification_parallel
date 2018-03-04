#include <iostream>
#include <vector>

#include "loader.h"

#define MAX_LOAD_TRAINER_IMAGES 50000
#define MAX_LOAD_TEST_IMAGES 10000

std::vector<std::string> trainer_paths { "./data/data_batch_1.bin", 
	"./data/data_batch_2.bin", "./data/data_batch_3.bin", 
	"./data/data_batch_4.bin", "./data/data_batch_5.bin" };
std::vector<std::string> test_paths { "./data/test_batch.bin" };

int main (int argc, char** argv)
{
//Statement to let us know the main started
std::cout << "Running program"<<std::endl;

std::vector<int> trainer_labels, test_labels;
FOURD_VECTOR(int) trainer_images, test_images;

std::cout << "Loading cifar batches:" << std::endl;

load_cifar(trainer_images, trainer_labels, trainer_paths, MAX_LOAD_TRAINER_IMAGES);
//load_cifar(test_images, test_labels, test_paths, MAX_LOAD_TEST_IMAGES);

std::cout << trainer_images.size() << " trainer images and " << test_images.size() << " test image have been loaded" << std::endl;

//std::vector<struct LayerAttribute> myLayers;

//Fully connected layer (flattens and does NN output)
//myLayers.push_back({1,1,'fc'});

//Pool layer2
//myLayers.push_back({1,1,'p'});

//Convlution layer2
//myLayers.push_back({1,1,'c'});

//Pool layer 1
//myLayers.push_back({1,1,'p'});

//Conlution layer 1
//myLayers.push_back({1,1,'c'});


//Create the CNN class to control the CNN
// Input format(mylayers, height,width,#oflabels,train set size, test set size, train set, test test)
//ConvolutionalNeuralNetwork CNN(myLayers, trainer_images[0][0].size(), trainer_images[0][0][0].size(), 10,
//	       	trainer_images.size(),test_images.size(), trainer_images, test_images);


//Clear memory
trainer_images.clear();
test_images.clear();
trainer_labels.clear();
test_labels.clear();

//Statement to let us know we exited without any error
std::cout << "\nExiting program"<<std::endl;
return 0;
}
