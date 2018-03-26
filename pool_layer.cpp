#include <iostream>
#include <limits>
#include "pool_layer.h"

PoolLayer::PoolLayer(LayerAttrib &attrib, int bs) : CnnLayer(attrib, bs){
	num_kernals = attrib.num_kernals;
	kernal_size = attrib.kernal_size;
	stride = attrib.stride;
	out_depth = in_depth*num_kernals; //id*nk;
	out_height = (in_height-kernal_size)/stride+1;
	out_width = (in_width-kernal_size)/stride+1;

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

	stored_output.resize(batch_size);
	pool_reference.resize(batch_size);
	for(int b=0;b<batch_size;++b){
		stored_output[b].resize(out_depth);
		pool_reference[b].resize(out_depth);
		for(int i=0;i<out_depth;++i){
			stored_output[b][i].resize(out_height);
			pool_reference[b][i].resize(out_height);
			for(int j=0;j<out_height;++j){
				stored_output[b][i][j].resize(out_width);
				pool_reference[b][i][j].resize(out_width);
				for(int k=0;k<out_width;++k){
					stored_output[b][i][j][k] = k;
					pool_reference[b][i][j][k] = k;
				}
			}
		}
	}
}

PoolLayer::~PoolLayer(){
	stored_input.clear();
	stored_output.clear();
}

void PoolLayer::ForwardPass(VECT4D(float) &input){
	batch_size = input.size(); //batch sizes could vary

	
	for(int b=0;b<batch_size;++b){
		for(int i=0;i<in_depth;++i){
			for(int j=0;j<in_height;++j){
				for(int k=0;k<in_width;++k){
					stored_input[b][i][j][k] = input[b][i][j][k];	
				}
			}
		}
	}


	int hlimit = in_height-kernal_size+1;
	int wlimit = in_width-kernal_size+1;
	for(int b=0;b<batch_size;++b){
		for(int d=0;d<in_depth;++d){
			for(int h=0;h<hlimit;h+=stride){
				for(int w=0;w<wlimit;w+=stride){
					apply_kernals(b,d,h,w);
				}
			}
		}
	}
}

void PoolLayer::BackPropagate(VECT4D(float) &deltas){

}

void PoolLayer::PrintLayout(){
	std::cout << std::endl;
	std::cout << "LayerType: Pool" << std::endl;
	std::cout << "id=" << in_depth << " ih=" << in_height << " iw=" << in_width << std::endl;
	std::cout << "od=" << out_depth << " oh=" << out_height << " ow=" << out_width << std::endl;
	std::cout << std::endl;
	
	std::cout << "pool_reference:" << std::endl;
	print_4d_vector(pool_reference);

	//std::cout << "stored_input:" << std::endl;
	//print_4d_vector(stored_input);
	//std::cout << "stored_output:" << std::endl;
	//print_4d_vector(stored_output);
}

void PoolLayer::apply_kernals(int b, int d, int h, int w){
	for(int i=0;i<num_kernals;++i){
		stored_output[b][i*in_depth+d][h/stride][w/stride] = stored_input[b][d][h][w];
		pool_reference[b][i*in_depth+d][h/stride][w/stride] = h*in_width+w;
		for(int j=0;j<kernal_size;++j){
			for(int k=0;k<kernal_size;++k){
				if(stored_input[b][d][h+j][w+k] > stored_output[b][i*in_depth+d][h/stride][w/stride]){ 
					stored_output[b][i*in_depth+d][h/stride][w/stride] = stored_input[b][d][h+j][w+k];
					pool_reference[b][i*in_depth+d][h/stride][w/stride] = (h+j)*in_width+(w+k);
				}
			}
		}
	}
}
