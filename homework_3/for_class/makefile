
all: testlib

testlib: testlib.o primlib.o
	/opt/boundschecking-gcc/bin/gcc -fbounds-checking -g $^ -o $@ -lm -lSDL -lpthread -lSDL_gfx

.c.o: 
	/opt/boundschecking-gcc/bin/gcc -I /opt/boundschecking-gcc/include -fbounds-checking -g -Wall -pedantic -std=c99 -c -D_REENTRANT $<

primlib.o: primlib.c primlib.h

testlib.o: testlib.c primlib.h

clean:
	-rm primlib.o testlib.o testlib
