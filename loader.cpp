#include <fstream>
#include "loader.h"

//#define INPUTFILE "inputs.txt"
//#define NUM_IMAGES 10000 //number per batch file
//#define IMG_SIZE 3072 //CIFAR-10 block size

void load_cifar(std::vector<CnnImage*> &images, const std::string inputfile, const int img_size, const int num_images){
	std::string line;
	std::ifstream ifile;
	ifile.open(inputfile.c_str());
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

	for(int i=0;i<num_ibatches;++i){
		ifile.open(ibatches[i].c_str(), std::ios::binary);
		if(ifile.is_open()){
			unsigned char label = 0, temp = 0;
			std::vector<unsigned char> img;
			for(int j=0;j<num_images;++j){
				ifile.read((char *)&label, sizeof(label));
				for(int k=0;k<img_size;++k){
					ifile.read((char *)&temp, sizeof(temp));
					img.push_back(temp);
				}

				images.push_back(new CnnImage(label,img.data()));
			}
		}
		ifile.close();
	}
}

