#ifndef _MEME_FUNCTIONS_H_
#define _MEME_FUNCTIONS_H_

#include "font_functions.h"

Place* get_place( Meme* meme, int index );
int count_spaces( char* line );
Meme make_meme( char* name );
Meme* get_meme( Database* data, char* name );
void read_meme_file( Database* data, char* name );
void free_database( Database* data );











#endif
