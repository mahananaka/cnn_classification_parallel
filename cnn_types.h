#ifndef CNNTYPES_H_
#define CNNTYPES_H_

#include <vector>

#define VECT3D(typ) std::vector<std::vector<std::vector<typ>>>
#define VECT4D(typ) std::vector<std::vector<std::vector<std::vector<typ>>>>
#define SIGMOID(x) 1.0/(1.0 + exp(-1*x))
#define DSIGMOID(x) SIGMOID(x)*(1-SIGMOID(x))

#define NUM_CLASSIFICATIONS 10
enum Classification { airplane, automobile, bird, cat, deer, dog, frog, horse, ship, truck };
enum LayerType { convolution, pool, relu, fc };

struct _layerattr{
	_layerattr(LayerType t, int nk, int ks, int s, int id, int ih, int iw){
		my_type = t;
		num_kernals = nk;
		kernal_size = ks;
		stride = s;
		in_depth = id;
		in_height = ih;
		in_width = iw;
	}
	_layerattr(LayerType t, int nk, int ks, int s){
		my_type = t;
		num_kernals = nk;
		kernal_size = ks;
		stride = s;
		in_depth = -1;
		in_height = -1;
		in_width = -1;
	}

	LayerType my_type;
	int num_kernals;
	int kernal_size;
	int stride;
	int in_depth;
	int in_height;
	int in_width;
};

typedef struct _layerattr LayerAttrib;

#endif
