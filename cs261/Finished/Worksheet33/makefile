all: prog

ws33: ws33.c dynArray.h dynArray.c
	gcc -g -Wall -std=c99 -o prog ws33.c dynArray.c 

compare.o: compare.c dynArray.h
	gcc -g -Wall -std=c99 -c compare.c
		
clean:	
	rm ws33.o
	rm compare.o
	rm prog
