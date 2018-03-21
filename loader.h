#ifndef LOADER_H
#define LOADER_H

#include <string>
#include <vector>
#include "cnn_types.h"

#define IMG_SPECTRUM 3
#define IMG_HEIGHT 32
#define IMG_WIDTH 32

void load_cifar(VECT4D(int) &images, std::vector<int> &labels, std::vector<std::string> &paths,
		const int num_images_per_batch, const int max_num_images);

void format_data(VECT3D(int) &img, const unsigned char *d);

#endif
