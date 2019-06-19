#include "EmbeddingStore.hpp"
#include <algorithm>




EmbeddingStore::EmbeddingStore(IEmbeddingModel &model)
{
    model.GetVocab(vocab);
    
    model.GetEmbeddingMatrix(vectors);
/*     for(int i=0; i < vectors.size(); i++)
    {
        w2v[vocab[i]] = vectors[i];
    }

    for(int i=0; i < vectors.size(); i++)
    {
        v2w[vectors[i]] = vocab[i];
    } */

    EmbeddingTree.create(vectors);
    //model.GetEmbeddingMatrix(Embeddings);
};

EmbeddingStore::~EmbeddingStore()
{

}

string EmbeddingStore::find_nierest(string word)
{
    /* cout<<vocab.size()<<endl;
    for(auto& i:vocab)
    {
        cout<<i<<endl;
    } */

    int vocab_index = std::distance(vocab.begin(),
                                    find(vocab.begin(), vocab.end(), word));
    // don't forget to handle the mismatch
    cout<<vocab_index<<endl;
    vector<VectorXf> res;
    std::vector<double> dists;
    EmbeddingTree.search(vectors[vocab_index], 2, &res, &dists);
    int vector_index = std::distance(vectors.begin(),
                                    find(vectors.begin(), vectors.end(), res[1]));

    return vocab[vector_index];
}


MatrixXd EmbeddingStore::readMatrix(const char *filename)
{
    std::ifstream indata;

    indata.open(filename);

    std::string line;
    getline(indata, line);
    std::stringstream lineStream(line);
    std::string cell;
    int count = 0, raw, coll;
    while (std::getline(lineStream, cell, ','))
    {
        if(count == 0) raw = stoi(cell);
        else coll = stoi( cell );
        count++;
    }
    MatrixXd res(raw,coll);
    cout<<"Matrix has been created"<<endl;
    raw = 0; coll = 0;
    while (getline(indata, line))
    {
    
        std::stringstream lineStream(line);
        std::string cell;

        while (std::getline(lineStream, cell, ','))
        {           
            res(raw,coll) = stof(cell);
            coll++;
        }
        coll = 0;
        raw++;
    }
    indata.close();
    return res;
};

//TODO:
//Saving type of matrix
void EmbeddingStore::writeMatrix(const char *filename, MatrixXd mat)
{
    ofstream outdata(filename,ios_base::out);
    int raws = mat.rows();
    int cols = mat.cols();
    outdata<<raws<<","<<cols<<endl;
    for(int i = 0; i< raws; i++)
    {
        for(int j = 0; j < cols-1; j++)
        {
            outdata<<mat(i,j)<<",";
        }
        outdata<<mat(i,cols-1)<<endl;
    }
    outdata.close();
    
}

