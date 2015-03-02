PROJECT_NAME = Assignment4
MAIN = main.cpp
TEST = test.cpp
LIBRARIES = Combat.cpp Dice.cpp Character.cpp Player.cpp
SOURCES = $(MAIN) $(TEST) $(LIBRARIES)
HEADERS = Dice.h Character.h Flags.h Player.h
DOCS = CS162Assignment4.pdf instructions.txt

############
CC = g++
CFLAGS = -std=c++0x
#CFLAGS += Wall
#DEBUG = -g -pg
#CFLAGS += $(DEBUG) 
MAKEFLAGS += -k
ZIPFILE = $(PROJECT_NAME).zip

all: $(PROJECT_NAME) stat_test test instructions

$(PROJECT_NAME):$(MAIN) $(LIBRARIES) $(HEADERS)
	$(CC) $(CFLAGS) -o $@ $^

test:$(MAIN) $(LIBRARIES) $(HEADERS)
	$(CC) $(CFLAGS) -DTEST=true -o $@ $^

stat_test:$(TEST) $(LIBRARIES) $(HEADERS)
	$(CC) $(CFLAGS) -DTEST=true -DSTATISTICS=true -o $@ $^

instructions:
	cat instructions.txt

clean:
	rm -f $(PROJECT_NAME) *.o *~ test stat_test

zip: 
	zip $(ZIPFILE) $(SOURCES) $(HEADERS) $(DOCS) makefile

%:%.cpp
	$(CC) $(CFLAGS) -o $@ $<
