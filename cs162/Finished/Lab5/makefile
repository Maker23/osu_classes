PROJECT_NAME = Lab5
MAIN = main.cpp
TEST = test.cpp
LIBRARIES = Filter.cpp
SOURCES = $(MAIN) $(TEST) $(LIBRARIES)
HEADERS = Filter.h
DOCS = CS162Lab5.pdf

############
CC = g++
CFLAGS = -std=c++0x
#CFLAGS += Wall
#DEBUG = -g -pg
#CFLAGS += $(DEBUG) 
MAKEFLAGS += -k
ZIPFILE = $(PROJECT_NAME).zip

all: $(PROJECT_NAME)

$(PROJECT_NAME):$(MAIN) $(LIBRARIES) $(HEADERS)
	$(CC) $(CFLAGS) -o $@ $^

test: $(TEST) $(LIBRARIES) $(HEADERS)
	$(CC) $(CFLAGS) -o $@ $^
	./test

clean:
	rm -f $(PROJECT_NAME) *.o *~ test Output_*.txt

zip: 
	zip $(ZIPFILE) $(SOURCES) $(HEADERS) $(DOCS) makefile

%:%.cpp
	$(CC) $(CFLAGS) -o $@ $<
