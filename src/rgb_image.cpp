#include "rgb_image.h"
#include "image.h"
#include "data_loader.h"

using namespace std;
   
RGBImage::RGBImage(): Image(0, 0), pixels(nullptr){
    // cout << "RGBImage()\n";
}
RGBImage::RGBImage(int width_, int height_, int ***pixels_): Image(width_, height_), pixels(pixels_) {
    // no need to new pixels, since it should be newed in LoadImage()
    // cout << "RGBImage(int width, int height, int ***pixels_)\n";
    // cout << (pixels == nullptr) << " " << width << " " << height << endl;
}
RGBImage::~RGBImage(){
    if(pixels != nullptr){
        for(int i = 0; i < height; ++i){
            for(int j = 0; j < width; ++j) delete[] pixels[i][j];
            delete[] pixels[i];
        }
        delete[] pixels;
        pixels = nullptr;
    }
    // cout << "~RGBImage()\n";
}
// Copy Constructor
RGBImage::RGBImage(const RGBImage& other) : Image(other.width, other.height), pixels(nullptr) {
    // cout << "RGBImage(const RGBImage& other)\n";
    if (other.pixels) {
        pixels = new int**[height];
        for (int i = 0; i < height; ++i) {
            pixels[i] = new int*[width];
            for (int j = 0; j < width; ++j) {
                pixels[i][j] = new int[3];
                for (int k = 0; k < 3; ++k) {
                    pixels[i][j][k] = other.pixels[i][j][k];
                }
            }
        }
    }
}
// Copy Assignment Operator
RGBImage& RGBImage::operator=(const RGBImage& other) {
    // cout << "RGBImage::operator=\n";

    if (this == &other) return *this; // Self-assignment check

    // Free existing resources
    if (pixels != nullptr) {
        for (int i = 0; i < height; ++i) {
            for (int j = 0; j < width; ++j) delete[] pixels[i][j];
            delete[] pixels[i];
        }
        delete[] pixels;
    }

    width = other.width;
    height = other.height;

    // Allocate new resources and copy data
    // if (other.pixels) {
    //     pixels = new int**[height];
    //     for (int i = 0; i < height; ++i) {
    //         pixels[i] = new int*[width];
    //         for (int j = 0; j < width; ++j) {
    //             pixels[i][j] = new int[3];
    //             for (int k = 0; k < 3; ++k) {
    //                 pixels[i][j][k] = other.pixels[i][j][k];
    //             }
    //         }
    //     }
    // }
    // else {
    //     pixels = nullptr;
    // }
    pixels = other.pixels;

    return *this;
}

bool RGBImage::LoadImage(string filename){
    // Claen up before loading next image
    if(pixels != nullptr){
        for(int i = 0; i < height; ++i){
            for(int j = 0; j < width; ++j) delete[] pixels[i][j];
            delete[] pixels[i];
        }
        delete[] pixels;
        pixels = nullptr;
    }
    pixels = imagefile.Load_RGB(filename, &width, &height);  // this call returns a new 3D int space
    fname = filename;
    return (pixels != nullptr);
}
void RGBImage::DumpImage(string filename){
    imagefile.Dump_RGB(width, height, pixels, filename);
    fname = filename;
}
void RGBImage::Display_X_Server(){
    imagefile.Display_RGB_X_Server(width, height, pixels);
}
void RGBImage::Display_ASCII(){
    imagefile.Display_RGB_ASCII(width, height, pixels);
}
void RGBImage::Display_CMD(){
    imagefile.Display_RGB_CMD(fname);
}
int*** RGBImage::get_rgbPixels(){
    return pixels;
}