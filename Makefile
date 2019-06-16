all: w2v

w2v: w2v.o main.o EmbeddingStore.o
	g++ w2v.o main.o EmbeddingStore.o -lpthread -o w2v -std=c++11 -g

w2v.o: word2vec.cpp
	g++ word2vec.cpp -c -I /usr/include/eigen3/ -o w2v.o -std=c++11 -g

EmbeddingStore.o: EmbeddingStore.cpp
	g++ EmbeddingStore.cpp -c -I /usr/include/eigen3/ -o EmbeddingStore.o -g -std=c++11

main.o: main.cpp
	g++ main.cpp -c -I /usr/include/eigen3/ -o main.o -std=c++11 -g

clean:
	rm -rf *.o w2v
