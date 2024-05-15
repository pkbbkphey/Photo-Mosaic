#include "image.h"
#include "data_loader.h"

using namespace std;

Image::Image(int width, int height): width(width), height(height) {

}
Image::~Image(){
    
}

bool Image::LoadImage(string filename){
    cout << "YOU CALLED A virtual FUNCTION.\n";
    return 0;
}
void Image::DumpImage(string filename){
    cout << "YOU CALLED A virtual FUNCTION.\n";
}
void Image::Display_X_Server(){
    cout << "YOU CALLED A virtual FUNCTION.\n";
}
void Image::Display_ASCII(){
    cout << "YOU CALLED A virtual FUNCTION.\n";
}
void Image::Display_CMD(){
    cout << "YOU CALLED A virtual FUNCTION.\n";
}

int **Image::get_grayPixels(){
    cout << "YOU CALLED A virtual FUNCTION.\n";
    return nullptr;
}
int ***Image::get_rgbPixels(){
    cout << "YOU CALLED A virtual FUNCTION.\n";
    return nullptr;
}
int Image::get_width(){
    return width;
}
int Image::get_height(){
    return height;
}
