#include "font_functions.h"

int main() {
	Font* f = read_font_file( "impact.fsf" );

	printf( "%s\n", f->name );

	free( f->name );
	free( f );

	return 0;
}


