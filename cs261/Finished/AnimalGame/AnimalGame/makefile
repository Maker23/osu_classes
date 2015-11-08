MAKEFLAGS += -i

all: prog

prog: main.c parseFile.c structs.h
	gcc -g -Wall -std=c99 -o prog main.c parseFile.c

clean:	
	rm *.o
	rm prog
