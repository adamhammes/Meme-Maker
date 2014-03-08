test: testing.o font_functions.o
	gcc -o testing testing.o image_functions.o pixel_functions.o font_functions.o -lm

testing.o : testing.c font_functions.o
	gcc -ansi -pedantic -c testing.c

structs : structs.h
	gcc -ansi -pedantic structs.h

overlay : overlay.o image_functions.o pixel_functions.o
	gcc -o overlay overlay.o image_functions.o pixel_functions.o -lm

overlay.o : overlay.c image_functions.o
	gcc -ansi -pedantic -c overlay.c

crop : crop.o image_functions.o pixel_functions.o
	gcc  -o crop crop.o image_functions.o pixel_functions.o -lm

crop.o : crop.c image_functions.o
	gcc -ansi -pedantic -c crop.c

image_functions.o : image_functions.h image_functions.c pixel_functions.o
	gcc -ansi -pedantic -c image_functions.c

pixel_functions.o : pixel_functions.c pixel_functions.c pixel.h
	gcc -ansi -pedantic -c pixel_functions.c

font_functions.o : font_functions.h font_functions.c image_functions.o structs.h
	gcc -ansi -pedantic -c font_functions.c

meme_functions.o : meme_functions.h meme_functions.c font_functions.o
	gcc -ansi -pedantic -c meme_functions.c
