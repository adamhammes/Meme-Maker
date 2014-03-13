#ifndef _MEME_FUNCTIONS_C_
#define _MEME_FUNCTIONS_C_

#include "meme_functions.h"

Place* name_place( Meme* meme, char* name ) {
	int i;

	for ( i = 0; i < meme->num_places; i++ ) {
			if( strcmp( meme->places[i].name, name ) == 0 )	return &meme->places[i] ;
	}

	return 0;
}


Place* get_place( Meme* meme, int index ) {
	return &meme->places[index];
}

int count_spaces( char* line ) {
	int spaces = 0, i = 1;
	int length = strlen( line );
	if( length <= 1 ) return 0;
	
	for(; i < length; i++ ) {
		if( isspace( line[i] && !isspace( line[i -1 ] ) ) ) spaces++;
	}

	return spaces;
}

Meme make_meme( char* name ) {
	Meme m;
	strcpy( m.name, name );
	m.num_places = 0;
	return m;
}

Font* get_font( Database* data, char* name ) {
	int i;

	for( i = 0; i < data->num_fonts; i++ ) {
		if( strcmp( data->fonts[i].name, name ) == 0 ) {
			return &data->fonts[i];
		}
	}

	return 0;
}


Meme* get_meme( Database* data, char* name ) {
	int i;
	for( i = 0; i < data->num_memes; i++ ) {
		if( strcmp( data->memes[i].name, name ) == 0 ) {
			return &data->memes[i];
		}
	}

	return 0;
}

void read_meme_file( Database* data, char* name ) {
	FILE* file = fopen( name, "r" );
	int num_memes, num_fonts, i, index;
	char* line = NULL;
	char* trim;
	char* word = NULL;
	size_t line_size;
	Meme* meme;
	Place* place;	


	if( file == 0 ) {
		printf("%s not found\n", name );
		exit(0);
	}
	
	getline( &line, &line_size, file );
	trim = no_whitespace( line );

	while( strcmp( line,  "" ) == 0 ) {
		getline(&line, &line_size, file );
		trim = no_whitespace( line );
	}
	/* count spaces so we know how many words there are */
	num_memes = count_spaces( trim ) + 1;
	/* now we know the number of memes, so we can properly allocate memory */
	data->memes = (Meme*)  malloc( num_memes * sizeof( Meme ) );
	data->num_memes = num_memes;

	index = strchr( trim, ':' ) - trim + 1; /* find where the words start */
	word = strtok( &trim[index], " " );
	strcpy( data->memes[0].name, word );
	data->memes[0] = make_meme( word );
	
	for( i = 1; i < num_memes; i++ ) {
		word = strtok( NULL, " " );
		data->memes[i] = make_meme( word );
	}
	free( line );
	line = NULL;

	while( getline( &line, &line_size, file ) != -1 ) {	/* while we haven't reached end of file */
		if( strcmp( line, "\n" ) == 0 ) { 
			continue;
		}

		trim = no_whitespace( line );	

		if( strncmp( trim, "FONT", 4 ) == 0 ) {
			data->num_fonts = count_spaces( trim ) + 1;
			data->fonts = malloc( sizeof( Font ) * data->num_fonts );
			
			index = strchr( trim, ':' ) - trim + 1;
			word = strtok( &trim[index], " " );
			data->fonts[0] = read_font_file( word );

			for( i = 1; i < num_fonts; i++ ) {
				data->fonts[i] = read_font_file( strtok( NULL, " " ) );
			}
		} else {
			word = strtok( trim, " :" ) ;
			meme = get_meme( data, word );
			
			word = strtok( NULL, " :" );
			if( strcmp( word, "FILE" ) == 0 ) { 
				meme->pic = read_in( strtok( NULL, " :" ) );
			} else {
				place = get_place( meme, meme->num_places++ );
				strcpy( place->name, word );
				place->x = atoi( strtok( NULL, " :" ) );
				place->y = atoi( strtok( NULL, " :" ) );
				place->has_text = 0;
			}
		}
		free( line );
		line = NULL;
	}
	fclose( file );
}

void free_database( Database* data ) {
	int i;
	for( i = 0; i < data->num_fonts; i++ ) { 
		free_font( &data->fonts[i] );
	}
	for( i = 0; i < data->num_memes; i++ ) { 
		close_image( &data->memes[i].pic );
	}
	free( data->fonts );
	free( data->memes );
}

#endif
