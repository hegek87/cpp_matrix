all:
	g++ -c -g -Wall matmain.cpp
	g++ -c -g -Wall matrix.cpp
	g++ -o matrix matrix.cpp matmain.cpp
	
	mv *.o matrix bin
