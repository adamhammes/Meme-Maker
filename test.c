#include "font_functions.h"

int main() {
	Font* f = read_font_file( "impact.fsf" );

	free_font( f );
	free( f );

	return 0;
}


