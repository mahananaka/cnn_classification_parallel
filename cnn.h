#ifndef CONVONEURALNETWORK_H_
#define CONVONEURALNETWORK_H_

#include <vector>
#include "cnn_types.h"
#include "convolution_layer.h"

class ConvolutionalNeuralNetwork {
	private:
		std::vector<CnnLayer*> my_layers;
		VECT4D(int) images;
	public:
		ConvolutionalNeuralNetwork(std::vector<LayerAttrib> &layers);
		void train(VECT4D(int) &inputs, std::vector<int> &answers);
		bool predict(VECT3D(int) &input);
		void dump_cnn();
};

#endif
