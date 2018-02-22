#include <chrono>
#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include "cnn_image.h"

#define INPUTFILE "inputs.txt"
#define NUM_IMAGES 10000 //number per batch file
#define IMG_SIZE 3072 //CIFAR-10 block size
#define IMG_WIDTH 32
#define IMG_HEIGHT 32

typedef std::chrono::high_resolution_clock Clock;

int main(int argc, char** argv){
	std::string line;
	std::ifstream ifile;
	ifile.open(INPUTFILE);
	std::vector<std::string> ibatches, tbatches;
	int num_ibatches = 0;

	if(ifile.is_open()){
		if(getline(ifile,line)){
			num_ibatches = atoi(line.c_str());
		}
		for(int i=0;i<num_ibatches;++i){
			getline(ifile,line);
			ibatches.push_back(line);
		}
		while(getline(ifile,line)){
			tbatches.push_back(line);
		}

	}
	ifile.close();


	std::vector<CnnImage*> images;
	for(int i=0;i<num_ibatches;++i){
		ifile.open(ibatches[i].c_str(), std::ios::binary);
		if(ifile.is_open()){
			unsigned char label = 0, temp = 0;
			std::vector<unsigned char> img;
			for(int j=0;j<NUM_IMAGES;++j){
				ifile.read((char *)&label, sizeof(label));
				for(int k=0;k<IMG_SIZE;++k){
					ifile.read((char *)&temp, sizeof(temp));
					img.push_back(temp);
				}

				images.push_back(new CnnImage(label,img.data()));
			}
		}
		ifile.close();
	}

	int count = images.size();
	std::cout << "Finished loading " << count << " images" << std::endl;

	for(int i=0;i<count;++i){
		delete images[i];
	}
}
