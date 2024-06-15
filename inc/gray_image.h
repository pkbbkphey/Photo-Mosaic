#ifndef _GRAY_IMAGE_H_
#define _GRAY_IMAGE_H_

#include "image.h"

class GrayImage : public Image{
private:
    int **pixels;
    void copyPixels(const GrayImage& other);

public:
    GrayImage();
    GrayImage(int width, int height, int **pixels);
    GrayImage(const GrayImage& other);  // Copy Constructor
    GrayImage& operator=(const GrayImage& other);   // Copy Assignment Operator
    virtual ~GrayImage();
    virtual bool LoadImage(string filename);
    virtual void DumpImage(string filename);
    virtual void Display_X_Server();
    virtual void Display_ASCII();
    virtual void Display_CMD();
    virtual int **get_grayPixels();
};

#endif