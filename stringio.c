#ifndef _STRINGIO_C_
#define _STRINGIO_C_

#include "stringio.h"

int read_line( FILE* file, char* str, int whitespace ) {
	int size;
	char c;

	size = 1;
	str  = (char*) malloc( size );

	while( (c = getc( file ) ) != '\n' ) {
		if( c == EOF ) {
			return 0;
		}
		if( !isspace( c ) || whitespace ) {
			str[size++] = c;
			str = (char*) realloc( str, size ); 
		}

	}
	str[size + 1] = 0;
	return 1;
}






#endif
