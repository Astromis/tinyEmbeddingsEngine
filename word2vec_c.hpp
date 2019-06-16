
#define MAX_STRING 100
#define EXP_TABLE_SIZE 1000
#define MAX_EXP 6
#define MAX_SENTENCE_LENGTH 1000
#define MAX_CODE_LENGTH 40

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <pthread.h>
#include <Eigen/Dense>
#include <Eigen/Core>
#include <iostream>
#include <thread>
#include <vector>

using namespace Eigen;
using namespace std;

//typedef float real;

struct vocab_word {
  long long cn;
  int *point;
  char *word, *code, codelen;
};


class Word2Vec
{
    private:

        // internal parameters
        const int vocab_hash_size = 30000000;  // Maximum 30 * 0.7 = 21M words in the vocabulary
        int *vocab_hash;
        float starting_alpha;
        struct vocab_word *vocab;
        const int table_size = 1e8;
        int *table;
        float *syn0, *syn1, *syn1neg, *expTable;
        clock_t start;
        bool read_vocab_flag;

        //adjustable params
        char train_file[MAX_STRING];
        int cbow = 1, debug_mode = 2, window = 5, min_count = 5, num_threads = 12, min_reduce = 1;
        long long vocab_max_size = 1000, vocab_size = 0, layer1_size = 16;
        long long train_words = 0, word_count_actual = 0, iter = 1, file_size = 0, classes = 0;
        float alpha = 0.025, sample = 1e-3;
        int hs = 0, negative = 5;

    public:
        Word2Vec(char* _train_file);
        ~Word2Vec();
        //native functions
        int AddWordToVocab(char *word);
        int ArgPos(char* str,int argc, char** argv);
        void CreateBinaryTree();
        void InitNet();
        void InitUnigramTable();
        void LearnVocabFromTrainFile();
        void ReadWord(char* word,FILE* fin);
        int ReadWordIndex(FILE* fin);
        void ReduceVocab();
        int GetWordHash(char *word);
        int SearchVocab(char* word);
        void SortVocab();
        //void *TrainModelThread(void* id);
        void TrainModelThread(int id);
        friend int VocabCompare(const void*a, const void* b);

        
        void clear_mem();
        void word2vecStandartInit();    
        //modified function
        MatrixXf TrainModel();
        void SaveVocab(char * save_vocab_file);
        void ReadVocab(char * read_vocab_file);




};

