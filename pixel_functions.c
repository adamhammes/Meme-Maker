

#include "pixel_functions.h"
#include <math.h>
#include <string.h>
#include <stdlib.h>

Pixel create_pixel(unsigned char r, unsigned char g, unsigned char b, unsigned char a) {
	Pixel temp;
	temp.red = r;
	temp.green = g;
	temp.blue = b;
	temp.alpha = a;
	
	return temp;	
}	

void black_and_white(Pixel *p) {
	double average =( (double) (p->red + p->blue + p->green) )/3;
	unsigned char rounded_average = round( average );
	p->red = p->blue = p->green = average;
}

Pixel overlay(Pixel *a, Pixel *b) {
	Pixel temp;

	temp.red =   calculate_color(a->red, b->red, a->alpha, b->alpha);
	temp.blue =  calculate_color(a->blue, b->blue, a->alpha, b->alpha);
	temp.green = calculate_color(a->green, b->green, a->alpha, b->alpha);
	temp.alpha = (unsigned char) lround( (double) b->alpha + a->alpha * (255- b->alpha) / 255 );

	return temp;
}

unsigned char calculate_color(unsigned char r1, unsigned char r2, unsigned char a1, unsigned char a2) {
	return (unsigned char) lround( a2 * r2 /255. + a1* r1* (255-a2)/ 255/ 255);
}

void color_shift(Pixel *p, char* pattern) {
	if( strcmp( pattern, "RG" ) == 0 || strcmp( pattern, "GR" ) == 0 ) {
		swap_colors( &p->red, &p->green);
	} else if( strcmp( pattern, "BR" ) == 0 || strcmp( pattern, "RB" ) == 0 ) {
		swap_colors( &p->red, &p->blue );
	} else if( strcmp( pattern, "BG" ) == 0 || strcmp( pattern, "GB" ) == 0 ) {
		swap_colors( &p->green, &p->blue );
	} else if( strcmp( pattern, "RGB" ) == 0 || strcmp( pattern, "GBR" ) == 0 || strcmp( pattern, "BRG" ) == 0 ) {
		triple_swap( &p->red, &p->green, &p->blue );
	} else if( strcmp( pattern, "RBG" ) == 0 || strcmp( pattern, "BGR" ) == 0 || strcmp( pattern, "GRB" ) == 0 ) {
		triple_swap( &p->red, &p->blue, &p->green );
	}
}

void swap_colors(unsigned char *a, unsigned char *b) {
	unsigned char t  = *a;
	*a = *b;
	*b = t;
}

void triple_swap( unsigned char *a, unsigned char *b, unsigned char *c ) {
	unsigned char t = *c;
	
	*c = *b;
	*b = *a;
	*a = t;	
}
