all: prog

prog: dynArray.o stackapp.o
	gcc -g -Wall -std=c99 -o prog dynArray.o stackapp.o

stackapp.o: stackapp.c dynArray.h
	gcc -g -Wall -std=c99 -c stackapp.c

dynArray.o: dynamicArray.c dynArray.h 
	gcc -g -Wall -std=c99 -c dynamicArray.c	-o dynArray.o
		
clean:
	rm dynArray.o
	rm stackapp.o
	rm prog
