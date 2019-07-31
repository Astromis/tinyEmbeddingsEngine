#include "word2vec.hpp"
#include "EmbeddingStore.hpp"
#include "vpTree.hpp"
#include "math.h"
#include <vector>
#include <iostream>



int main(int argc, char* argv[])
{
    if(argc <= 1)
    {
        cout<<"Data file was not defined"<<endl;
        return 0;
    }

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
        vector<string> ans;
        vector<double> dists;
        storage.find_k_nierest(test, 3, ans, dists);
        for(auto i: ans)
        {
            cout<<i<<endl;
        }
    }

    return 0;
}
