#include <iostream>
#include "convolution_layer.h"

ConvolutionLayer::ConvolutionLayer(LayerAttrib &attrib) : CnnLayer(attrib){
	out_depth = in_depth*num_kernals; //id*nk;
	out_height = (in_height-kernal_size)/stride+1;
	out_width = (in_width-kernal_size)/stride+1;

	stored_input.resize(in_depth);
	for(int i=0;i<in_depth;++i){
		stored_input[i].resize(in_height);
		for(int j=0;j<in_height;++j){
			stored_input[i][j].resize(in_width);
			for(int k=0;k<in_width;++k){
				stored_input[i][j][k] = 0;	
			}
		}
	}

	stored_output.resize(out_depth);
	for(int i=0;i<out_depth;++i){
		stored_output[i].resize(out_height);
		for(int j=0;j<out_height;++j){
			stored_output[i][j].resize(out_width);
			for(int k=0;k<out_width;++k){
				stored_output[i][j][k] = 0;	
			}
		}
	}
}

ConvolutionLayer::~ConvolutionLayer(){
	stored_input.clear();
	stored_output.clear();
}

void ConvolutionLayer::ForwardPass(VECT3D(int) &input){

}

void ConvolutionLayer::BackPropagate(VECT3D(int) &deltas){

}

