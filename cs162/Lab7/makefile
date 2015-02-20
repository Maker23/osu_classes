PROJECT_NAME = Lab7
MAIN = main.cpp
TEST = 
LIBRARIES = File.cpp
SOURCES = $(MAIN) $(TEST) $(LIBRARIES) 
DATA = buildFiles.cpp 
HEADERS = File.h
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

data: buildFiles
	./buildFiles

buildFiles: $(DATA) $(LIBRARIES) $(HEADER)
	$(CC) $(CFLAGS) -o $@ $^

$(PROJECT_NAME):$(MAIN) $(LIBRARIES) $(HEADERS)
	$(CC) $(CFLAGS) -o $@ $^

clean:
	rm -f $(PROJECT_NAME) *.o *~ test Output_*.txt SelectSortOutput.?

zip: 
	zip $(ZIPFILE) $(SOURCES) $(HEADERS) $(DOCS) makefile

%:%.cpp
	$(CC) $(CFLAGS) -o $@ $<
