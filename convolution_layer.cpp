#include <iostream>
#include "convolution_layer.h"

ConvolutionLayer::ConvolutionLayer(LayerAttrib &attrib, int bs) : CnnLayer(attrib, bs){
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
	for(int b=0;b<batch_size;++b){
		stored_output[b].resize(out_depth);
		for(int i=0;i<out_depth;++i){
			stored_output[b][i].resize(out_height);
			for(int j=0;j<out_height;++j){
				stored_output[b][i][j].resize(out_width);
				for(int k=0;k<out_width;++k){
					stored_output[b][i][j][k] = k;	
				}
			}
		}
	}

	kernal.resize(num_kernals);
	for(int i=0;i<num_kernals;++i){
		kernal[i].resize(kernal_size);
		for(int j=0;j<kernal_size;++j){
			kernal[i][j].resize(kernal_size);
			for(int k=0;k<kernal_size;++k){
				kernal[i][j][k] = 0.5;	
			}
		}
	}
		
}

ConvolutionLayer::~ConvolutionLayer(){
	stored_input.clear();
	stored_output.clear();
}

void ConvolutionLayer::ForwardPass(VECT4D(float) &input){
	batch_size = input.size();

	for(int ind=0;ind<batch_size;++ind){
		for(int d=0;d<in_depth;++d){
			for(int h=0;h<in_height;++h){
				for(int w=0;w<in_width;++w){
					stored_input[ind][d][h][w] = input[ind][d][h][w];
				}
			}
		}
	}

	/*
	* This is a very big loop of with multiple 2D stencils striding over
	* multiple 3D inputs. This totals 7 nested for loops.
	*/

	//calculate the range of height/width;
	int hlimit = in_height-kernal_size+1;
	int wlimit = in_width-kernal_size+1;

	/*
	//foreach img, foreach kernal, foreach depth(channel)
	for(int ind=0;ind<batch_size;++ind){
		for(int k=0;k<num_kernals;++k){
			for(int d=0;d<in_depth;++d){

				//output depth is different than input depth
				int od = k*in_depth+d;

				//limit the range so that we don't overflow with the stencil
				for(int h=0;h<hlimit;h+=stride){
					for(int w=0;w<wlimit;w+=stride){	
						for(int i=0;i<kernal_size;++i){
							for(int j=0;j<kernal_size;++j){
								stored_output[ind][od][h][w] += stored_input[ind][d][h+i][w+j]*kernal[k][i][j];
							}
						}
					}
				}
				//end of stencil over one slice
			}
		}
	}*/

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

void ConvolutionLayer::BackPropagate(VECT4D(float) &deltas){

}


void ConvolutionLayer::PrintLayout(){
	std::cout << std::endl;
	std::cout << "LayerType: Convolution" << std::endl;
	std::cout << "id=" << in_depth << " ih=" << in_height << " iw=" << in_width << std::endl;
	std::cout << "od=" << out_depth << " oh=" << out_height << " ow=" << out_width << std::endl;
	std::cout << std::endl;
	
	std::cout << "kernal:" << std::endl;
	print_3d_vector(kernal);

	//std::cout << "stored_input:" << std::endl;
	//print_4d_vector(stored_input);
	//std::cout << "stored_output:" << std::endl;
	//print_4d_vector(stored_output);
}

void ConvolutionLayer::apply_kernals(int b, int d, int h, int w){
	for(int i=0;i<num_kernals;++i){
		for(int j=0;j<kernal_size;++j){
			for(int k=0;k<kernal_size;++k){
				stored_output[b][i*in_depth+d][h/stride][w/stride] += stored_input[b][d][h+j][w+k]*kernal[i][j][k];
			}
		}
	}
}

