#include <chrono>
#include <iostream>
#include <vector>
#include "loader.h"

#define MAX_LOAD_TRAINER_IMAGES 10000
#define MAX_LOAD_TEST_IMAGES 10000

typedef std::chrono::high_resolution_clock Clock;


int main (int argc, char** argv)
{
	std::vector<std::string> trainer_paths { "./data/data_batch_1.bin","./data/data_batch_2.bin",
		"./data/data_batch_3.bin","./data/data_batch_4.bin","./data/data_batch_5.bin" };
	std::vector<std::string> trainer_paths2 { "./data/data_batch_1a.bin","./data/data_batch_1b.bin",
		"./data/data_batch_1c.bin","./data/data_batch_1d.bin","./data/data_batch_1e.bin",
		"./data/data_batch_1f.bin","./data/data_batch_1g.bin","./data/data_batch_1h.bin",
		"./data/data_batch_1i.bin","./data/data_batch_1j.bin","./data/data_batch_2a.bin",
		"./data/data_batch_2b.bin","./data/data_batch_2c.bin","./data/data_batch_2d.bin",
		"./data/data_batch_2e.bin","./data/data_batch_2f.bin","./data/data_batch_2g.bin",
		"./data/data_batch_2h.bin","./data/data_batch_2i.bin","./data/data_batch_2j.bin",
		"./data/data_batch_3a.bin","./data/data_batch_3b.bin","./data/data_batch_3c.bin",
		"./data/data_batch_3d.bin","./data/data_batch_3e.bin","./data/data_batch_3f.bin",
		"./data/data_batch_3g.bin","./data/data_batch_3h.bin","./data/data_batch_3i.bin",
		"./data/data_batch_3j.bin","./data/data_batch_4a.bin","./data/data_batch_4b.bin",
		"./data/data_batch_4c.bin","./data/data_batch_4d.bin","./data/data_batch_4e.bin",
		"./data/data_batch_4f.bin","./data/data_batch_4g.bin","./data/data_batch_4h.bin",
		"./data/data_batch_4i.bin","./data/data_batch_4j.bin","./data/data_batch_5a.bin",
		"./data/data_batch_5b.bin","./data/data_batch_5c.bin","./data/data_batch_5d.bin",
		"./data/data_batch_5e.bin","./data/data_batch_5f.bin","./data/data_batch_5g.bin",
		"./data/data_batch_5h.bin","./data/data_batch_5i.bin","./data/data_batch_5j.bin"};

	std::vector<std::string> test_paths { "./data/test_batch.bin" };
	//Statement to let us know the main started
	std::cout << "Running program"<<std::endl;

	std::vector<int> trainer_labels, trainer_labels2, test_labels;
	FOURD_VECTOR(int) trainer_images, trainer_images2, test_images;

	std::cout << "Loading cifar batches:" << std::endl;

	auto t1 = Clock::now();
	for(int i=0;i<2;++i){
		alt_load_cifar(trainer_images, trainer_paths[i], 10000, 50000);
	}
	for(int i=0;i<20;++i){
		alt_load_cifar(trainer_images2,trainer_paths2[i], 1000, 50000);
	}
	/*
	alt_load_cifar(trainer_images2, "./data/data_batch_1a.bin", 1000, 10000);
	alt_load_cifar(trainer_images2, "./data/data_batch_1b.bin", 1000, 10000);
	alt_load_cifar(trainer_images2, "./data/data_batch_1c.bin", 1000, 10000);
	alt_load_cifar(trainer_images2, "./data/data_batch_1d.bin", 1000, 10000);
	alt_load_cifar(trainer_images2, "./data/data_batch_1e.bin", 1000, 10000);
	alt_load_cifar(trainer_images2, "./data/data_batch_1f.bin", 1000, 10000);
	alt_load_cifar(trainer_images2, "./data/data_batch_1g.bin", 1000, 10000);
	alt_load_cifar(trainer_images2, "./data/data_batch_1h.bin", 1000, 10000);
	alt_load_cifar(trainer_images2, "./data/data_batch_1i.bin", 1000, 10000);
	alt_load_cifar(trainer_images2, "./data/data_batch_1j.bin", 1000, 10000);
	*/
	auto t2 = Clock::now();

	auto t = std::chrono::duration_cast<std::chrono::milliseconds>(t2-t1).count();
	std::cout << "Loaded into 4d vector in " << t << " ms" << std::endl;

	for(int i=0;i<20000;++i){
		for(int j=0;j<3;++j){
			for(int k=0;k<32;++k){
				for(int l=0;l<32;++l){
					if(trainer_images[i][j][k][l] == trainer_images2[i][j][k][l]){
						if(i%1000==0 && j==0 && k==0 && l==0){
							std::cout << "good upto " << i << std::endl;
						}
					}else{
						std::cout << "prob: ["<<i<<"]["<<j<<"]["<<k<<"]["<<l<<"]" << std::endl;
						exit(-1);
					}
				}
			}
		}
	}

	std::cout << trainer_images.size() << " trainer images and " << test_images.size() 
		<< " test image have been loaded" << std::endl;

	std::cout << trainer_images2.size() << " trainer2 images and " << test_images.size() 
		<< " test image have been loaded" << std::endl;
	
	//Clear memory
	trainer_images.clear();
	test_images.clear();
	trainer_labels.clear();
	test_labels.clear();

	//Statement to let us know we exited without any error
	std::cout << "\nExiting program"<<std::endl;
	return 0;
}
