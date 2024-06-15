#include "gray_image.h"
#include "image.h"
#include "data_loader.h"

using namespace std;
   
GrayImage::GrayImage(): Image(0, 0), pixels(nullptr){

}
GrayImage::GrayImage(int width, int height, int **pixels): Image(width, height), pixels(pixels) {
    // no need to new pixels, since it should be newed in LoadImage()
}
GrayImage::~GrayImage(){
    if (pixels != nullptr) {
        for (int i = 0; i < height; ++i) {
            delete[] pixels[i];
        }
        delete[] pixels;
        pixels = nullptr;  // Ensure pixels is null after deletion
    }
    // cout << "~GrayImage()\n";
}

void GrayImage::copyPixels(const GrayImage& other) {
    width = other.width;
    height = other.height;
    if (other.pixels != nullptr) {
        pixels = new int*[height];
        for (int i = 0; i < height; ++i) {
            pixels[i] = new int[width];
            std::copy(other.pixels[i], other.pixels[i] + width, pixels[i]);
        }
    } else {
        pixels = nullptr;
    }
}
// Copy Constructor
GrayImage::GrayImage(const GrayImage& other) : Image(other) {
    copyPixels(other);
}
// Copy Assignment Operator
GrayImage& GrayImage::operator=(const GrayImage& other) {
    if (this != &other) {
        // Free existing resource
        if (pixels != nullptr) {
            for (int i = 0; i < height; ++i) {
                delete[] pixels[i];
            }
            delete[] pixels;
        }
        // Copy new resource
        Image::operator=(other);
        copyPixels(other);
    }
    return *this;
}


bool GrayImage::LoadImage(string filename){
    // Clean up before loading next image
    if (pixels != nullptr) {
        for (int i = 0; i < height; ++i) {
            delete[] pixels[i];
        }
        delete[] pixels;
        pixels = nullptr;  // Ensure pixels is null after deletion
    }
    pixels = imagefile.Load_Gray(filename, &width, &height);  // this call returns a new 2D int space
    fname = filename;
    return (pixels != nullptr);
}
void GrayImage::DumpImage(string filename){
    imagefile.Dump_Gray(width, height, pixels, filename);
    fname = filename;
}
void GrayImage::Display_X_Server(){
    imagefile.Display_Gray_X_Server(width, height, pixels);
}
void GrayImage::Display_ASCII(){
    imagefile.Display_Gray_ASCII(width, height, pixels);
}
void GrayImage::Display_CMD(){
    imagefile.Display_Gray_CMD(fname);
}
int** GrayImage::get_grayPixels(){
    return pixels;
}