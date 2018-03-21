#ifndef CNNLAYER_H_
#define CNNLAYER_H_

#include "cnn_helpers.h"

class CnnLayer {
	private:
		int i_height, i_width;
		int o_height, o_width;
		int kernal_size, num_kernals;
		int stride;
		int stored_input;
		int stored_output;
	public:
		Layers(int ih, int iw, int oh, int ow, int ks, int nk, int s) : 
			i_height(ih), i_width(iw), o_height(oh), o_width(ow), kernal_size(ks), num_kernals(nk), stride(s);
		virtual VECT3D(int) ForwardPass(VECT3D(int)) = 0;
		virtual VECT3D(int) BackPropagate() = 0;
};

#endif
