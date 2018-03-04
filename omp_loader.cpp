#include <fstream>
#include "loader.h"
#include <iostream>
#include <omp.h>

#define NUM_BYTES_PER_IMAGE 3072
#define NUM_IMAGES_PER_BATCH 10000

void load_cifar(FOURD_VECTOR(int) &images, std::vector<int> &labels, 
		const std::vector<std::string> &batches, const int max_num_images){
	
	int num_batches = batches.size();
	std::ifstream file[num_batches];
	images.resize(max_num_images);
	labels.resize(max_num_images);

	#pragma omp parallel for shared(batches,images,file) num_threads(num_batches)
	for(int i=0;i<num_batches;++i){
		std::cout << "Loading " << batches[i] << std::endl;
		file[i].open(batches[i].c_str(), std::ios::binary);
		if(file[i].is_open()){
			unsigned char label = 0, temp = 0;
			std::vector<unsigned char> img;
			for(int j=0;j<NUM_IMAGES_PER_BATCH;++j){
				file[i].read((char *)&label, sizeof(label));
				labels[i*NUM_IMAGES_PER_BATCH+j] = static_cast<int>(label);
				for(int k=0;k<NUM_BYTES_PER_IMAGE;++k){
					file[i].read((char *)&temp, sizeof(temp));
					img.push_back(temp);
				}

				format_data(images[i*NUM_IMAGES_PER_BATCH+j],img.data());
				//if(i*NUM_IMAGES_PER_BATCH+j>=max_num_images-1){
				//	file.close();
				//	return;
				//}
			}
		}
		file[i].close();
	}
}

void format_data(THREED_VECTOR(int) &img, const unsigned char *d) {
	img.resize(IMG_SPECTRUM);

	#pragma omp parallel for shared(img)
	for(int i=0;i<IMG_SPECTRUM;++i){
        	img[i].resize(IMG_HEIGHT);
        	for(int j=0;j<IMG_HEIGHT;++j){
        		img[i][j].resize(IMG_WIDTH);
		}
	}

	#pragma omp parallel for shared(img)
	for(int i=0;i<IMG_SPECTRUM;++i){
		for(int j=0;j<IMG_HEIGHT;++j){
			for(int k=0;k<IMG_WIDTH;++k){
				img[i][j][k] = static_cast<int>(d[(i*IMG_SPECTRUM)+(j*IMG_HEIGHT)+k]);
			}
		}
	}
}
