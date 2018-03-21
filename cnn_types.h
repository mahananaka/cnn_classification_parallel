#ifndef CNNHELPERS_H_
#define CNNHELPERS_H_

#include <vector>

#define VECT3D(typ) std::vector<std::vector<std::vector<typ>>>
#define VECT4D(typ) std::vector<std::vector<std::vector<std::vector<typ>>>>

enum Classification { airplane, automobile, bird, cat, deer, dog, frog, horse, ship, truck };
enum LayerType { convolution, pool, relu, fc };

struct _layerattr{
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
