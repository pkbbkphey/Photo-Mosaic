#include "rgb_image.h"
#include "image.h"
#include "data_loader.h"

using namespace std;
   
RGBImage::RGBImage(): Image(0, 0){

}
RGBImage::RGBImage(int width, int height, int ***pixels): Image(width, height), pixels(pixels) {
    // no need to new pixels, since it should be newed in LoadImage()
}
RGBImage::~RGBImage(){
    for(int i = 0; i < height; ++i){
        for(int j = 0; j < width; ++j) delete[] pixels[i][j];
        delete[] pixels[i];
    }
    delete[] pixels;
}

bool RGBImage::LoadImage(string filename){
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