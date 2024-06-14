#include "image.h"
#include "gray_image.h"
#include "rgb_image.h"
#include "transparent_image.h"
#include "bit_field_filter.h"
#include "photo_mosaic.h"
#include "matting.h"

using namespace std;

int main(int argc, char *argv[]){
// vvvvvvvvvvvvvvv  Demonstrate image loading, dumping, and displaying  vvvvvvvvvvvvvvvvvvvvvvv

    cout << "\nvvvvvvvvvvvvvvv  Demonstrate image loading, dumping, and displaying  vvvvvvvvvvvvvvvvvvvvvvv\n";
    Image *grayImg = new GrayImage();
    grayImg->LoadImage("Image-Folder/mnist/img_100.jpg");
    grayImg->DumpImage("img1.jpg");
    grayImg->Display_CMD();
    grayImg->Display_X_Server();
    
    Image *RGBImg = new RGBImage();
    RGBImg->LoadImage("Image-Folder/lena.jpg");
    RGBImg->DumpImage("img2.jpg");
    RGBImg->Display_CMD();
    RGBImg->Display_X_Server();

// ^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

// vvvvvvvvvvvvvvvvvvvvvvvvvvvvvvv  Demostrate bit field filter  vvvvvvvvvvvvvvvvvvvvvvvvvvvvvv
    // some bit field filter design driven code here

    cout << "\nvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvv  Demostrate bit field filter  vvvvvvvvvvvvvvvvvvvvvvvvvvvvvv\n";
    //  TEST FOR GRAYSCALE FILTERS
    photo_filter filter;

    /*grayImg->LoadImage("Image-Folder/noise.jpg");
    // grayImg->DumpImage("Image-Folder/results/c0.jpg");
    grayImg->Display_X_Server();

    filter.applyAnisotropicDiffusion(grayImg->get_grayPixels(), grayImg->get_width(), grayImg->get_height(), 10, 0.3, 18);
    // grayImg->DumpImage("Image-Folder/results/c2.jpg");
    grayImg->Display_X_Server();*/

    //  Test for grayscale bit field filters
    cout << "  =============== Case 1 ===============\n";
    cout << "    original image\n";
    grayImg->LoadImage("Image-Folder/lena.jpg");
    grayImg->Display_X_Server();

    cout << "    filtered image (0b00001100)\n";
    filter.apply(grayImg->get_grayPixels(), grayImg->get_width(), grayImg->get_height(), 0b00001100);
    grayImg->Display_X_Server();


    //  Test for RGB bit field filters
    cout << "  =============== Case 2 ===============\n";
    cout << "    original image\n";
    RGBImg->LoadImage("Image-Folder/lena.jpg");
    RGBImg->DumpImage("Image-Folder/results/b0.jpg");
    RGBImg->Display_X_Server();

    cout << "    filtered image (0b00001100)\n";
    filter.apply(RGBImg->get_rgbPixels(), RGBImg->get_width(), RGBImg->get_height(), 0b00001100);
    RGBImg->Display_X_Server();


    //  Test for RGB bit field filters with order
    cout << "  =============== Case 3 ===============\n";
    cout << "    original image\n";
    grayImg->LoadImage("Image-Folder/lena.jpg");
    // grayImg->DumpImage("Image-Folder/results/c0.jpg");
    grayImg->Display_X_Server();

    cout << "    filtered image\n";
    filter.apply_order(grayImg->get_grayPixels(), grayImg->get_width(), grayImg->get_height(), 20031);
    // grayImg->DumpImage("Image-Folder/results/c1.jpg");
    grayImg->Display_X_Server();

    cout << "  =============== Case 4 ===============\n";
    cout << "    original image\n";
    grayImg->LoadImage("Image-Folder/lena.jpg");
    grayImg->Display_X_Server();

    cout << "    filtered image 1\n";
    filter.apply_order(grayImg->get_grayPixels(), grayImg->get_width(), grayImg->get_height(), 2010);
    grayImg->Display_X_Server();

    cout << "    filtered image 2\n";
    grayImg->LoadImage("Image-Folder/lena.jpg");
    filter.apply_order(grayImg->get_grayPixels(), grayImg->get_width(), grayImg->get_height(), 1020);
    grayImg->Display_X_Server();

// ^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

// vvvvvvvvvvvvvvvvvvvvvvvvvvvvvvv  Demostrate for photo mosaic  vvvvvvvvvvvvvvvvvvvvvvvvvvvvvv
    // some photo mosaic driven code here

    cout << "\nvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvv  Demostrate for photo mosaic  vvvvvvvvvvvvvvvvvvvvvvvvvvvvvv\n";

    cout << "  =============== Case 1 ===============\n";
    cout << "    original image\n";
    RGBImg->LoadImage("Image-Folder/girl_2x.png");
    RGBImg->Display_X_Server();

    cout << "    mosaic image\n";
    PhotoMosaic* mosaicObj = new PhotoMosaic();
    RGBImg = mosaicObj->generate("Image-Folder/cifar10", "Image-Folder/girl_2x.png");
    RGBImg->Display_X_Server();
    RGBImg->DumpImage("Image-Folder/results/mosaicImg.jpg");

    cout << "  =============== Case 2 ===============\n";
    cout << "    original image\n";
    RGBImg->LoadImage("Image-Folder/CKS_Memorial_Hall.jpg");
    RGBImg->Display_X_Server();

    cout << "    mosaic image\n";
    RGBImg = mosaicObj->generate("Image-Folder/cifar10", "Image-Folder/CKS_Memorial_Hall.jpg");
    RGBImg->Display_X_Server();

// ^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

    // more ...
// vvvvvvvvvvvvvvvvvvvvvvvvv  Demostrate for transparent image  vvvvvvvvvvvvvvvvvvvvvvvvvvvvvvv

    cout << "\nvvvvvvvvvvvvvvvvvvvvvvvvv  Demostrate for transparent image  vvvvvvvvvvvvvvvvvvvvvvvvvvvvvvv\n";
    RGBImg->LoadImage("Image-Folder/lena.jpg");
    RGBImg->Display_X_Server();

    Image *transImg = new transparentImage();
    transImg->LoadImage("Image-Folder/lena.jpg");
    int w = transImg->get_width(); 
    int h = transImg->get_height();
    int **alpha = new int *[h];
    for(int j = 0; j < h; ++j){
        alpha[j] = new int [w];
        for(int i = 0; i < w; ++i){
            alpha[j][i] = 255 * (float(i)/w) * (float(j)/h);
        }
    }
    transImg->setAlpha(alpha);
    transImg->DumpImage("Image-Folder/results/trans_png.png");
    transImg->Display_X_Server();

// ^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

// vvvvvvvvvvvvvvvvvvvvvvvvvvvv  Demostrate for image matting  vvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvv

    cout << "\nvvvvvvvvvvvvvvvvvvvvvvvvvvvv  Demostrate for image matting  vvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvv\n";

    cout << "  =============== Case 1 ===============\n";
    cout << "    original image\n";
    RGBImg->LoadImage("Image-Folder/bird.jpg");
    RGBImg->Display_X_Server();

    cout << "    matted image (mode = remove_blurred)\n";
    matting mattingObj;
    mattingObj.setMode(mattingObj.remove_blurred);
    transImg = mattingObj.applyMatting("Image-Folder/bird.jpg");
    transImg->DumpImage("Image-Folder/results/matt/mattImg14.png");
    transImg->Display_X_Server();
    
    cout << "  =============== Case 2 ===============\n";
    cout << "    original image\n";
    RGBImg->LoadImage("Image-Folder/ladybug.jpg");
    RGBImg->Display_X_Server();

    cout << "    matted image (mode = remove_blurred_smoothly)\n";
    mattingObj.setMode(mattingObj.remove_blurred_smoothly);
    transImg = mattingObj.applyMatting("Image-Folder/ladybug.jpg");
    transImg->Display_X_Server();

    cout << "  =============== Case 3 ===============\n";
    cout << "    original image\n";
    RGBImg->LoadImage("Image-Folder/texts.jpg");
    RGBImg->Display_X_Server();

    cout << "    matted image (mode = extract_text)\n";
    mattingObj.setMode(mattingObj.extract_text);
    transImg = mattingObj.applyMatting("Image-Folder/texts.jpg");
    transImg->Display_X_Server();


// ^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^
    return 0;
}
