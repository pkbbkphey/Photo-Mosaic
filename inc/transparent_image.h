#ifndef _TRANSPARENT_IMAGE_H_
#define _TRANSPARENT_IMAGE_H_

#include "rgb_image.h"

class transparentImage : public RGBImage{
private:
    int **alpha = nullptr;
public:
    transparentImage();
    transparentImage(int width, int height, int ***pixels, int **alpha);
    virtual ~transparentImage();
    virtual void Display_X_Server();
    virtual void DumpImage(string filename);
    virtual void setAlpha(int **alpha);
    virtual int **getAlpha();
};

#endif