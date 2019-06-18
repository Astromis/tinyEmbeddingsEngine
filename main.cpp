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
    EmbeddingStore store(model);

    return 0;
}
