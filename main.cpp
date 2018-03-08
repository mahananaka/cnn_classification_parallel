#include <chrono>
#include <iostream>
#include <vector>
#include "loader.h"

#define MAX_LOAD_TRAINER_IMAGES 10000
#define MAX_LOAD_TEST_IMAGES 10000

typedef std::chrono::high_resolution_clock Clock;

std::vector<std::string> trainer_paths { "./data/data_batch_1.bin" };
std::vector<std::string> trainer_paths2 { "./data/data_batch_1a.bin","./data/data_batch_1b.bin",
	"./data/data_batch_1c.bin","./data/data_batch_1d.bin","./data/data_batch_1e.bin","./data/data_batch_1f.bin",
	"./data/data_batch_1g.bin","./data/data_batch_1h.bin","./data/data_batch_1i.bin","./data/data_batch_1j.bin"};
std::vector<std::string> test_paths { "./data/test_batch.bin" };

int main (int argc, char** argv)
{
//Statement to let us know the main started
std::cout << "Running program"<<std::endl;

std::vector<int> trainer_labels, trainer_labels2, test_labels;
FOURD_VECTOR(int) trainer_images, trainer_images2, test_images;

std::cout << "Loading cifar batches:" << std::endl;

auto t1 = Clock::now();
load_cifar(trainer_images, trainer_labels, trainer_paths, 10000, MAX_LOAD_TRAINER_IMAGES);
//load_cifar(test_images, test_labels, test_paths, MAX_LOAD_TEST_IMAGES);
auto t2 = Clock::now();

auto t = std::chrono::duration_cast<std::chrono::milliseconds>(t2-t1).count();
std::cout << "Loaded into 4d vector in " << t << " ms" << std::endl;

load_cifar(trainer_images2, trainer_labels2, trainer_paths2, 1000, MAX_LOAD_TRAINER_IMAGES);
for(int i=0;i<10000;++i){
	for(int j=0;j<3;++j){
		for(int k=0;k<32;++k){
			for(int l=0;l<32;++l){
				if(trainer_images[i][j][k][l] == trainer_images2[i][j][k][l]){
					//do nothing
				}else{
					std::cout << "problem @ ["<<i<<"]["<<j<<"]["<<k<<"]["<<l<<"]"<<std::endl;
					std::cout <<  trainer_images[i][j][k][l] <<","<< trainer_images[i][j][k][l+1] 
							<<","<< trainer_images[i][j][k][l+2] <<","<< trainer_images[i][j][k][l+3]
							<<","<< trainer_images[i][j][k][l+4] <<","<< trainer_images[i][j][k][l+5]
							<<","<< trainer_images[i][j][k][l+6] <<","<< trainer_images[i][j][k][l+7]
							<<","<< trainer_images[i][j][k][l+8] <<","<< trainer_images[i][j][k][l+9];
					std::cout <<" : "<< trainer_images2[i][j][k][l] <<","<< trainer_images2[i][j][k][l+1] 
							<<","<< trainer_images2[i][j][k][l+2] <<","<< trainer_images2[i][j][k][l+3]
							<<","<< trainer_images2[i][j][k][l+4] <<","<< trainer_images2[i][j][k][l+5]
							<<","<< trainer_images2[i][j][k][l+6] <<","<< trainer_images2[i][j][k][l+7]
							<<","<< trainer_images2[i][j][k][l+8] <<","<< trainer_images2[i][j][k][l+9]
							<< std::endl;
							i++;
					std::cout <<  trainer_images[i][j][k][l] <<","<< trainer_images[i][j][k][l+1] 
							<<","<< trainer_images[i][j][k][l+2] <<","<< trainer_images[i][j][k][l+3]
							<<","<< trainer_images[i][j][k][l+4] <<","<< trainer_images[i][j][k][l+5]
							<<","<< trainer_images[i][j][k][l+6] <<","<< trainer_images[i][j][k][l+7]
							<<","<< trainer_images[i][j][k][l+8] <<","<< trainer_images[i][j][k][l+9];
					std::cout <<" : "<< trainer_images2[i][j][k][l] <<","<< trainer_images2[i][j][k][l+1] 
							<<","<< trainer_images2[i][j][k][l+2] <<","<< trainer_images2[i][j][k][l+3]
							<<","<< trainer_images2[i][j][k][l+4] <<","<< trainer_images2[i][j][k][l+5]
							<<","<< trainer_images2[i][j][k][l+6] <<","<< trainer_images2[i][j][k][l+7]
							<<","<< trainer_images2[i][j][k][l+8] <<","<< trainer_images2[i][j][k][l+9]
							<< std::endl;
							i++;
					std::cout <<  trainer_images[i][j][k][l] <<","<< trainer_images[i][j][k][l+1] 
							<<","<< trainer_images[i][j][k][l+2] <<","<< trainer_images[i][j][k][l+3]
							<<","<< trainer_images[i][j][k][l+4] <<","<< trainer_images[i][j][k][l+5]
							<<","<< trainer_images[i][j][k][l+6] <<","<< trainer_images[i][j][k][l+7]
							<<","<< trainer_images[i][j][k][l+8] <<","<< trainer_images[i][j][k][l+9];
					std::cout <<" : "<< trainer_images2[i][j][k][l] <<","<< trainer_images2[i][j][k][l+1] 
							<<","<< trainer_images2[i][j][k][l+2] <<","<< trainer_images2[i][j][k][l+3]
							<<","<< trainer_images2[i][j][k][l+4] <<","<< trainer_images2[i][j][k][l+5]
							<<","<< trainer_images2[i][j][k][l+6] <<","<< trainer_images2[i][j][k][l+7]
							<<","<< trainer_images2[i][j][k][l+8] <<","<< trainer_images2[i][j][k][l+9]
							<< std::endl;
					exit(-1);
				}
			}
		}
	}
}

std::cout << trainer_images.size() << " trainer images and " << test_images.size() << " test image have been loaded" << std::endl;

std::cout << trainer_images2.size() << " trainer2 images and " << test_images.size() << " test image have been loaded" << std::endl;
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
