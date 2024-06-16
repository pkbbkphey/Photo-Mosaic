#ifndef _SCREEN_H_
#define _SCREEN_H_

#include "data_loader.h"

class Screen_{
private:
    static Data_Loader imagefile;
public:
    void displayParallel(int **pixels1, int w1, int h1, int **pixels2, int w2, int h2);
    void displayParallel(int ***pixels1, int w1, int h1, int ***pixels2, int w2, int h2);
    void displayParallel(int ***pixels1, int w1, int h1, int ***pixels2, int** alpha2, int w2, int h2);
    void displayParallel(int ***pixels1, int **alpha1, int w1, int h1, int ***pixels2, int** alpha2, int w2, int h2);
};

#endif