#ifndef CNNLAYER_H_
#define CNNLAYER_H_

#include "cnn_types.h"

class CnnLayer {
	protected:
		LayerType layer_type;	
		int batch_size, in_depth, in_height, in_width;
		int out_depth, out_height, out_width;
		VECT4D(float) stored_input;
		VECT4D(float) stored_output;
	public:
		CnnLayer(LayerAttrib &attrib, int bs);
		~CnnLayer();
		virtual void ForwardPass(VECT4D(float) &input) = 0;
		virtual void BackPropagate(VECT4D(float) &deltas) = 0;
		virtual void PrintLayout() = 0;
		virtual void set_targets(std::vector<float> &targets);
		void get_output_dimensions(int &d, int &h, int &w);
		LayerType get_layer_type();
		VECT4D(float) get_output();
		void print_4d_vector(VECT4D(float) &A);
		void print_3d_vector(VECT3D(float) &A);
		void print_2d_vector(std::vector<std::vector<float>> &A);
		void print_vector(std::vector<float> &A);
};

#endif
