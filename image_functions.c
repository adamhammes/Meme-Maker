#include "image_functions.h"

FILE* open_file(char* name) {
	FILE* file = fopen( name, "rb" );

	if( file == 0 ) {
		printf("File not found.\n");
		exit(0);
	}

	fflush(file);

	return file;
}


Image read_in( char* name ) {
	FILE* f = fopen( name, "rb" );

	int i, j;
	Image image;
	fread( &(image.width),  sizeof(int), 1, f );
	fread( &(image.height), sizeof(int), 1, f);
	
	image.pixels  = (Pixel**) malloc( image.width * sizeof(Pixel*) );
	
	for( i = 0; i < image.width; i++ ) {
		image.pixels[i] = (Pixel*) malloc( image.height * sizeof(Pixel) );
	}

	for( j = 0; j < image.height; j++ ) {
		for( i = 0; i < image.width; i++ ) {
			fread( &image.pixels[i][j].red,   sizeof(unsigned char), 1, f );
			fread( &image.pixels[i][j].green, sizeof(unsigned char), 1, f );
			fread( &image.pixels[i][j].blue,  sizeof(unsigned char), 1, f );
			fread( &image.pixels[i][j].alpha, sizeof(unsigned char), 1, f );
		}
	}

	return image;
}

Image make_one( Image* pic1, Image* pic2, int x, int y ) {
	int i, j;
	Image temp;

	temp = make_image( pic1->width, pic1->height );

	for( j = 0; j < pic1->height; j++ ) {
		for( i = 0 ; i < pic1->width; i++ ) {
			temp.pixels[i][j] = pic1->pixels[i][j];
		}
	}

	if( x < 0 || y < 0 ) {
		return temp;
	}


	for( j = y; (j - y) < pic2->height && j < pic1->height; j++ ) {
		for( i = x; (i - x) < pic2->width && i < pic1->width; i++ ) {
			temp.pixels[i][j] = overlay( &pic1->pixels[i][j], &pic2->pixels[i - x][j - y]);
		}
	}
	return temp;
}

Image crop(Image* pic, int x_start, int y_start, int x, int y) {
	Image new;
	int i, j;

	new.width  = x;
	new.height = y;
	new.pixels = (Pixel**) malloc( new.width * sizeof(Pixel*) );

	for( i = 0; i < new.width; i++ ) {
		new.pixels[i] = (Pixel*) malloc( new.height * sizeof(Pixel) );	
	}

	for( j = y_start; j < (y_start + y) && j < pic->height; j++ ) { 
		for( i = x_start; i < (x_start + x) && i < pic->width; i++ ) {
			new.pixels[i - x_start][j - y_start] = pic->pixels[i][j];
		}
	}

	return new;
}

void make_funky(Image* pic, char* pattern) {
	int i, j;

	for( j = 0; j < pic->height; j++ ) {
		for( i = 0; i < pic->width; i++ ) {
			color_shift( &pic->pixels[i][j], pattern );
		}
	}
}

void make_grey(Image* pic) {
	int i, j;

	for( j = 0; j < pic->height; j++ ) {
		for( i = 0; i < pic->width; i++ ) {
			black_and_white( &pic->pixels[i][j] );
		}
	}	
}

void write_file(Image* pic, char* name) {
	int i, j;

	FILE* outfile = fopen( name, "wb" );
	fwrite( &(pic->width),  sizeof(int), 1, outfile );
	fwrite( &(pic->height), sizeof(int), 1, outfile );

	for( j = 0; j < pic->height; j++ ) {
		for( i = 0; i < pic->width; i++ ) {
			fwrite( &(pic->pixels[i][j].red),   sizeof(unsigned char), 1, outfile );
			fwrite( &(pic->pixels[i][j].green), sizeof(unsigned char), 1, outfile );
			fwrite( &(pic->pixels[i][j].blue),  sizeof(unsigned char), 1, outfile );
			fwrite( &(pic->pixels[i][j].alpha), sizeof(unsigned char), 1, outfile );
		}
	}

	fclose( outfile );
}

void close_image(Image* image) {
	int i;
	for( i = 0; i < image->width; i++ ) {
		free( image->pixels[i] );
	}

	free( image->pixels );
}

Image make_image( int x, int y ) {
	Image temp;
	int i;

	temp.width = x;
	temp.height = y;

	temp.pixels = (Pixel**) malloc( x * sizeof(Pixel*) );
	
	for( i = 0; i < x; i++ ) {
		temp.pixels[i] = (Pixel*) malloc( x * sizeof(Pixel) );
	}

	return temp;
}
