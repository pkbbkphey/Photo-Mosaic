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
    /*img0->LoadImage("Image-Folder/lena.jpg");
    img0->DumpImage("Image-Folder/results/a0.jpg");
    img0->Display_X_Server();

    filter.apply(img0->get_grayPixels(), img0->get_width(), img0->get_height(), 0b00001100);
    img0->DumpImage("Image-Folder/results/a1.jpg");
    img0->Display_X_Server();

    img0->LoadImage("Image-Folder/lena.jpg");
    filter.apply(img0->get_grayPixels(), img0->get_width(), img0->get_height(), filter.BOX | filter.SOBEL);
    img0->DumpImage("Image-Folder/results/a2.jpg");
    img0->Display_X_Server();

    img0->LoadImage("Image-Folder/noise.jpg");
    filter.apply(img0->get_grayPixels(), img0->get_width(), img0->get_height(), filter.MEDIAN);
    img0->DumpImage("Image-Folder/results/a3.jpg");
    img0->Display_X_Server();*/

    img0->LoadImage("Image-Folder/lena.jpg");
    img0->Display_X_Server();

    filter.apply_order(img0->get_grayPixels(), img0->get_width(), img0->get_height(), 10200);
    img0->DumpImage("Image-Folder/results/a4.jpg");
    img0->Display_X_Server();

    img0->LoadImage("Image-Folder/lena.jpg");
    filter.apply_order(img0->get_grayPixels(), img0->get_width(), img0->get_height(), 10230);
    img0->DumpImage("Image-Folder/results/a5.jpg");
    img0->Display_X_Server();


    //  TEST FOR RGB FILTERS
    Image *img1 = new RGBImage();
    /*img1->LoadImage("Image-Folder/lena.jpg");
    img1->DumpImage("Image-Folder/results/b0.jpg");
    img1->Display_X_Server();

    filter.apply(img1->get_rgbPixels(), img1->get_width(), img1->get_height(), 0b00001100);
    img1->DumpImage("Image-Folder/results/b1.jpg");
    img1->Display_X_Server();

    img1->LoadImage("Image-Folder/lena.jpg");
    filter.apply(img1->get_rgbPixels(), img1->get_width(), img1->get_height(), filter.BOX | filter.SOBEL);
    img1->DumpImage("Image-Folder/results/b2.jpg");
    img1->Display_X_Server();

    img1->LoadImage("Image-Folder/noise.jpg");
    filter.apply(img1->get_rgbPixels(), img1->get_width(), img1->get_height(), filter.MEDIAN);
    img1->DumpImage("Image-Folder/results/b3.jpg");
    img1->Display_X_Server();*/

    img1->LoadImage("Image-Folder/lena.jpg");
    img1->Display_X_Server();

    filter.apply_order(img1->get_rgbPixels(), img1->get_width(), img1->get_height(), 2010);
    img1->DumpImage("Image-Folder/results/b4.jpg");
    img1->Display_X_Server();

    img1->LoadImage("Image-Folder/lena.jpg");
    filter.apply_order(img1->get_rgbPixels(), img1->get_width(), img1->get_height(), 1020);
    img1->DumpImage("Image-Folder/results/b5.jpg");
    img1->Display_X_Server();

// ^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^
    // some photo mosaic driven code here

    // more ...
    return 0;
}
