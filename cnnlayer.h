#ifndef CNNLAYER_H_
#define CNNLAYER_H_

#include "cnn_types.h"

class CnnLayer {
	protected:	
		int in_depth, in_height, in_width;
		int out_depth, out_height, out_width;
		int kernal_size, num_kernals, stride;
		VECT3D(int) stored_input;
		VECT3D(int) stored_output;
	public:
		CnnLayer(LayerAttrib &attrib);
		~CnnLayer();
		virtual void ForwardPass(VECT3D(int) &input) = 0;
		virtual void BackPropagate(VECT3D(int) &deltas) = 0;
		void print_layout();
		void print_3d_vector(VECT3D(int) &A);
};

#endif
