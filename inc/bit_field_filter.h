#ifndef _BIT_FIELD_FILTER_H_
#define _BIT_FIELD_FILTER_H_

#include <stdint.h>

using namespace std;
class photo_filter{
public:
    photo_filter();
    // void bitfield_filter(int **pixels, int w, int h, int8_t option);
    // void bitfield_filter(int ***pixels, int w, int h, int8_t option);
// private:
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