all: determinant

determinant: determinant.o determinantFun.o
	gcc -g $^ -o $@ -lm -lSDL -lpthread -lSDL_gfx

.c.o:
	gcc -g -Wall -pedantic -std=c99 -c -D_REENTRANT $<

determinantFun.o: determinantFun.c determinantFun.h

determinant.o: determinant.c determinantFun.h determinant.h

clean:
	-rm determinantFun.o determinant.o determinant

