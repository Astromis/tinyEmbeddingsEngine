#ifndef _IEMBEDDINGMODEL_H
#define _IEMBEDDINGMODEL_H

#include <vector>
#include <string>
#include <Eigen/Dense>

/**
 * @breif An interface for various types of word embedding models
 */

class IEmbeddingModel
{
    public:
    virtual void GetVocab(std::vector<std::string> &vocabulary) = 0;
    virtual void GetEmbeddingMatrix(Eigen::MatrixXf &Embeddings) = 0;
    virtual void GetEmbeddingMatrix(std::vector<Eigen::VectorXf> &Embeddings) = 0;
};


#endif