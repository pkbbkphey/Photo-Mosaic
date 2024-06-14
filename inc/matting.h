#ifndef _MATTING_H_
#define _MATTING_H_

#include "transparent_image.h"

class matting{
public:
    transparentImage* applyMatting(string orignPath);
    enum mode {remove_blurred, remove_blurred_smoothly, extract_text};
    void setMode(int _mode);
private:
    int mode = remove_blurred;
};

#endif