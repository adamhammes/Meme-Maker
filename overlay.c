#include "image_functions.h"

int main( int argc, char** argv ) {
	FILE* infile;
	Image pic1, pic2, pic3;

	if( argc < 6 ) {
		printf("Please enter all arguments.");
		exit(0);
	}

	infile = open_file( argv[1] );
	pic1 = read_in( infile );

	infile = open_file( argv[2] );
	pic2 = read_in( infile );
	
	fclose( infile );
	
	pic3 = make_one( &pic1, &pic2, atoi(argv[4]), atoi(argv[5]) );
	write_file( &pic3, argv[3] );

	close_image( &pic1 );
	close_image( &pic2 );
	close_image( &pic3 );

	return 0;
}
