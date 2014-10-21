CC = g++
DEBUG = -g
CFLAGS = $(DEBUG) 
#CFLAGS += -Wall
PROGS = loop name randNum randNum2 strings
MAKEFLAGS += -k

all: $(PROGS)

%:%.cpp
	$(CC) $(CFLAGS) -o $@ $<

clean:
	rm -f $(PROGS) *.o *~
