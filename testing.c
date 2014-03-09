#include "meme_functions.h"


int main() {
	printf("started\n");	
	Database* d = (Database*) malloc( sizeof( Database ) );
	printf("almost there...");
	read_meme_file( d, "memes.mem" );

	printf( "%s\n", d->memes[0].name );

	free_database( d );
	return 0;
}
