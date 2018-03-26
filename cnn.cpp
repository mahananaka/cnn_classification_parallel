#include <iostream>
#include "cnn.h"
#include "convolution_layer.h"
#include "pool_layer.h"
#include "fully_connected_layer.h"

ConvolutionalNeuralNetwork::ConvolutionalNeuralNetwork(std::vector<LayerAttrib> &layers, int ne, int bs, float lr){
	num_epochs = ne;
	batch_size = bs;
	learn_rate = lr;

	try{
		num_layers = layers.size();
		my_layers.resize(num_layers);

		if(layers[num_layers-1].my_type != fc)
			throw -3;

		for(int i=0;i<num_layers;++i){
			if(layers[i].in_depth<0){
				if(i>0){
					int d, h, w;
					(my_layers[i-1])->get_output_dimensions(d, h, w);
					automate_inputs(layers[i],d,h,w);
				}else{
					throw -1;
				}
			}
			switch(layers[i].my_type) {
				case convolution:{
					CnnLayer *l = new ConvolutionLayer(layers[i],batch_size);
					my_layers[i] = l;
					break;
				}
				case pool:{
					CnnLayer *l = new PoolLayer(layers[i],batch_size);
					my_layers[i] = l;
					break;
				}
				case relu:{		
					break;
				}
				case fc:{
					CnnLayer *l = new FullyConnectedLayer(layers[i],batch_size, learn_rate);
					my_layers[i] = l;
					break;
				}
				default:{
					throw -2;
					break;
				}
			}
		}		
	}catch(int erno){
		std::cout << "Error constructing CNN: ";
		switch(erno){
			case -1:	
				std::cout << "First layer input dimensions must be defined." << std::endl;
				break;
			case -2:
				std::cout << "Invalid layer type." << std::endl;
				break;
			case -3:
				std::cout << "Last layer must be of type fc" << std::endl;
		}
		throw erno;
	}
}

ConvolutionalNeuralNetwork::~ConvolutionalNeuralNetwork(){
	for(int i=0;i<num_layers;++i){
		delete my_layers[i];
	}

	my_layers.clear();
}

void ConvolutionalNeuralNetwork::train(VECT4D(float) &images, std::vector<float> &answers){
	for(int e=0;e<num_epochs;++e){
		//TODO: randomize images and answers at start of epoch (must maintain relation between set)
		int iterations = images.size() / batch_size;
		int leftovers = images.size() % batch_size;

        for(int i=0;i<iterations;++i){
            std::cout << "running batch " << i << std::endl;
            VECT4D(float)::const_iterator start = images.begin() + (i*batch_size);
            VECT4D(float)::const_iterator end = start+batch_size;
            VECT4D(float) batch(start,end);

			std::vector<float>::const_iterator a_start = answers.begin() + (i*batch_size);	
			std::vector<float>::const_iterator a_end = a_start+batch_size;
			std::vector<float> batch_answers(a_start,a_end);
		
			my_layers[num_layers-1]->set_targets(batch_answers);
			my_layers[0]->ForwardPass(batch);
			for(int l=1;l<num_layers;++l){
				VECT4D(float) prev_layer_output = my_layers[l-1]->get_output();
				my_layers[l]->ForwardPass(prev_layer_output);
			}
			//TODO: handle the backpropagate
        }
		
		if(leftovers>0){
			//handle the leftovers
			std::cout << "running leftover batch size=" << leftovers << std::endl;
			VECT4D(float)::const_iterator start = images.begin() + (iterations*batch_size);
			VECT4D(float)::const_iterator end = start+leftovers;
			VECT4D(float) batch(start,end);

			std::vector<float>::const_iterator a_start = answers.begin() + (iterations*batch_size);	
			std::vector<float>::const_iterator a_end = a_start+leftovers;
			std::vector<float> batch_answers(a_start,a_end);

			my_layers[num_layers-1]->set_targets(answers);
			my_layers[0]->ForwardPass(batch);
			for(int l=1;l<num_layers;++l){
				VECT4D(float) prev_layer_output = my_layers[l-1]->get_output();
				my_layers[l]->ForwardPass(prev_layer_output);
			}
			//TODO: handle the backpropagate
		}
	}
}

bool ConvolutionalNeuralNetwork::predict(VECT3D(float) &input){

}

void ConvolutionalNeuralNetwork::dump_cnn(){
	for(int i=0;i<my_layers.size();++i){
		this->my_layers[i]->PrintLayout();	
	}
}

void ConvolutionalNeuralNetwork::print_layer(int index){
	if(index<num_layers && index>=0){
		my_layers[index]->PrintLayout();
	}else{
		std::cout << "Invalid index: " << index << std::endl;
	}
}

void ConvolutionalNeuralNetwork::automate_inputs(LayerAttrib &cur, int d, int h, int w){
	if(cur.in_depth<0)
		cur.in_depth = d;
	
	if(cur.in_height<0)
		cur.in_height = h;
	
	if(cur.in_width<0)
		cur.in_width = w;
}
