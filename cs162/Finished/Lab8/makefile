PROJECT_NAME = Lab8
MAIN = main.cpp
TEST = test.cpp
LIBRARIES = Functions.cpp
HEADERS = Functions.h
DATA = 
DOCS =  CS162Lab8.pdf
SOURCES = $(MAIN) $(TEST) $(LIBRARIES) 
ZIPFILE = $(PROJECT_NAME).zip

############
CC = g++
CFLAGS = -std=c++0x
MAKEFLAGS += -k

all: $(PROJECT_NAME) test

test: $(TEST) $(LIBRARIES) $(HEADERS)
	$(CC) $(CFLAGS) -o $@ $^

$(PROJECT_NAME):$(MAIN) $(LIBRARIES) $(HEADERS)
	$(CC) $(CFLAGS) -o $@ $^

clean:
	rm -f $(PROJECT_NAME) *.o *~ test $(ZIPFILE)

zip: 
	zip $(ZIPFILE) $(SOURCES) $(HEADERS) $(DOCS) $(DATA) makefile

%:%.cpp
	$(CC) $(CFLAGS) -o $@ $<
