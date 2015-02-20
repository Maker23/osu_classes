PROJECT_NAME = Assignment3
MAIN = 
TEST = test.cpp
LIBRARIES = Dice.cpp Character.cpp
SOURCES = $(MAIN) $(TEST) $(LIBRARIES)
HEADERS = Dice.h Character.h Flags.h
DOCS = CS162Assignment3.pdf

############
CC = g++
CFLAGS = -std=c++0x
#CFLAGS += Wall
#DEBUG = -g -pg
#CFLAGS += $(DEBUG) 
MAKEFLAGS += -k
ZIPFILE = $(PROJECT_NAME).zip

all: $(PROJECT_NAME)

$(PROJECT_NAME):$(TEST) $(LIBRARIES) $(HEADERS)
	$(CC) $(CFLAGS) -o $@ $^

$(PROJECT_NAME).test:$(TEST) $(LIBRARIES) $(HEADERS)
	$(CC) $(CFLAGS) -DTEST=true -o $@ $^

test: $(PROJECT_NAME).test
	./$(PROJECT_NAME).test

clean:
	rm -f $(PROJECT_NAME) *.o *~ test Output_*.txt $(PROJECT_NAME).test

zip: 
	zip $(ZIPFILE) $(SOURCES) $(HEADERS) $(DOCS) makefile

%:%.cpp
	$(CC) $(CFLAGS) -o $@ $<
