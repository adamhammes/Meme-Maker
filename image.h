#include "pixel_functions.h"

/*
	Defines the structure to hold the image.
*/


typedef struct image_s {
	unsigned int width;
	unsigned int height;
	
	/* will hold the pixels of the image */
	Pixel** pixels;
} Image;
