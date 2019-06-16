//#include "word2vec.h"
#include "word2vec.hpp"
#include "EmbeddingStore.hpp"

int main(int argc, char* argv[])
{
    //word2vecStandartInit(argv[1]);
    //TrainModel();
    //clear_mem();
    Word2Vec model(argv[1]);
    model.TrainModel();
    EmbeddingStore store(model);
    
    return 0;
}
