# tinyEmbeddingsEngine
This engine provides the methods to deal with semantic word vectors. Basicly, it is a storage for the embedding matrix and the related vocabulary. It can
* find similar word fast 
* compute the cosine similarity 
* produce embeddings for more complicated structure of text (not tested yet). 

Basic usage:


```cpp
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
    // Create storage from embeddings
    EmbeddingStore storage(model);
    string test;

    cout<<"Enter the word for search: ";
    cin>>test;
    vector<string> ans;
    vector<double> dists;
    // search the nearist word
    cout<<storage.find_nierest("England")
    // perform searching of k nearist neigbours
    storage.find_k_nierest(test, 3, ans, dists);
    for(auto i: ans)
    {
        cout<<i<<endl;
    }

    return 0;
}


```
It will be included in search engine.
