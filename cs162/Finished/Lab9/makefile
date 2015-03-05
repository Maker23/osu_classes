PROJECT_NAME = Lab9
MAIN = main.cpp
TEST = test.cpp
LIBRARIES =
HEADERS = Node.h Queue.h Stack.h 
DATA = 
DOCS = comments.txt QueueFunc.h StackFunc.h
SOURCES = $(MAIN) $(TEST) $(LIBRARIES) 
ZIPFILE = $(PROJECT_NAME).zip

############
CC = g++
CFLAGS = -std=c++0x
MAKEFLAGS += -k -s

all: $(PROJECT_NAME) test comments

test: $(TEST) $(LIBRARIES) $(HEADERS)
	echo $(CC) $(CFLAGS) -o $@ $^
	$(CC) $(CFLAGS) -o $@ $^

$(PROJECT_NAME):$(MAIN) $(LIBRARIES) $(HEADERS)
	echo $(CC) $(CFLAGS) -o $@ $^
	$(CC) $(CFLAGS) -o $@ $^

comments: 
	cat comments.txt

clean:
	echo rm -f $(PROJECT_NAME) *.o *~ test $(ZIPFILE)
	rm -f $(PROJECT_NAME) *.o *~ test $(ZIPFILE)

zip: 
	echo zip $(ZIPFILE) $(SOURCES) $(HEADERS) $(DOCS) $(DATA) makefile
	zip $(ZIPFILE) $(SOURCES) $(HEADERS) $(DOCS) $(DATA) makefile

%:%.cpp
	$(CC) $(CFLAGS) -o $@ $<
