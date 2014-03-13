#include "meme_functions.h"


int main( int argc, char** argv ) {
	Database* d = malloc( sizeof( Database ) );
	FILE* file;
	char* line = NULL;
	char* word = NULL;
	char* trim;
	size_t size = 0;
	int i, j;
	Macro* macro = malloc( sizeof( Macro ) );
	Place* place;

	if( argc != 3 ) {
		printf("Invalid number of arguments");
		exit(0);
	}
	
	file = fopen( argv[2], "r" );
	if( file == 0 ) {
		printf("%s not found.\n", argv[2] );
		exit(0);
	}
	
	read_meme_file( d, argv[1] );
	while( getline( &line, &size, file ) != -1 ) {	
		if( strcmp( line, "\n" ) == 0 ) {	
			continue;
		}
		
		trim = no_whitespace( line );
		
		word = strtok( trim, " :" );

		if( strcmp( word, "" ) == 0 ) {
			continue;
		} else if( strcmp( word, "OUTFILE" ) == 0 ) {
			strcpy( macro->outfile, strtok( NULL, " :" ) );
		} else if( strcmp( word, "MEME" ) == 0 ) {
			macro->meme = get_meme( d, strtok( NULL, " :" ) );
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
				if( macro->font->coords[ place->text[j] ][3] == 0 ) {
					printf("Letter \"%c\" not found.\n", place->text[j]); 
					exit(0);
				}
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
