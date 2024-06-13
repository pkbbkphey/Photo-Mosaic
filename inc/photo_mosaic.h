#ifndef _PHOTO_MOSAIC_H_
#define _PHOTO_MOSAIC_H_

#include "rgb_image.h"
#include "image.h"
using namespace std;

// #define tileWNum 100    // how many tiles are in the same row (horizontal count)
#define tileSize 32     // the width and height of pixels in the original photo

class PhotoMosaic{
public:
    RGBImage *generate(string tilePath, string orignPath);
};

#endif