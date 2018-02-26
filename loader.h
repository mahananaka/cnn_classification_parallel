#include <string>
#include <vector>
#include "cnn_image.h"

void load_cifar(std::vector<CnnImage*> &images, const std::string inputfile, const int img_size, const int num_images);
