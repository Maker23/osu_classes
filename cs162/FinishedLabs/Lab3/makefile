PROJECT_NAME = Lab3
SOURCES = Lab3.cpp
INPUT_DATA = infile.one infile.two
OUTPUT_FILE = outfile

CC = g++
CFLAGS = -std=c++0x
#CFLAGS += Wall
#DEBUG = -g -pg
#CFLAGS += $(DEBUG) 
MAKEFLAGS += -k
ZIPFILE = $(PROJECT_NAME).zip


all: $(PROJECT_NAME)

clean:
	rm -f $(PROJECT_NAME) *.o *~ $(OUTPUT_FILE)

test: $(PROJECT_NAME)
	$(PROJECT_NAME) $(INPUT_DATA) $(OUTPUT_FILE)

zip: 
	zip $(ZIPFILE) $(SOURCES) $(INPUT_DATA) makefile

$(PROJECT_NAME):$(SOURCES) $(INPUT_DATA)
	$(CC) $(CFLAGS) -o $@ $<

infile.one:
	/bin/echo -e '3\n4\n5\n6\n6\n6 7 8\n9' > infile.one

infile.two:
	/bin/echo -e "-1\nbad\n6\n\n10\n11\n13.0" > infile.two

%:%.cpp
	$(CC) $(CFLAGS) -o $@ $<
