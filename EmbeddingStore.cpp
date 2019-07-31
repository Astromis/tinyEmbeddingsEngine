#include "EmbeddingStore.hpp"
#include <algorithm>




EmbeddingStore::EmbeddingStore(IEmbeddingModel &model)
{
    model.GetVocab(vocab);
    model.GetEmbeddingMatrix(vectors);

    EmbeddingTree.create(vectors);

    for(int i=0; i < vocab.size(); i++)
    {
        word2index[vocab[i]] = i;
    }
    //model.GetEmbeddingMatrix(Embeddings);
};

EmbeddingStore::~EmbeddingStore()
{

}

/**
 * @brief find the nierest word
 * word [in] word the neighbour to be founded
 * @return the nierest word 
 */
string EmbeddingStore::find_nierest(string word)
{

    // I'm not sure that the distance is faster than linear search
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

/**
 * @brief find k the nierest words
 * word [in] word the neighbour to be founded
 * k [in] the number of neighbours
 * results [out] vector with the nierest words
 * dists [out] vecotr with distances from word to its neighbours
 *  
 */
void EmbeddingStore::find_k_nierest(string word, int k, 
                                    vector<string>& results, vector<double>& dists)
{

    // I'm not sure that the distance is faster than linear search
    int vocab_index = std::distance(vocab.begin(),
                                    find(vocab.begin(), vocab.end(), word));
    // don't forget to handle the mismatch
    cout<<vocab_index<<endl;
    vector<VectorXf> res;
    EmbeddingTree.search(vectors[vocab_index], k, &res, &dists);
    for(int i=1; i < k; i++)
    {
        int vector_index = std::distance(vectors.begin(),
                                        find(vectors.begin(), vectors.end(), res[i]));
        results.push_back(vocab[vector_index]);
    }   
}

void EmbeddingStore::dbscan(float eps, int minPts)
{
    int cluster_num = 0;
    for(auto word_vector: vectors)
    {
        
    }
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


VectorXf EmbeddingStore::operator[](string word)
{
    int idx = word2index[word];
    return vectors[idx];
}

/**
 * @brief Compute the SIF embeddings for piece of text (sentence, in general)
 * sentence [in] sentence to which embedding need to compute
 * wf [in] term frequency table
 * alpga [in] hyperparameter of smoothing, typicall range is [3e-5, 3e-3]
 * @return vector of piece of text 
 */
VectorXf EmbeddingStore::get_sif(string sentence, map<string, int> tf, float alpha)
{
    // this method need to be optimzed
    vector<string> result;
    istringstream iss(sentence);
    for(string s; iss >> s; )
        result.push_back(s);
    vector<VectorXf> vects;
    VectorXf res;
    for(string s:result)
    {
        vects.push_back(vectors[ word2index[s] ] * ((float)alpha / ( (float)alpha + tf[s]) ));
    }
    res = vects[vects.size()];
    vects.pop_back();
    for(int i=0; i< vects.size(); i++) res = res + vects[i];

    res = res / (vects.size() + 1);
    return res;
}