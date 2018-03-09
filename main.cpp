#include <chrono>
#include <iostream>
#include <vector>
#include "loader.h"

#define MAX_LOAD_TRAINER_IMAGES 50000
#define MAX_LOAD_TEST_IMAGES 10000
#define NUM_IMAGES_PER_BATCH 10000

typedef std::chrono::high_resolution_clock Clock;


int main (int argc, char** argv)
{
	std::vector<std::string> trainer_paths { "./data/data_batch_1a.bin","./data/data_batch_1b.bin",
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

	std::vector<std::string> test_paths { "./data/test_batch_a.bin", "./data/test_batch_b.bin",
		"./data/test_batch_c.bin","./data/test_batch_d.bin","./data/test_batch_e.bin",
		"./data/test_batch_f.bin","./data/test_batch_g.bin","./data/test_batch_h.bin",
       		"./data/test_batch_i.bin","./data/test_batch_j.bin" };
	
	/*
	std::vector<std::string> trainer_paths { "./data/data_batch_1.bin", "./data/data_batch_2.bin",
		"./data/data_batch_3.bin", "./data/data_batch_4.bin", "./data/data_batch_5.bin"};

	std::vector<std::string> test_paths { "./data/test_batch.bin" };
	*/

	//Statement to let us know the main started
	std::cout << "Running program"<<std::endl;

	std::vector<int> trainer_labels, test_labels;
	FOURD_VECTOR(int) trainer_images, test_images;

	std::cout << "Loading cifar:" << std::endl;
	std::cout << "...trainer images" << std::endl;
	auto t1 = Clock::now();
	load_cifar(trainer_images,trainer_labels,trainer_paths, NUM_IMAGES_PER_BATCH, MAX_LOAD_TRAINER_IMAGES);
	auto t2 = Clock::now();

	std::cout << "...test images" << std::endl;
	auto t3 = Clock::now();
	load_cifar(test_images,test_labels,test_paths, NUM_IMAGES_PER_BATCH, MAX_LOAD_TEST_IMAGES);
	auto t4 = Clock::now();

	auto diffa = std::chrono::duration_cast<std::chrono::milliseconds>(t2-t1).count();
	auto diffb = std::chrono::duration_cast<std::chrono::milliseconds>(t4-t3).count();
	std::cout << "Loaded into 4d vectors in " << diffa+diffb << " ms" << std::endl;

	std::cout << trainer_images.size() << " trainer images and " << test_images.size() 
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
