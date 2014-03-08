#include "font_functions.h"

int main() {
	Font* f = read_font_file( "impact.fsf" );

	printf( "%s\n", f->name );

	printf( "%d\n", f->letters['a'].width );

	write_file( &f->letters['a'], "a.simp" );
	return 0;
}


