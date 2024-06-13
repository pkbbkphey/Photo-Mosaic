#include "transparent_image.h"
#include "rgb_image.h"

// Constructor definitions
transparentImage::transparentImage() : RGBImage() {
    alpha = nullptr;
}

transparentImage::transparentImage(int width, int height, int ***pixels, int **alpha)
    : RGBImage(width, height, pixels) {
    this->alpha = alpha;
}

// Destructor
transparentImage::~transparentImage() {
    if (alpha != nullptr) {
        for (int i = 0; i < height; ++i) {
            delete[] alpha[i];
        }
        delete[] alpha;
    }
}

// Implementation of DumpImage
void transparentImage::DumpImage(string filename) {
    // Ensure the Data_Loader is initialized properly
    // Data_Loader dataLoader;

    // Use the Dump_RGBA_PNG method from the Data_Loader to save the image with transparency
    imagefile.Dump_RGBA_PNG(width, height, pixels, alpha, filename);
}

void transparentImage::setAlpha(int **alpha){
    this->alpha = alpha;
}