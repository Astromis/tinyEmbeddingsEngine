CC=g++
CFLAGS=-c -Wall -std=c++11

all: matrix

matrix: main.o
	$(CC) main.o -std=c++11 -o matrix
	
main.o: main.cpp
	$(CC) $(CFLAGS) main.cpp -I /usr/local/include/eigen3/
	
clean:
	rm -rf *.o matrix
