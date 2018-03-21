#ifndef CONVOLAYER_H_
#define CONVOLAYER_H_

#include "cnnlayer.h"

class ConvolutionLayer : public CnnLayer {
	private:
	public:
		ConvolutionLayer(LayerAttrib &attr);
		~ConvolutionLayer();
		void ForwardPass(VECT3D(int) &input);
		void BackPropagate(VECT3D(int) &deltas);
};

#endif
