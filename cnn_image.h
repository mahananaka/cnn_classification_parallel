#include <cstring>

#define HEIGHT 32
#define WIDTH 32
#define SPECTRUM 3

enum ImgType { AIRPLANE, AUTOMOBILE, BIRD,
	        CAT, DEER, DOG, FROG, HORSE, SHIP, TRUCK };
class CnnImage {
	public:
		ImgType label;
		unsigned char data[SPECTRUM][WIDTH][HEIGHT];
		int w = WIDTH;
		int h = HEIGHT;
		int s = SPECTRUM;
	
		CnnImage(unsigned char t, unsigned char *d) : label(static_cast<ImgType>(t)) {
			std::memcpy(data,d,s*w*h);
		}

		~CnnImage() {}

};
