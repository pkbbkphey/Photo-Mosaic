#include "gray_image.h"
#include "image.h"
#include "data_loader.h"

using namespace std;
   
GrayImage::GrayImage(): Image(0, 0){  // need to use copy constructor

}
GrayImage::GrayImage(int width, int height, int **pixels): Image(width, height), pixels(pixels) {
    // no need to new pixels, since it should be newed in LoadImage()
}
GrayImage::~GrayImage(){
    for(int i = 0; i < height; ++i) delete[] pixels[i];
    delete[] pixels;
}

bool GrayImage::LoadImage(string filename){
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