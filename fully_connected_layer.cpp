#include <iostream>
#include "fully_connected_layer.h"

FullyConnectedLayer::FullyConnectedLayer(LayerAttrib &attrib, int bs, float lr) : CnnLayer(attrib, bs){
	num_neurons = in_depth*in_height*in_width;
	out_depth = 0;
	out_height = 0;
	out_width = NUM_CLASSIFICATIONS;
	learn_rate = lr;

	//initalize stored_input, shape and values
	stored_input.resize(batch_size);
	for(int b=0;b<batch_size;++b){
		stored_input[b].resize(in_depth);
		for(int i=0;i<in_depth;++i){
			stored_input[b][i].resize(in_height);
			for(int j=0;j<in_height;++j){
				stored_input[b][i][j].resize(in_width);
				for(int k=0;k<in_width;++k){
					stored_input[b][i][j][k] = k;	
				}
			}
		}
	}

	//intialize stored_output
	//output is vector of floats from [0-1] representing the % confidence in that classification
	//its 1 dimensional of size equal to the possible classifications
	mapped_output.resize(batch_size);
	for(int b=0;b<batch_size;++b){
		mapped_output[b].resize(out_width);
		for(int c=0;c<out_width;++c){
			mapped_output[b][c] = 0;	
		}
	}

	//initialize answers for each input in the batch
	batch_answers.resize(batch_size);
	for(int b=0;b<batch_size;++b){
		batch_answers[b].resize(NUM_CLASSIFICATIONS);
		for(int c=0;c<NUM_CLASSIFICATIONS;++c){
			batch_answers[b][c] = 0;
		}
	}

	//project the input from 4D to 2D (batch index remains unaffected)
	flattened_input.resize(batch_size);
	for(int b=0;b<batch_size;++b){
		flattened_input[b].resize(num_neurons);
		for(int n=0;n<num_neurons;++n){
			flattened_input[b][n] = 0;
		}
	}

	//initialize dbiases and deltas
	dbiases.resize(batch_size);
	deltas.resize(batch_size);
	for(int b=0;b<batch_size;++b){
		dbiases[b].resize(NUM_CLASSIFICATIONS);
		deltas[b].resize(NUM_CLASSIFICATIONS);	
		for(int c=0;c<NUM_CLASSIFICATIONS;++c){
			dbiases[b][c] = 0;
			deltas[b][c] = 0;
		}
	}

	//initialize biases for each class	
	biases.resize(NUM_CLASSIFICATIONS);
	for(int c=0;c<NUM_CLASSIFICATIONS;++c){
		biases[c] = 0;
	}

	//initialize dweights
	dweights.resize(batch_size);
	for(int b=0;b<batch_size;++b){
		dweights[b].resize(num_neurons);
		for(int n=0;n<num_neurons;++n){
			dweights[b][n].resize(NUM_CLASSIFICATIONS);
			for(int c=0;c<NUM_CLASSIFICATIONS;++c){
				dweights[b][n][c] = 0;
			}
		}
	}

	//initialize weidths
	weights.resize(num_neurons);
	for(int n=0;n<num_neurons;++n){
		weights[n].resize(NUM_CLASSIFICATIONS);
		for(int c=0;c<NUM_CLASSIFICATIONS;++c){
			weights[n][c] = 0;
		}
	}
}

FullyConnectedLayer::~FullyConnectedLayer(){
	stored_input.clear();
	stored_output.clear();
}

void FullyConnectedLayer::ForwardPass(VECT4D(float) &input){
	batch_size = input.size();
}

void FullyConnectedLayer::BackPropagate(VECT4D(float) &deltas){

}

void FullyConnectedLayer::PrintLayout(){
	std::cout << std::endl;
	std::cout << "LayerType: Fully Connected" << std::endl;
	std::cout << "id=" << in_depth << " ih=" << in_height << " iw=" << in_width << std::endl;
	std::cout << "od=" << out_depth << " oh=" << out_height << " ow=" << out_width << std::endl;
	std::cout << std::endl;
	
	std::cout << "weights:" << std::endl;
	print_2d_vector(weights);

	std::cout << "dweights:" << std::endl;
	print_3d_vector(dweights);

	std::cout << "biases:" << std::endl;
	print_vector(biases);

	std::cout << "dbiases:" << std::endl;
	print_2d_vector(dbiases);

	std::cout << "deltas:" << std::endl;
	print_2d_vector(deltas);

	//std::cout << "stored_input:" << std::endl;
	//print_4d_vector(stored_input);
	//std::cout << "stored_output:" << std::endl;
	//print_4d_vector(stored_output);
}

void FullyConnectedLayer::set_targets(std::vector<float> &targets){
	//setting the correct answers for this batch of training images
	for(int i=0;i<batch_size;++i){
		for(int j=0;j<NUM_CLASSIFICATIONS;++j){
			batch_answers[i][j] = (targets[i]>0) ? targets[i] : 0;
		}
	}
}

// input[batch][depth][height][width] -> flattened_input[batch][depth*height*width]
void FullyConnectedLayer::flatten_input(VECT4D(float) &input){
	for(int b=0;b<batch_size;++b){
		for(int d=0;d<in_depth;++d){
			for(int h=0;h<in_height;++h){
				int offset = d*in_height*in_width+h*in_width;
				for(int w=0;w<in_width;++w){
					flattened_input[b][offset+w] = input[b][d][h][w];
				}	
			}
		}
	}
}

