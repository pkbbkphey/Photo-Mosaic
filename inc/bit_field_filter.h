#ifndef _BIT_FIELD_FILTER_H_
#define _BIT_FIELD_FILTER_H_

#include <stdint.h>

using namespace std;
class photo_filter{
public:
    photo_filter();
    void apply(int **pixels, int w, int h, int8_t option);
    void apply(int ***pixels, int w, int h, int8_t option);
    void apply_order(int **pixels, int w, int h, int order);
    void apply_order(int ***pixels, int w, int h, int order);
    enum option {
        BOX         = 0b00000001,
        SOBEL       = 0b00000010,
        CONTRAST    = 0b00000100,
        MOSAIC      = 0b00001000,
        MEDIAN      = 0b00010000
    };
    void applyAnisotropicDiffusion(int** pixels, int w, int h, int iterations, double lambda, double kappa);
// private:     // Not setting these filters to private because some other algorithms use these filters
    // void gray_filter(int **pixels, int w, int h);
    void applyBoxFilter(int **pixels, int w, int h);
    void applySobelGradient(int **pixels, int w, int h);
    void applyContrastStretching(int **pixels, int w, int h);
    void applyMosaicFilter(int **pixels, int w, int h, int blockSize);
    void applyMedianFilter(int **pixels, int w, int h);
    // void rgb_filter(int ***pixels, int w, int h);
    void applyBoxFilter(int ***pixels, int w, int h);
    void applySobelGradient(int ***pixels, int w, int h);
    void applyContrastStretching(int ***pixels, int w, int h);
    void applyMosaicFilter(int ***pixels, int w, int h, int blockSize);
    void applyMedianFilter(int ***pixels, int w, int h);
};

#endif