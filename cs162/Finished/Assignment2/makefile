PROJECT_NAME = ShoppingList
MAIN = main.cpp
TEST = test.cpp
LIBRARIES = List.cpp Item.cpp validateNumericInput.cpp
SOURCES = $(MAIN) $(LIBRARIES)
HEADERS = Item.h List.h validateNumericInput.h
DOCS = CS162Assignment2.pdf
DATA = myList.data myListTest.data


CC = g++
CFLAGS = -std=c++0x
#CFLAGS += Wall
#DEBUG = -g -pg
#CFLAGS += $(DEBUG) 
MAKEFLAGS += -k
ZIPFILE = $(PROJECT_NAME).zip


all: $(PROJECT_NAME)

$(PROJECT_NAME):$(SOURCES) $(HEADERS)
	$(CC) $(CFLAGS) -o $@ $(SOURCES)

test: $(TEST) $(LIBRARIES)
	$(CC) $(CFLAGS) -o $@ $(LIBRARIES) test.cpp
	./test

clean:
	rm -f $(PROJECT_NAME) test *.o *~

zip: 
	zip $(ZIPFILE) $(SOURCES) $(HEADERS) $(TEST) $(DATA) $(DOCS) makefile

%:%.cpp
	$(CC) $(CFLAGS) -o $@ $<
