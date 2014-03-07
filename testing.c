#include "font_functions.h"

int main() {
	Font* f = read_font_file( "impact.fsf" );

	printf( "%s\n", f->name );

	printf( "%d %d %d %d\n", f->coords['a'][0], f->coords['a'][1], f->coords['a'][2], f->coords['a'][3] );
	write_file( f->letters['a'], "a.simp" );
	free( f->name );
	free( f );

	return 0;
}


