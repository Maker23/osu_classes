CC = g++
DEBUG = -g
CFLAGS = $(DEBUG) 
#CFLAGS += -Wall
PROGS = arcade arcade2 echo finalist firelaws hailstone hello loop mpg name name_v1 numGuess randFun randFun2 randNum randNum2 recConvert recFun refFun retFun size sortFun strings test

MAKEFLAGS += -k

all: $(PROGS)

%:%.cpp
	$(CC) $(CFLAGS) -o $@ $<

clean:
	rm -f $(PROGS) *.o *~
