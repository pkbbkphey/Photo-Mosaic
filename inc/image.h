#ifndef _IMAGE_H_
#define _IMAGE_H_

#include "data_loader.h"
using namespace std;

class Image{
protected:
    int width, height;
    string fname; // store filename for Display_CMD()
    static Data_Loader imagefile;
public:
    Image(int width, int height);
    ~Image();
    virtual bool LoadImage(string filename);
    virtual void DumpImage(string filename);
    virtual void Display_X_Server();
    virtual void Display_ASCII();
    virtual void Display_CMD();
    virtual int **get_grayPixels();
    virtual int ***get_rgbPixels();
    // template <class T>
    // T get_pixels();
    // int **get_pixels();
    // virtual int ***get_pixels();
    int get_width();
    int get_height();
};

#endif