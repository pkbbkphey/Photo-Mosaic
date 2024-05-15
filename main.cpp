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

// vvvvvvvvvvvvvvvvvvvvvvvvvvvvvvv  Demostrate bit field fielter  vvvvvvvvvvvvvvvvvvvvvvvvvvvvv
    // some bit field filter design driven code here
    Image *img_test = new GrayImage();
    img_test->LoadImage("Image-Folder/lena.jpg");
    img_test->DumpImage("img_test_raw.jpg");
    img_test->Display_X_Server();

    photo_filter filter;
    filter.applyBoxFilter(img_test->get_grayPixels(), img_test->get_width(), img_test->get_height());
    img_test->DumpImage("img_test_boxFilter.jpg");
    img_test->Display_X_Server();

    img_test->LoadImage("Image-Folder/lena.jpg");
    filter.applySobelGradient(img_test->get_grayPixels(), img_test->get_width(), img_test->get_height());
    img_test->DumpImage("img_test_sobelGradient.jpg");
    img_test->Display_X_Server();

// ^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^
    // some photo mosaic driven code here

    // more ...
    return 0;
}
