all: TowerOfHanoi

TowerOfHanoi: TowerOfHanoi.o primlib.o
	gcc -I/usr/include/SDL/ -g $^ -o $@ -lm -lSDL -lpthread -lSDL_gfx

.c.o: 
	gcc -I/usr/include/SDL/ -g -Wall -pedantic -std=c99 -c -D_REENTRANT $<

primlib.o: primlib.c primlib.h

TowerOfHanoi.o: TowerOfHanoi.c primlib.h

clean:
	-rm primlib.o TowerOfHanoi.o TowerOfHanoi
