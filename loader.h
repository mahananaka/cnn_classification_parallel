#ifndef LOADER_H
#define LOADER_H

#include <string>
#include <vector>

#define IMG_SPECTRUM 3
#define IMG_HEIGHT 32
#define IMG_WIDTH 32

#define THREED_VECTOR(t) std::vector<std::vector<std::vector<t>>>
#define FOURD_VECTOR(t) std::vector<std::vector<std::vector<std::vector<t>>>>

void load_cifar(FOURD_VECTOR(int) &images, std::vector<int> &labels, 
		const std::vector<std::string> &batches, const int num_images_per_batch, const int max_num_images);

void format_data(THREED_VECTOR(int) &img, const unsigned char *d);

#endif
