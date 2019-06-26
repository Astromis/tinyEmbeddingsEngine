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
#include "vpTree.hpp"
#include "math.h"
#include <unordered_map>


using namespace std;
using namespace Eigen;



class EmbeddingStore
{
    private:
        static double eucl_dist(const VectorXf& a, const VectorXf& b)
        {
            double dist = 0 ;
            for(int i = 0; i < a.size(); i++)
                dist += pow( a[i] - b[i],2);
            return sqrt(dist);
        }
        static double cosine_dist(const VectorXf& a, const VectorXf& b)
        {
            double dot = 0, norm_1 = 0, norm_2 = 0;
            for(int i = 0; i < a.size(); i++)
            {
                dot += a[i] * b[i];
                norm_1 += pow(a[i], 2);
                norm_2 += pow(b[i], 2);
            }

            return dot / (sqrt(norm_1)* sqrt(norm_2) );
        } 
        //Am I sure that here should be a vector?
        vector<string> vocab;
        vector<VectorXf> vectors;
        //unordered_map<string, VectorXf> w2v;
        //unordered_map<VectorXf, string> v2w;
        MatrixXf Embeddings;
        VpTree<VectorXf, eucl_dist> EmbeddingTree;

  
    public:

    EmbeddingStore();
    ~EmbeddingStore();
    EmbeddingStore(IEmbeddingModel &model);
    MatrixXd readMatrix(const char *filename);
    void writeMatrix(const char *filename, MatrixXd mat);
    void find_k_nierest(string word, int k, 
                       vector<string>& results, vector<double>& dists);

    void dbscan(float eps, int minPts);
    float similarity();
    string find_nierest(string word);
};

#endif