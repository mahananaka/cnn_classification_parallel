#ifndef FCLAYER_H_
#define FCLAYER_H_

#include "cnnlayer.h"

class FullyConnectedLayer : public CnnLayer {
	private:
		std::vector<std::vector<float>> batch_answers, flattened_input, mapped_output;
		std::vector<std::vector<float>> weights, deltas, dbiases;
		std::vector<float> biases;
		VECT3D(float) dweights;
		int num_neurons;
		float learn_rate;
	public:
		FullyConnectedLayer(LayerAttrib &attr, int bs, float lr);
		~FullyConnectedLayer();
		void ForwardPass(VECT4D(float) &input);
		void BackPropagate(VECT4D(float) &deltas);
		void PrintLayout();
		void set_targets(std::vector<float> &targets) override;
		void flatten_input(VECT4D(float) &input);
};

#endif
