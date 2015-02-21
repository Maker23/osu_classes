PROJECT_NAME = Lab7
MAIN = main.cpp
LIBRARIES = File.cpp
HEADERS = File.h
DATA = buildFiles.cpp 
DOCS =  CS162Lab7.pdf
SOURCES = $(MAIN) $(TEST) $(LIBRARIES) 
ZIPFILE = $(PROJECT_NAME).zip

############
CC = g++
CFLAGS = -std=c++0x
MAKEFLAGS += -k

all: $(PROJECT_NAME) buildFiles

data: buildFiles
	mkdir -p DataFiles
	./buildFiles

buildFiles: $(DATA) $(LIBRARIES) $(HEADERS)
	$(CC) $(CFLAGS) -o $@ $^

$(PROJECT_NAME):$(MAIN) $(LIBRARIES) $(HEADERS)
	$(CC) $(CFLAGS) -o $@ $^

clean:
	rm -f $(PROJECT_NAME) *.o *~ buildFiles DataFiles/* $(ZIPFILE)

zip: 
	zip $(ZIPFILE) $(SOURCES) $(HEADERS) $(DOCS) $(DATA) makefile

%:%.cpp
	$(CC) $(CFLAGS) -o $@ $<
