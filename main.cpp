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
    Image *img_test = new GrayImage();
    img_test->LoadImage("Image-Folder/lena.jpg");
    img_test->DumpImage("Image-Folder/results/raw.jpg");
    img_test->Display_X_Server();

    filter.applyBoxFilter(img_test->get_grayPixels(), img_test->get_width(), img_test->get_height());
    img_test->DumpImage("Image-Folder/results/boxFilter.jpg");
    img_test->Display_X_Server();

    img_test->LoadImage("Image-Folder/lena.jpg");
    filter.applySobelGradient(img_test->get_grayPixels(), img_test->get_width(), img_test->get_height());
    img_test->DumpImage("Image-Folder/results/sobelGradient.jpg");
    img_test->Display_X_Server();

    img_test->LoadImage("Image-Folder/lena.jpg");
    filter.applyContrastStretching(img_test->get_grayPixels(), img_test->get_width(), img_test->get_height());
    img_test->DumpImage("Image-Folder/results/contrastStretching.jpg");
    img_test->Display_X_Server();

    img_test->LoadImage("Image-Folder/lena.jpg");
    filter.applyMosaicFilter(img_test->get_grayPixels(), img_test->get_width(), img_test->get_height(), 10);
    img_test->DumpImage("Image-Folder/results/mosaicFilter.jpg");
    img_test->Display_X_Server();

    img_test->LoadImage("Image-Folder/lena.jpg");
    filter.applyMedianFilter(img_test->get_grayPixels(), img_test->get_width(), img_test->get_height());
    img_test->DumpImage("Image-Folder/results/medianFilter.jpg");
    img_test->Display_X_Server();

    //  TEST FOR RGB FILTERS
    Image *img_test1 = new RGBImage();
    img_test1->LoadImage("Image-Folder/lena.jpg");
    img_test1->DumpImage("Image-Folder/results/raw1.jpg");
    img_test1->Display_X_Server();

    filter.applyBoxFilter(img_test1->get_rgbPixels(), img_test1->get_width(), img_test1->get_height());
    img_test1->DumpImage("Image-Folder/results/boxFilter1.jpg");
    img_test1->Display_X_Server();

    img_test1->LoadImage("Image-Folder/lena.jpg");
    filter.applySobelGradient(img_test1->get_rgbPixels(), img_test1->get_width(), img_test1->get_height());
    img_test1->DumpImage("Image-Folder/results/sobelGradient1.jpg");
    img_test1->Display_X_Server();

    img_test1->LoadImage("Image-Folder/lena.jpg");
    filter.applyContrastStretching(img_test1->get_rgbPixels(), img_test1->get_width(), img_test1->get_height());
    img_test1->DumpImage("Image-Folder/results/contrastStretching1.jpg");
    img_test1->Display_X_Server();

    img_test1->LoadImage("Image-Folder/lena.jpg");
    filter.applyMosaicFilter(img_test1->get_rgbPixels(), img_test1->get_width(), img_test1->get_height(), 10);
    img_test1->DumpImage("Image-Folder/results/mosaicFilter1.jpg");
    img_test1->Display_X_Server();

    img_test1->LoadImage("Image-Folder/lena.jpg");
    filter.applyMedianFilter(img_test1->get_rgbPixels(), img_test1->get_width(), img_test1->get_height());
    img_test1->DumpImage("Image-Folder/results/medianFilter1.jpg");
    img_test1->Display_X_Server();

// ^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^
    // some photo mosaic driven code here

    // more ...
    return 0;
}
