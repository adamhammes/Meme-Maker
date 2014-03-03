#include "image.h"

typedef struct font_s {
	Image base_image;
	Image letters[256];
	char* name;
} Font;

typedef struct meme_s {
	char* name;
	char* file_name;
	
	int top_x;
	int top_y;
	int bot_x;
	int bot_y;
} Meme;

typedef struct macro_s {
	Font* f;
	char* top_text;
	char* bot_test;
	Meme* m;
} Macro;

typedef struct database_s {
	Font* fonts;
	int num_fonts;

	Meme* memes;
	int num_memes;
} Database;
