#ifndef POOLLAYER_H_
#define POOLLAYER_H_

#include "cnnlayer.h"

class PoolLayer : public CnnLayer {
	private:
		int num_kernals, kernal_size, stride;
		VECT4D(float) pool_reference;
		void apply_kernals(int b, int d, int h, int w);
	public:
		PoolLayer(LayerAttrib &attr, int bs);
		~PoolLayer();
		void ForwardPass(VECT4D(float) &input);
		void BackPropagate(VECT4D(float) &deltas);
		void PrintLayout();
};

#endif
