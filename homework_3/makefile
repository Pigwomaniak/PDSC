all: tetris

tetris: tetris.o primlib.o
	gcc -I/usr/include/SDL/ -fsanitize=address -g $^ -o $@ -lm -lSDL -lpthread -lSDL_gfx

.c.o: 
	gcc -I/usr/include/SDL/ -fsanitize=address -g -Wall -pedantic -std=c99 -c -D_REENTRANT $<

primlib.o: primlib.c primlib.h

tetris.o: tetris.c primlib.h

clean:
	-rm primlib.o tetris.o tetris
