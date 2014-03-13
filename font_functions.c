#ifndef _FONT_FUNCTIONS_C_
#define _FONT_FUNCTIONS_C_

#include "font_functions.h"


char* no_whitespace( char* str ) {
	char* end;
	
	if( strlen( str ) < 1 || str[0] == '\n' ) {
		return str;
	}

	while( isspace( str[0] ) ) {
		str++;
	}

	end = str + strlen( str ) - 1;
	while( end > str  && isspace( end[0] ) ) {
		end--;
	}

	end[1] = 0;
	
	return str;
}

Font read_font_file( char* name ) {
	char* line = NULL;
	char* trim;
	Image temp;
	Font f;
	int length;
	int nums[4];
	char c;
	int i, j;
	size_t buffer_size;
	FILE* file = fopen( name, "r" );

	if( file == 0 ) { 
		printf("%s not found\n", name );
		exit(0);
	}
	
	/* set all coords to zero so we know later which ones are initialized */
	for( i = 0; i < 256; i++ ) {
		for( j = 0; j < 4; j++ ) { 
			f.coords[i][j] = 0;
		}
	}
	while( getline( &line, &buffer_size, file ) != -1 ) { /* while we have not reached end of file */
		trim = no_whitespace( line );
		if( trim[0] == 'N' ) { /* if we are reading the name line */
			length = strlen( trim ) - 5 + 1; /* plus 1 to account for null 0 */
			strcpy( f.name, &trim[5] );
			f.name[length - 1] = 0;
		} else if( trim[0] == 'I' ) { /* if we are reading file name line */
			f.base_image = read_in( &trim[6] );
		} else if( line[0] == 'C' ) { /* if we are specifying character dimensions */
			c = trim[9];
			sscanf( trim,  "CHARACTER%c:%d %d %d %d", &c, &f.coords[c][0], &f.coords[c][1], &f.coords[c][2], &f.coords[c][3] );
		}
		free( line );
		line = NULL;
	}
	fclose( file );
	for( i = 0; i < 256; i++ ) {
		if( f.coords[i][2] != 0 ) { /* if the coordinates were listed for this character */
			set_letter( &f, (char) i, f.coords[i][0], f.coords[i][1], f.coords[i][2], f.coords[i][3] );
		}
	}
	return f;
}

int set_letter( Font* f, char c, int x, int y, int w, int h ) {
	if( x < 0 || x + w > f->base_image.width || y < 0 || y + h > f->base_image.height ||
		x < 0 || y < 0 ) { /* if invalid dimensions given */
		return 0;
	}

	f->letters[ (int) c ] = crop( &f->base_image, x, y, w, h );
	return 1;
}

void free_font( Font* font ) {
	int i;
	close_image( &font->base_image );
	for( i = 0; i < 256; i++ ) {
		if( font->coords[i][3] != 0 ) {
			close_image( &font->letters[i] );
		}
	}
}

int get_width( Font* font, char c ) {
	if( font->letters == 0 ) {
		return 0;
	}

	return font->letters[c].width;
}

int calculate_width( Font* font, char* sequence ) {
	int i;
	int width = 0;

	for( i = 0; i < strlen( sequence ); i++ ) {
			width += get_width( font, sequence[i] );
	}

	return width;
}

int crop_position( Font* f, Image* pic, char* sequence, int index, int x ) {
	int i;
	int cur_width = 0;
	int halfway = calculate_width( f, sequence ) / 2; /* truncation is fine here */
	int far_left = x - halfway;

	for( i = 0; i < index; i++ ) {
		cur_width += get_width( f, sequence[i] );
	}
	
	return cur_width + far_left;
}

#endif
