#ifndef CONVONEURALNETWORK_H_
#define CONVONEURALNETWORK_H_

#include <vector>
#include "cnn_types.h"
#include "convolution_layer.h"

class ConvolutionalNeuralNetwork {
	private:
		std::vector<CnnLayer*> my_layers;
		VECT4D(float) images;
		int num_layers;
		int batch_size;
		int num_epochs;
		float learn_rate;
	public:
		ConvolutionalNeuralNetwork(std::vector<LayerAttrib> &layers, int ne, int bs, float lr);
		~ConvolutionalNeuralNetwork();
		void train(VECT4D(float) &inputs, std::vector<float> &answers);
		bool predict(VECT3D(float) &input);
		void dump_cnn();
		void print_layer(int index);
		void automate_inputs(LayerAttrib &cur, int d, int h, int w);
		int get_layer_count() { return num_layers; }
};

#endif
