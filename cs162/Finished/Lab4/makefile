PROJECT_NAME = Lab4
SOURCES = main.cpp Dice.cpp
HEADERS = Dice.h
DOCS = CS162Lab4.pdf

CC = g++
CFLAGS = -std=c++0x
#CFLAGS += Wall
#DEBUG = -g -pg
#CFLAGS += $(DEBUG) 
MAKEFLAGS += -k
ZIPFILE = $(PROJECT_NAME).zip

all: $(PROJECT_NAME)

clean:
	rm -f $(PROJECT_NAME) *.o *~

test: $(PROJECT_NAME)
	./$(PROJECT_NAME)

zip: 
	zip $(ZIPFILE) $(SOURCES) $(HEADERS) $(DOCS) makefile

$(PROJECT_NAME):$(SOURCES) $(HEADERS)
	$(CC) $(CFLAGS) -o $@ $^

%:%.cpp
	$(CC) $(CFLAGS) -o $@ $<
