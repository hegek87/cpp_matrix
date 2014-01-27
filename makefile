CC = g++
CFLAGS = -c -g -Wall -o
OBJECTS = bin/matrix.o bin/matmain.o

all: bin/matrix
	
bin/matrix: $(OBJECTS)
	$(CC) $(OBJECTS) -o bin/matrix -lUnitTest++
	
bin/matrix.o: matrix.cpp
	$(CC) $(CFLAGS) bin/matrix.o matrix.cpp
	
bin/matmain.o: matmain.cpp
	$(CC) $(CFLAGS) bin/matmain.o matmain.cpp
	
clean:
	rm -f ./bin/*
