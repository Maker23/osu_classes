PROJECT_NAME = FinalProject
MAIN = main.cpp
TEST = test.cpp
FUNCPTR = funtest.cpp
LIBRARIES = Room.cpp Container.cpp Thing.cpp BuildTheEnvironment.cpp
HEADERS = Room.h Container.h Thing.h
DATA = 
DOCS =  CS162FinalProject.pdf comments.txt
SOURCES = $(MAIN) $(TEST) $(LIBRARIES) 
ZIPFILE = $(PROJECT_NAME).zip

############
CC = g++
CFLAGS = -std=c++0x -O3
MAKEFLAGS += -k

all: $(PROJECT_NAME) test comments

funtest: $(FUNCPTR) $(LIBRARIES) $(HEADERS)
	$(CC) $(CFLAGS) -o $@ $^

test: $(TEST) $(LIBRARIES) $(HEADERS)
	$(CC) $(CFLAGS) -o $@ $^

$(PROJECT_NAME):$(MAIN) $(LIBRARIES) $(HEADERS)
	$(CC) $(CFLAGS) -o $@ $^

comments: 
	cat comments.txt

clean:
	rm -f $(PROJECT_NAME) *.o *~ test $(ZIPFILE)

zip: 
	zip $(ZIPFILE) $(SOURCES) $(HEADERS) $(DOCS) $(DATA) makefile

%:%.cpp
	$(CC) $(CFLAGS) -o $@ $<
