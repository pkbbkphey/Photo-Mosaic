#ifndef _MATTING_H_
#define _MATTING_H_

#include "transparent_image.h"

class matting{
public:
    transparentImage* applyMatting(string orignPath);
};

#endif