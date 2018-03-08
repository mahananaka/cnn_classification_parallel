#include <fstream>
#include <iostream>
#include "CImg.h"

#define NUM_BYTES_PER_IMAGE 3072
#define NUM_IMAGES_PER_BATCH 10000

void  load_cifar(unsigned char **images, std::string path, const int num_images_per_batch, const int max_num_images){
	
	std::ifstream file;

	std::cout << "Loading " << path << std::endl;
	file.open(path.c_str(), std::ios::binary);
	if(file.is_open()){
		unsigned char label = 0;
		for(int j=0;j<num_images_per_batch;++j){
			file.read((char *)&label, sizeof(label));
			file.read((char *)images[j],sizeof(unsigned char)*NUM_BYTES_PER_IMAGE);
		}
	}
	file.close();
}

using namespace cimg_library;

int main(int argc, char** argv){
	unsigned char images1[10000][3072];
	unsigned char images2[2000][3072];

	load_cifar((unsigned char**)images1,"./data/data_batch_1.bin",10000,10000);
	load_cifar((unsigned char**)images2,"./data/data_batch_1a.bin",1000,1000);
	load_cifar((unsigned char**)images2+1000,"./data/data_batch_1b.bin",1000,1000);

	CImg<unsigned char> img1(32,32,1,3,(char *)images1[999],false);
	CImg<unsigned char> img2(32,32,1,3,(char *)images2[999],false);

	CImgDisplay dispa(img1,"From large batch");
	CImgDisplay dispb(img2,"From split batch");

	while(!dispa.is_closed() && !dispb.is_closed()){
		
	}

	return 0;
}


