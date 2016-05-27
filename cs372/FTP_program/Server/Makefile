# Makefile for the socket programming example
#

ftserver_objects = ftserver.o

all : ftserver

ftserver: $(ftserver_objects)
	gcc -o ftserver $(ftserver_objects)

Socket: Socket.cpp
ServerSocket: ServerSocket.cpp
ClientSocket: ClientSocket.cpp
ftserver: ftserver.c

clean:
	rm -f *.o ftserver simple_client
