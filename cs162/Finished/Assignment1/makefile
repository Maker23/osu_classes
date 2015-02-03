PROJECT_NAME = Life
SOURCES = Life.cpp validateIntegerInput.cpp LifeForms.cpp
HEADERS = validateIntegerInput.h LifeForms.h

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

zip: 
	zip $(ZIPFILE) $(SOURCES) $(HEADERS) makefile

$(PROJECT_NAME):$(SOURCES) $(HEADERS)
	$(CC) $(CFLAGS) -o $@ $(SOURCES)

%:%.cpp
	$(CC) $(CFLAGS) -o $@ $<
