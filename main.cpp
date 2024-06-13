#include "image.h"
#include "gray_image.h"
#include "rgb_image.h"
#include "photo_mosaic.h"
#include "bit_field_filter.h"

int main(int argc, char *argv[]){
// vvvvvvvvvvvvvvv  Demonstrate image loading, dumping, and displaying  vvvvvvvvvvvvvvvvvvvvvvv
    // Image *img1 = new GrayImage();
    // img1->LoadImage("Image-Folder/mnist/img_100.jpg");
    // img1->DumpImage("img1.jpg");
    // img1->Display_X_Server();
    // img1->Display_CMD();
    
    // Image *img2 = new RGBImage();
    // img2->LoadImage("Image-Folder/lena.jpg");
    // img2->DumpImage("img2.jpg");
    // img2->Display_X_Server();
    // img2->Display_CMD();
// ^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

// vvvvvvvvvvvvvvvvvvvvvvvvvvvvvvv  Demostrate bit field filter  vvvvvvvvvvvvvvvvvvvvvvvvvvvvvv
    // some bit field filter design driven code here
    //  TEST FOR GRAYSCALE FILTERS
    photo_filter filter;
    Image *img0 = new GrayImage();
    img0->LoadImage("Image-Folder/noise.jpg");
    img0->DumpImage("Image-Folder/results/c0.jpg");
    img0->Display_X_Server();

    // filter.apply_order(img0->get_grayPixels(), img0->get_width(), img0->get_height(), 20031);
    // img0->DumpImage("Image-Folder/results/c1.jpg");
    // img0->Display_X_Server();

    filter.applyAnisotropicDiffusion(img0->get_grayPixels(), img0->get_width(), img0->get_height(), 10, 0.3, 18);
    img0->DumpImage("Image-Folder/results/c2.jpg");
    img0->Display_X_Server();

    //  TEST FOR RGB FILTERS
    // Image *img1 = new RGBImage();
    /*img1->LoadImage("Image-Folder/lena.jpg");
    img1->DumpImage("Image-Folder/results/b0.jpg");
    img1->Display_X_Server();

    filter.apply(img1->get_rgbPixels(), img1->get_width(), img1->get_height(), 0b00001100);*/


// ^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

// vvvvvvvvvvvvvvvvvvvvvvvvvvvvvvv  Demostrate for photo mosaic  vvvvvvvvvvvvvvvvvvvvvvvvvvvvvv
    // some photo mosaic driven code here
    PhotoMosaic* mosaicObj = new PhotoMosaic();
    RGBImage *mosaicImg;
    mosaicImg = mosaicObj->generate("Image-Folder/cifar10", "Image-Folder/87499_0.jpg");
    mosaicImg->Display_X_Server();
    mosaicImg->DumpImage("Image-Folder/results/mosaicImg.jpg");
// ^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^
    // more ...
    return 0;
}
