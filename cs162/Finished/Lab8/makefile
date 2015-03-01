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
MAKEFLAGS += -k -s

all: $(PROJECT_NAME) test comments

test: $(TEST) $(LIBRARIES) $(HEADERS)
	echo $(CC) $(CFLAGS) -o $@ $^
	$(CC) $(CFLAGS) -o $@ $^

$(PROJECT_NAME):$(MAIN) $(LIBRARIES) $(HEADERS)
	echo $(CC) $(CFLAGS) -o $@ $^
	$(CC) $(CFLAGS) -o $@ $^

comments: 
	echo ""
	echo "  Run  ./Lab8  to try the maze program."
	echo "  Run  ./test  to do the automated tests."
	echo "  The map of the maze, along with information about the test method,"
	echo "  can be found in the pdf document."
	echo "  Thx Jan!"
	echo ""

clean:
	echo rm -f $(PROJECT_NAME) *.o *~ test $(ZIPFILE)
	rm -f $(PROJECT_NAME) *.o *~ test $(ZIPFILE)

zip: 
	echo zip $(ZIPFILE) $(SOURCES) $(HEADERS) $(DOCS) $(DATA) makefile
	zip $(ZIPFILE) $(SOURCES) $(HEADERS) $(DOCS) $(DATA) makefile

%:%.cpp
	$(CC) $(CFLAGS) -o $@ $<
