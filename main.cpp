#include "word2vec.hpp"
#include "EmbeddingStore.hpp"
#include "vpTree.hpp"
#include "math.h"
#include <vector>
#include <iostream>



int main(int argc, char* argv[])
{
    Word2Vec model(argv[1]);
    model.TrainModel();
    cout<<"Constructing the embedding table..."<<endl;
    EmbeddingStore storage(model);
    //model.clear_mem();
    string test;
    while(1)
    {
        cout<<"Enter the word for search: ";
        cin>>test;
        cout<<storage.find_nierest(test);
    }
    return 0;
}
