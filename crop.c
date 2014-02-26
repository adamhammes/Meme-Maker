#include "image_functions.h"

int main( int argc, char** argv ) {
	FILE* infile;
	Image pic, new;

	if( argc < 7 ) {
		printf("Please enter all arguments.\n");
		exit(0);
	}

	infile = open_file( argv[1] );
	pic = read_in( infile );
	fclose( infile );

	new = crop( &pic, atoi(argv[3]), atoi(argv[4]), atoi(argv[5]), atoi(argv[6]) );
	write_file( &new, argv[2] );

	close_image( &pic );
	close_image( &new );

	return 0;
}
