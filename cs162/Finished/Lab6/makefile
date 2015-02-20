PROJECT_NAME = Lab6
MAIN = main.cpp
TEST = 
LIBRARIES = 
SOURCES = $(MAIN) $(TEST) $(LIBRARIES)
HEADERS = 
DOCS =  DataFiles/*

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

clean:
	rm -f $(PROJECT_NAME) *.o *~ test Output_*.txt SelectSortOutput.?

zip: 
	zip $(ZIPFILE) $(SOURCES) $(HEADERS) $(DOCS) makefile

%:%.cpp
	$(CC) $(CFLAGS) -o $@ $<
