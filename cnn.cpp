#include <iostream>
#include "cnn.h"
#include "convolution_layer.h"

ConvolutionalNeuralNetwork::ConvolutionalNeuralNetwork(std::vector<LayerAttrib> &layers){
	this->my_layers.resize(layers.size());
	
	for(int i=0;i<this->my_layers.size();++i){
		switch(layers[i].my_type) {
			case convolution:{
				CnnLayer *l = new ConvolutionLayer(layers[i]);
				my_layers[i] = l;
				break;
			}
			case pool:{
				break;
			}
			case relu:{		
				break;
			}
			case fc:{
				break;
			}
			default:{
				std::cout << "Error contructing CNN" << std::endl;
				break;
			}
		}
	}
}

void ConvolutionalNeuralNetwork::train(VECT4D(int) &inputs, std::vector<int> &answers){

}

bool ConvolutionalNeuralNetwork::predict(VECT3D(int) &input){

}

void ConvolutionalNeuralNetwork::dump_cnn(){
	for(int i=0;i<my_layers.size();++i){
		this->my_layers[i]->print_layout();	
	}
}
