#include <fstream>
#include "loader.h"
#include <iostream>

#define NUM_BYTES_PER_IMAGE 3072
#define NUM_IMAGES_PER_BATCH 10000

void  load_cifar(FOURD_VECTOR(int) &images, std::vector<int> &labels, 
		const std::vector<std::string> &batches, const int num_images_per_batch, const int max_num_images){
	
	std::string line;
	std::ifstream file;
	int num_batches = batches.size();
	images.resize(max_num_images);

	for(int i=0;i<num_batches;++i){
		std::cout << "Loading " << batches[i] << std::endl;
		file.open(batches[i].c_str(), std::ios::binary);
		if(file.is_open()){
			unsigned char label = 0, temp = 0;
			std::vector<unsigned char> img;
			for(int j=0;j<num_images_per_batch;++j){
				file.read((char *)&label, sizeof(label));
				labels.push_back(static_cast<int>(label));
				for(int k=0;k<NUM_BYTES_PER_IMAGE;++k){
					file.read((char *)&temp, sizeof(temp));
					img.push_back(temp);
				}

				format_data(images[i*num_images_per_batch+j],img.data());
				if(i*num_images_per_batch+j>=max_num_images-1){
					file.close();
					return;
				}
			}
		}
		file.close();
	}
}

void  alt_load_cifar(FOURD_VECTOR(int) &images, std::string path, const int num_images_per_batch, const int max_num_images){
	std::ifstream file;
        std::cout << "Loading " << path << std::endl;
	int offset = images.size();
	images.resize(images.size()+num_images_per_batch);
        file.open(path.c_str(), std::ios::binary);
        if(file.is_open()){
		unsigned char label = 0;
		unsigned char temp[3072];
		for(int j=0;j<num_images_per_batch;++j){
			file.read((char *)&label, sizeof(label));
			file.read((char *)temp,sizeof(unsigned char)*NUM_BYTES_PER_IMAGE);
			format_data(images[offset+j],temp);
		}
	}
	file.close();
}

void format_data(THREED_VECTOR(int) &img, const unsigned char *d) {
	img.resize(IMG_SPECTRUM);

	for(int i=0;i<IMG_SPECTRUM;++i){
        	img[i].resize(IMG_HEIGHT);
        	for(int j=0;j<IMG_HEIGHT;++j){
        		img[i][j].resize(IMG_WIDTH);
		}
	}

	for(int i=0;i<IMG_SPECTRUM;++i){
		for(int j=0;j<IMG_HEIGHT;++j){
			for(int k=0;k<IMG_WIDTH;++k){
				img[i][j][k] = static_cast<int>(d[(i*IMG_SPECTRUM)+(j*IMG_HEIGHT)+k]);
			}
		}
	}
}
