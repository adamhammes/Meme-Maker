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
