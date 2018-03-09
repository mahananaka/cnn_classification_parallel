#include <fstream>
#include <iostream>
#include <algorithm>
#include "loader.h"
#include "omp.h"

#define NUM_BYTES_PER_IMAGE 3072

void  load_cifar(FOURD_VECTOR(int) &images, std::vector<int> &labels, std::vector<std::string> &paths,
		const int num_images_per_batch, const int max_num_images){

	int num_paths = static_cast<int>(paths.size());
	int capacity = std::min(max_num_images,num_images_per_batch*num_paths);
	images.resize(capacity);
	labels.resize(capacity);

	std::ifstream files[num_paths];

	#pragma omp parallel for shared(files,images,labels,num_paths,capacity) num_threads(num_paths)
	for(int i=0;i<num_paths;++i){
		int offset = i*num_images_per_batch;
        	files[i].open(paths[i].c_str(), std::ios::binary);
	        if(files[i].is_open()){
			unsigned char lbl = 0;
			unsigned char temp[NUM_BYTES_PER_IMAGE];
			for(int j=0;j<num_images_per_batch;++j){
				if(offset+j<capacity){
					files[i].read((char *)&lbl, sizeof(lbl));
					files[i].read((char *)temp,sizeof(unsigned char)*NUM_BYTES_PER_IMAGE);
					format_data(images[offset+j],temp);
					labels[offset+j] = static_cast<int>(lbl);
				}else{
					break;
				}
			}
		}
		files[i].close();
	}
}

void format_data(THREED_VECTOR(int) &img, const unsigned char *d) {
	img.resize(IMG_SPECTRUM);

	#pragma omp parallel for shared(img,d)
	for(int i=0;i<IMG_SPECTRUM;++i){
        	img[i].resize(IMG_HEIGHT);
        	for(int j=0;j<IMG_HEIGHT;++j){
        		img[i][j].resize(IMG_WIDTH);
		}
	}

	#pragma omp parallel for shared(img,d)
	for(int i=0;i<IMG_SPECTRUM;++i){
		for(int j=0;j<IMG_HEIGHT;++j){
			for(int k=0;k<IMG_WIDTH;++k){
				img[i][j][k] = static_cast<int>(d[(i*IMG_SPECTRUM)+(j*IMG_HEIGHT)+k]);
			}
		}
	}
}
