#include "image.h"
#include <stdio.h>
#include <stdlib.h>

FILE* open_file(char* name);
Image read_in(FILE* f);


Image crop(Image* pic, int x_start, int y_start, int x, int y);
void make_grey(Image* pic);
void make_funky(Image* pic, char* pattern);
void write_image(char* name, Image* pic);

Image make_one(Image* pic1, Image* pic2, int x, int y);
Image make_image( int x, int y);
void close_image(Image* i);
