#include "image.h"
#include "data_loader.h"

using namespace std;

// Define the static member variable
Data_Loader Image::imagefile;       // This is very important! It takes 3 hours to find this bug

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

void Image::setAlpha(int **alpha){
    cout << "YOU CALLED A virtual FUNCTION.\n";
}