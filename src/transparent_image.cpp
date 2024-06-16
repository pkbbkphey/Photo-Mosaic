#include "transparent_image.h"
#include "rgb_image.h"

// Constructor definitions
transparentImage::transparentImage() : RGBImage() {
    alpha = nullptr;
}

transparentImage::transparentImage(int width, int height, int ***pixels, int **alpha_)
    : RGBImage(width, height, pixels) {
    this->alpha = alpha_;
}

// Destructor
transparentImage::~transparentImage() {
    if (alpha != nullptr) {
        for (int i = 0; i < height; ++i) {
            delete[] alpha[i];
        }
        delete[] alpha;
    }
    // cout << "~transparentImage()\n";
}

void transparentImage::Display_X_Server(){
    int ***temp_pixels = new int **[height];
    for(int j = 0; j < height; ++j){
        temp_pixels[j] = new int *[width];
        for(int i = 0; i < width; ++i){
            temp_pixels[j][i] = new int[3];
            temp_pixels[j][i][0] = pixels[j][i][0] * alpha[j][i] / 255;
            temp_pixels[j][i][1] = pixels[j][i][1] * alpha[j][i] / 255;
            temp_pixels[j][i][2] = pixels[j][i][2] * alpha[j][i] / 255;
        }
    }
    imagefile.Display_RGB_X_Server(width, height, temp_pixels);
    // Clean up temp_pixels
    for(int j = 0; j < height; ++j){
        for(int i = 0; i < width; ++i){
            delete[] temp_pixels[j][i];
        }
        delete[] temp_pixels[j];
    }
    delete[] temp_pixels;
}

// Implementation of DumpImage
void transparentImage::DumpImage(string filename) {
    // Ensure the Data_Loader is initialized properly
    // Data_Loader dataLoader;

    // Use the Dump_RGBA_PNG method from the Data_Loader to save the image with transparency
    imagefile.Dump_RGBA_PNG(width, height, pixels, alpha, filename);
}

void transparentImage::setAlpha(int **alpha_){
    // Clean up before loading next alpha
    if (alpha != nullptr) {
        for (int i = 0; i < height; ++i) {
            delete[] alpha[i];
        }
        delete[] alpha;
    }
    this->alpha = alpha_;
}

int **transparentImage::getAlpha(){
    return alpha;
}