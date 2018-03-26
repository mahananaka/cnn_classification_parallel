#include <iostream>
#include "cnnlayer.h"

CnnLayer::CnnLayer(LayerAttrib &attrib, int bs){
	layer_type = attrib.my_type;
	in_depth = attrib.in_depth;
	in_height = attrib.in_height;
	in_width = attrib.in_width;
	batch_size = bs;
}

CnnLayer::~CnnLayer(){
	stored_input.clear();
	stored_output.clear();
}

void CnnLayer::get_output_dimensions(int &d, int &h, int &w){
	d = out_depth;
	h = out_height;
	w = out_width;
}

LayerType CnnLayer::get_layer_type(){
	return layer_type;
}

VECT4D(float) CnnLayer::get_output(){
	return stored_output;
}

void CnnLayer::set_targets(std::vector<float> &targets){
	//do nothing just a dummy for a derivative class
}

void CnnLayer::print_4d_vector(VECT4D(float) &A){
	for(int i=0;i<A.size();++i){
		std::cout << "img " << i+1 << " of " << A.size() << std::endl;
		for(int j=0;j<A[i].size();++j){
			for(int k=0;k<A[i][j].size();++k){
				for(int l=0;l<A[i][j][k].size();++l){
					std::cout << A[i][j][k][l] << " "; 
				}
				std::cout << std::endl;
			}
			std::cout << std::endl;
		}
	}
	std::cout << "------End of 4D Vector------" << std::endl << std::endl;
}

void CnnLayer::print_3d_vector(VECT3D(float) &A){
	for(int i=0;i<A.size();++i){
		for(int j=0;j<A[i].size();++j){
			for(int k=0;k<A[i][j].size();++k){
				std::cout << A[i][j][k] << " ";
			}
			std::cout << std::endl;
		}
		std::cout << std::endl;
	}
	std::cout << "------End of 3D Vector------" << std::endl << std::endl;
}

void CnnLayer::print_2d_vector(std::vector<std::vector<float>> &A){
	for(int i=0;i<A.size();++i){
		for(int j=0;j<A[i].size();++j){
			std::cout << A[i][j] << " ";
		}
		std::cout << std::endl;
	}
	std::cout << "------End of 2D Vector------" << std::endl << std::endl;
}
void CnnLayer::print_vector(std::vector<float> &A){
	for(int i=0;i<A.size();++i){
		std::cout << A[i] << " ";
	}
	std::cout << std::endl << "-----End of 1D Vector" << std::endl << std::endl;
}
