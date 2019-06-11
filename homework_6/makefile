all: linkedList

linkedList: linkedList.o linkedListFun.o
	gcc -g $^ -o $@ -lm -lSDL -lpthread -lSDL_gfx

.c.o:
	gcc -g -Wall -pedantic -std=c99 -c -D_REENTRANT $<

linkedListFun.o: linkedListFun.c linkedListFun.h

linkedList.o: linkedList.c linkedListFun.h

clean:
	-rm linkedListFun.o linkedList.o linkedList

