#ifndef _TESTING_C_
#define _TESTING_C_ 


#include "meme_functions.c"


int main() {
	Database* d;
	read_meme_file( d, "memes.mem" );

	printf( "%s\n", d->memes[0].name );

	free_database( d );
	return 0;
}

#endif
