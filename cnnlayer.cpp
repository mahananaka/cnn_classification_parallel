#include <iostream>
#include "cnnlayer.h"

CnnLayer::CnnLayer(LayerAttrib &attrib){
	in_depth = attrib.in_depth;
	in_height = attrib.in_height;
	in_width = attrib.in_width;
	kernal_size = attrib.kernal_size;
	num_kernals = attrib.num_kernals;
	stride = attrib.stride;
}

CnnLayer::~CnnLayer(){
	stored_input.clear();
	stored_output.clear();
}

void CnnLayer::print_layout(){
	std::cout << "id=" << in_depth << " ih=" << in_height << " iw=" << in_width << std::endl;
	std::cout << "od=" << out_depth << " oh=" << out_height << " ow=" << out_width << std::endl;
	std::cout << std::endl << std::endl;
	std::cout << "ks=" << kernal_size << " nk=" << num_kernals << " str=" << stride << std::endl;

	std::cout << "stored_input:" << std::endl;
	print_3d_vector(stored_input);
	std::cout << "stored_output:" << std::endl;
	print_3d_vector(stored_output);
}

void CnnLayer::print_3d_vector(VECT3D(int) &A){
	for(int i=0;i<A.size();++i){
		for(int j=0;j<A[i].size();++j){
			for(int k=0;k<A[i][j].size();++k){
				std::cout << A[i][j][k] << " "; 
			}
			std::cout << std::endl;
		}
		std::cout << std::endl;
	}
}
