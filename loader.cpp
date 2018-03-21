#include <fstream>
#include "loader.h"
#include <iostream>
#include <algorithm>

#define NUM_BYTES_PER_IMAGE 3072

void  load_cifar(FOURD_VECTOR(int) &images, std::vector<int> &labels, std::vector<std::string> &paths,
		const int num_images_per_batch, const int max_num_images){

	int capacity = std::min(max_num_images,num_images_per_batch*static_cast<int>(paths.size()));
	images.resize(capacity);
	labels.resize(capacity);

	for(int i=0;i<paths.size();++i){
		std::ifstream file;
		int offset = i*num_images_per_batch;

        	file.open(paths[i].c_str(), std::ios::binary);
	        if(file.is_open()){
			unsigned char lbl = 0;
			unsigned char temp[NUM_BYTES_PER_IMAGE];
			for(int j=0;j<1;++j){
				if(offset+j<capacity){
					file.read((char *)&lbl, sizeof(lbl));
					file.read((char *)temp,sizeof(unsigned char)*NUM_BYTES_PER_IMAGE);
					format_data(images[offset+j],temp);
					labels[offset+j] = static_cast<int>(lbl);
				}else{
					break;
				}
			}
		}
		file.close();
	}
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
