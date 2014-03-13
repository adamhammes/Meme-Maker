all: crop overlay meme

meme: meme.c meme.o meme_functions.o font_functions.o image_functions.o
	gcc -o meme meme.o meme_functions.o font_functions.o image_functions.o pixel_functions.o -lm

meme.o : meme.c meme_functions.o font_functions.o image_functions.o
	gcc -ansi -pedantic -c meme.c

font_functions.o : font_functions.h font_functions.c image_functions.o structs.h
	gcc -ansi -pedantic -c font_functions.c

meme_functions.o : meme_functions.h meme_functions.c font_functions.o
	gcc -ansi -pedantic -c meme_functions.c

tarball : crop overlay meme
	make clean
	tar czf hammesa.tar.gzip *.c *.h README makefile

clean : 
	rm -f *.o crop overlay meme

overlay : overlay.o image_functions.o pixel_functions.o
	gcc -o overlay overlay.o image_functions.o pixel_functions.o -lm

overlay.o : overlay.c image_functions.o
	gcc -ansi -pedantic -c overlay.c

crop : crop.o image_functions.o pixel_functions.o
	gcc  -o crop crop.o image_functions.o pixel_functions.o -lm

crop.o : crop.c image_functions.o
	gcc -ansi -pedantic -c crop.c

pixel_functions.o : pixel_functions.h pixel_functions.c pixel.h
	gcc -ansi -pedantic -c pixel_functions.c


image_functions.o : image_functions.c image_functions.c pixel_functions.o
	gcc -ansi -pedantic -c image_functions.c
