#ifndef _EMBEDDINGSTORE_H
#define _EMBEDDINGSTORE_H

#include <Eigen/Dense>
#include <Eigen/Core>
#include "word2vec.hpp"
#include <vector>
#include <string>
#include <iostream>
#include <fstream>
#include "IEmbeddingModel.hpp"


using namespace std;
using namespace Eigen;

class EmbeddingStore
{
    private:
        //Am I sure that here should be a vector?
        vector<string> vocab;
        MatrixXf Embeddings;

    public:

    EmbeddingStore();
    ~EmbeddingStore();
    EmbeddingStore(IEmbeddingModel &model);
    MatrixXd readMatrix(const char *filename);
    void writeMatrix(const char *filename, MatrixXd mat);


    float similarity();
    string find_nierest();
};

#endif