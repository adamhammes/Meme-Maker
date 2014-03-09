#ifndef _STRUCTS_H_
#define _STRUCTS_H_

#include "image.h"

typedef struct font_s {
	Image base_image;
	int coords[256][4];
	Image letters[256];
	char name[100];
} Font;


typedef struct place_s {
	char name[100];
	char text[100];
	int x;
	int y;
	int has_text;
} Place;


typedef struct meme_s {
	char name[100];
	char file_name[100];
	Image pic;
	
	Place places[100];
	int num_places;	
} Meme;

typedef struct macro_s {
	Font* font;
	Meme* meme;
	char outfile[100];
} Macro;

typedef struct database_s {
	Font* fonts;
	int num_fonts;

	Meme* memes;
	int num_memes;
} Database;

#endif
