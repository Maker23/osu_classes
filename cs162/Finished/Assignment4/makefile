PROJECT_NAME = Assignment4
MAIN = main.cpp
TEST = test.cpp
LIBRARIES = Combat.cpp Dice.cpp Character.cpp Player.cpp
SOURCES = $(MAIN) $(TEST) $(LIBRARIES)
HEADERS = Dice.h Character.h Flags.h Player.h
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

$(PROJECT_NAME):$(MAIN) $(LIBRARIES) $(HEADERS)
	$(CC) $(CFLAGS) -o $@ $^

test:$(TEST) $(LIBRARIES) $(HEADERS)
	$(CC) $(CFLAGS) -DTEST=true -o $@ $^

clean:
	rm -f $(PROJECT_NAME) *.o *~ test Output_*.txt $(PROJECT_NAME).test

zip: 
	zip $(ZIPFILE) $(SOURCES) $(HEADERS) $(DOCS) makefile

%:%.cpp
	$(CC) $(CFLAGS) -o $@ $<
