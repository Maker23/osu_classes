CC = g++
CFLAGS = -Wall -std=c++0x -ftime-report
#DEBUG = -g -pg
#CFLAGS += $(DEBUG) 
MAKEFLAGS += -k
PROGS = lab1-1 lab1-2
ZIPFILE = archive.zip

all: $(PROGS)

clean:
	rm -f $(PROGS) *.o *~

zip: 
	zip $(ZIPFILE) *.cpp *.h makefile

lab1-1:lab1-1.cpp
	$(CC) $(CFLAGS) -o $@ $?

lab1-2:lab1-2.cpp g.cpp f.cpp
	$(CC) $(CFLAGS) -o $@ $?
