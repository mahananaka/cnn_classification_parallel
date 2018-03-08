#include <fstream>
#include <iostream>
#include "CImg.h"
#include <string>

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
	unsigned char **images1 = new unsigned char*[10000];
	unsigned char **images2 = new unsigned char*[10000];

	for(int i=0;i<10000;++i){
		images1[i] = new unsigned char[3072];
		images2[i] = new unsigned char[3072];
	}

	load_cifar((unsigned char**)images1,"./data/data_batch_1.bin",10000,10000);
	load_cifar((unsigned char**)images2,"./data/data_batch_1a.bin",1000,1000);
	load_cifar((unsigned char**)images2+1000,"./data/data_batch_1b.bin",1000,1000);
	load_cifar((unsigned char**)images2+2000,"./data/data_batch_1c.bin",1000,1000);
	load_cifar((unsigned char**)images2+3000,"./data/data_batch_1d.bin",1000,1000);
	load_cifar((unsigned char**)images2+4000,"./data/data_batch_1e.bin",1000,1000);
	load_cifar((unsigned char**)images2+5000,"./data/data_batch_1f.bin",1000,1000);
	load_cifar((unsigned char**)images2+6000,"./data/data_batch_1g.bin",1000,1000);
	load_cifar((unsigned char**)images2+7000,"./data/data_batch_1h.bin",1000,1000);
	load_cifar((unsigned char**)images2+8000,"./data/data_batch_1i.bin",1000,1000);
	load_cifar((unsigned char**)images2+9000,"./data/data_batch_1j.bin",1000,1000);


	int curimg = std::atoi(argv[1]);
	CImg<unsigned char> img1((unsigned char *)images1[curimg],32,32,1,3,false);
	CImg<unsigned char> img2((unsigned char *)images2[curimg],32,32,1,3,false);

	for(int i=0;i<10000;++i){
		for(int j=0;j<3072;++j){
			if(images1[i][j] == images2[i][j]){

			}else{
				std::cout << i << "," << j << "  -  " << images1[i][j] << ":" 
					<< images2[i][j] << std::endl;
			}
		}
	}

	CImgDisplay disp_a(img1,"from whole");
	CImgDisplay disp_b(img2,"from split");

	disp_a.resize(256,256,true);
	disp_b.resize(256,256,true);
	
	while(!disp_a.is_closed() && !disp_b.is_closed()){
		if(disp_a.button()&1){
		}
	}
	
	return 0;
}


