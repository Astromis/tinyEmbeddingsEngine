all: w2v

w2v: w2v.o main.o
	g++ w2v.o main.o -lpthread -o w2v

w2v.o: word2vec.cpp
	g++ word2vec.cpp -c -I /usr/include/eigen3/ -o w2v.o
	
main.o: main.cpp
	g++ main.cpp -c -I /usr/include/eigen3/ -o main.o
