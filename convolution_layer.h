#ifndef CONVOLAYER_H_
#define CONVOLAYER_H_

#include "cnnlayer.h"

class ConvolutionLayer : public CnnLayer {
	private:
		VECT3D(float) kernal;
		int num_kernals, kernal_size, stride;
		void apply_kernals(int b, int d, int h, int w);
	public:
		ConvolutionLayer(LayerAttrib &attr, int bs);
		~ConvolutionLayer();
		void ForwardPass(VECT4D(float) &input);
		void BackPropagate(VECT4D(float) &deltas);
		void PrintLayout();
};

#endif
