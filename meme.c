#include "meme_functions.h"


int main( int argc, char** argv ) {
	Database* d = malloc( sizeof( Database ) );
	FILE* file = fopen( argv[2], "r" );
	char* line = NULL;
	char* word = NULL;
	size_t size = 0;
	int i, j;
	Macro* macro = malloc( sizeof( Macro ) );
	Place* place;
	
	read_meme_file( d, argv[1] );

	while( getline( &line, &size, file ) != -1 ) {	
		if( strcmp( line, "\n" ) == 0 ) {	
			continue;
		}
		no_whitespace( line );
			

		word = strtok( line, " :" );

		if( strcmp( word, "" ) == 0 ) {
			continue;
		} else if( strcmp( word, "OUTFILE" ) == 0 ) {
			strcpy( macro->outfile, strtok( NULL, " :" ) );
		} else if( strcmp( word, "MEME" ) == 0 ) {
			word = strtok( NULL, " :" );
			macro->meme = get_meme( d, word );
		} else if( strcmp( word, "FONT" ) == 0 ) {
			macro->font = get_font( d, strtok( NULL, " :" ) );
		} else {
			place = name_place( macro->meme, word );
			strcpy( place->text, (char*) &line[ strlen( word ) + 1 ] );
			place->has_text = 1;
		}
	}

	for( i = 0; i < macro->meme->num_places; i++ ) {
		if( macro->meme->places[i].has_text == 1 ) {
			place = &macro->meme->places[i];
			for( j = 0; j < strlen( place->text ); j++ ) {
				macro->meme->pic = make_one(	&macro->meme->pic,
												&macro->font->letters[ place->text[j] ],
												crop_position(	macro->font,
																&macro->meme->pic,
																place->text,
																j,
																place->x ),
												place->y - macro->font->letters[ place->text[j] ].height );
			}
		}
	}
	write_file( &macro->meme->pic, macro->outfile );
	
	free( macro );
	free_database( d );
	free( d );

	fclose( file );

	return 0;
}
