#ifndef _RGB_IMAGE_H_
#define _RGB_IMAGE_H_

#include "image.h"

class RGBImage : public Image{
protected:
    int ***pixels;

public:
    RGBImage();
    RGBImage(int width, int height, int ***pixels);
    ~RGBImage();
    virtual bool LoadImage(string filename);
    virtual void DumpImage(string filename);
    virtual void Display_X_Server();
    virtual void Display_ASCII();
    virtual void Display_CMD();
    int ***get_rgbPixels();
    
};

#endif