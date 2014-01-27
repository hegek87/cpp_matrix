CC = g++
CFLAGS = -c -g -Wall -o
OBJECTS = bin/matrix.o bin/matmain.o

all: matrix
	
matrix: $(OBJECTS)
	$(CC) $(OBJECTS) -o bin/matrix
	
bin/matrix.o:
	$(CC) $(CFLAGS) bin/matrix.o matrix.cpp
	
bin/matmain.o:
	$(CC) $(CFLAGS) bin/matmain.o matmain.cpp
	
clean:
	rm -f ./bin/*
