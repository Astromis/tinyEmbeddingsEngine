#include "word2vec.h"

int main(int argc, char* argv[])
{
    word2vecStandartInit(argv[1]);
    TrainModel();
    clear_mem();
    return 0;
}
