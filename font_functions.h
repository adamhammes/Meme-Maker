#include "image_functions.h"
#ifndef _FONT_FUNCTIONS_H_
#define _FONT_FUNCTIONS_H_


#include "structs.h"
#include <string.h>


void no_whitespace( char* str );
Font read_font_file( char* name );
void free_font( Font* font );


int set_letter( Font* f, char c, int x, int y, int w, int h);
int get_width( Font* f, char c );
int calculate_width( Font* font, char* sequece );
int crop_position( Font* f, Image* pic, char* sequence, int index, int x );

#endif
