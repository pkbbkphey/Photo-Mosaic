
#define DEMO_IMG_LOADING
#define DEMO_BIT_FIEL_FILTER
#define DEMO_PHOTO_MOSAIC
#define DEMO_TRANS_IMG
#define DEMO_IMG_MATTING

bool FOR_VAL_GRIND = 0;
#define EN_X_SERVER !FOR_VAL_GRIND
#define EN_DUMP_PNG !FOR_VAL_GRIND


#include "image.h"
#include "gray_image.h"
#include "rgb_image.h"
#include "transparent_image.h"
#include "bit_field_filter.h"
#include "photo_mosaic.h"
#include "matting.h"
#include "screen.h"

using namespace std;

int main(int argc, char *argv[]){

    typedef Image* ImagePtr;
    ImagePtr grayImg, grayImg2;
    ImagePtr RGBImg, RGBImg2;
    ImagePtr transImg;

    Screen_ screen;

// vvvvvvvvvvvvvvv  Demonstrate image loading, dumping, and displaying  vvvvvvvvvvvvvvvvvvvvvvv

    #ifdef DEMO_IMG_LOADING
    cout << "\nvvvvvvvvvvvvvvv  Demonstrate image loading, dumping, and displaying  vvvvvvvvvvvvvvvvvvvvvvv\n";
    // case 1
    grayImg = new GrayImage();
    grayImg->LoadImage("Image-Folder/check.jpg");
    grayImg->Display_CMD();
    grayImg->Display_ASCII();
    delete grayImg;

    // case 2
    grayImg = new GrayImage();
    grayImg->LoadImage("Image-Folder/smile.jpg");
    grayImg->DumpImage("demo00_dump_gray.jpg");
    grayImg->Display_CMD();
    if(EN_X_SERVER)
    grayImg->Display_X_Server();
    delete grayImg;
    
    // case 3
    RGBImg = new RGBImage();
    RGBImg->LoadImage("Image-Folder/smile.jpg");
    RGBImg->DumpImage("demo01_dump_RGB.jpg");
    RGBImg->Display_CMD();
    if(EN_X_SERVER)
    RGBImg->Display_X_Server();
    delete RGBImg;

    #endif
// ^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

// vvvvvvvvvvvvvvvvvvvvvvvvvvvvvvv  Demostrate bit field filter  vvvvvvvvvvvvvvvvvvvvvvvvvvvvvv
    // some bit field filter design driven code here
    photo_filter filter;
    #ifdef DEMO_BIT_FIEL_FILTER
    cout << "\nvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvv  Demostrate bit field filter  vvvvvvvvvvvvvvvvvvvvvvvvvvvvvv\n";

    cout << "  =============== Case 1 ===============\n";
    RGBImg = new RGBImage();
    RGBImg->LoadImage("Image-Folder/lena.jpg");

    RGBImg2 = new RGBImage();
    RGBImg2->LoadImage("Image-Folder/lena.jpg");
    cout << "    filtering... (option = BOX)\n";
    filter.apply(RGBImg2->get_rgbPixels(), RGBImg2->get_width(), RGBImg2->get_height(), filter.BOX);

    if(EN_X_SERVER)
    screen.displayParallel( RGBImg->get_rgbPixels(), RGBImg->get_width(), RGBImg->get_height(), RGBImg2->get_rgbPixels(), RGBImg2->get_width(), RGBImg2->get_height());
    RGBImg2->DumpImage("demo10_bitFieldFilter.jpg");
    delete RGBImg;
    delete RGBImg2;

    cout << "  =============== Case 2 ===============\n";
    RGBImg = new RGBImage();
    RGBImg->LoadImage("Image-Folder/lena.jpg");

    RGBImg2 = new RGBImage();
    RGBImg2->LoadImage("Image-Folder/lena.jpg");
    cout << "    filtering... (option = SOBEL)\n";
    filter.apply(RGBImg2->get_rgbPixels(), RGBImg2->get_width(), RGBImg2->get_height(), filter.SOBEL);

    if(EN_X_SERVER)
    screen.displayParallel( RGBImg->get_rgbPixels(), RGBImg->get_width(), RGBImg->get_height(), RGBImg2->get_rgbPixels(), RGBImg2->get_width(), RGBImg2->get_height());
    RGBImg2->DumpImage("demo11_bitFieldFilter.jpg");
    delete RGBImg;
    delete RGBImg2;

    cout << "  =============== Case 3 ===============\n";
    RGBImg = new RGBImage();
    RGBImg->LoadImage("Image-Folder/lena.jpg");

    RGBImg2 = new RGBImage();
    RGBImg2->LoadImage("Image-Folder/lena.jpg");
    cout << "    filtering... (option = CONTRAST)\n";
    filter.apply(RGBImg2->get_rgbPixels(), RGBImg2->get_width(), RGBImg2->get_height(), filter.CONTRAST);

    if(EN_X_SERVER)
    screen.displayParallel( RGBImg->get_rgbPixels(), RGBImg->get_width(), RGBImg->get_height(), RGBImg2->get_rgbPixels(), RGBImg2->get_width(), RGBImg2->get_height());
    RGBImg2->DumpImage("demo12_bitFieldFilter.jpg");
    delete RGBImg;
    delete RGBImg2;

    cout << "  =============== Case 4 ===============\n";
    RGBImg = new RGBImage();
    RGBImg->LoadImage("Image-Folder/lena.jpg");

    RGBImg2 = new RGBImage();
    RGBImg2->LoadImage("Image-Folder/lena.jpg");
    cout << "    filtering... (option = MOSAIC)\n";
    filter.apply(RGBImg2->get_rgbPixels(), RGBImg2->get_width(), RGBImg2->get_height(), filter.MOSAIC);

    if(EN_X_SERVER)
    screen.displayParallel( RGBImg->get_rgbPixels(), RGBImg->get_width(), RGBImg->get_height(), RGBImg2->get_rgbPixels(), RGBImg2->get_width(), RGBImg2->get_height());
    RGBImg2->DumpImage("demo13_bitFieldFilter.jpg");
    delete RGBImg;
    delete RGBImg2;

    cout << "  =============== Case 5 ===============\n";
    RGBImg = new RGBImage();
    RGBImg->LoadImage("Image-Folder/woman.jpg");

    RGBImg2 = new RGBImage();
    RGBImg2->LoadImage("Image-Folder/woman.jpg");
    cout << "    filtering... (option = MEDIAN)\n";
    filter.apply(RGBImg2->get_rgbPixels(), RGBImg2->get_width(), RGBImg2->get_height(), filter.MEDIAN);

    if(EN_X_SERVER)
    screen.displayParallel( RGBImg->get_rgbPixels(), RGBImg->get_width(), RGBImg->get_height(), RGBImg2->get_rgbPixels(), RGBImg2->get_width(), RGBImg2->get_height());
    RGBImg2->DumpImage("demo14_bitFieldFilter.jpg");
    delete RGBImg;
    delete RGBImg2;

    cout << "  =============== Case 6 ===============\n";
    grayImg = new GrayImage();
    grayImg->LoadImage("Image-Folder/fingerprint.jpg");

    grayImg2 = new GrayImage();
    grayImg2->LoadImage("Image-Folder/fingerprint.jpg");
    cout << "    filtering... (option = ANISOTROPIC)\n";
    filter.apply(grayImg2->get_grayPixels(), grayImg2->get_width(), grayImg2->get_height(), filter.ANISOTROPIC);

    if(EN_X_SERVER)
    screen.displayParallel( grayImg->get_grayPixels(), grayImg->get_width(), grayImg->get_height(), grayImg2->get_grayPixels(), grayImg2->get_width(), grayImg2->get_height());
    grayImg2->DumpImage("demo15_bitFieldFilter.jpg");
    delete grayImg;
    delete grayImg2;

    //  Test for grayscale bit field filters
    cout << "  =============== Case 7 ===============\n";
    grayImg = new GrayImage();
    grayImg->LoadImage("Image-Folder/lena.jpg");

    grayImg2 = new GrayImage();
    grayImg2->LoadImage("Image-Folder/lena.jpg");
    cout << "    filtering... (option = 0b001100 = CONTRAST | MOSAIC)\n";
    filter.apply(grayImg2->get_grayPixels(), grayImg2->get_width(), grayImg2->get_height(), 0b00001100);

    if(EN_X_SERVER)
    screen.displayParallel( grayImg->get_grayPixels(), grayImg->get_width(), grayImg->get_height(), grayImg2->get_grayPixels(), grayImg2->get_width(), grayImg2->get_height());
    grayImg2->DumpImage("demo16_bitFieldFilter.jpg");
    delete grayImg;
    delete grayImg2;


    //  Test for RGB bit field filters
    cout << "  =============== Case 8 ===============\n";
    RGBImg = new RGBImage();
    RGBImg->LoadImage("Image-Folder/lena.jpg");

    RGBImg2 = new RGBImage();
    RGBImg2->LoadImage("Image-Folder/lena.jpg");
    cout << "    filtering... (option = CONTRAST | MOSAIC)\n";
    filter.apply(RGBImg2->get_rgbPixels(), RGBImg2->get_width(), RGBImg2->get_height(), filter.CONTRAST | filter.MOSAIC);

    if(EN_X_SERVER)
    screen.displayParallel( RGBImg->get_rgbPixels(), RGBImg->get_width(), RGBImg->get_height(), RGBImg2->get_rgbPixels(), RGBImg2->get_width(), RGBImg2->get_height());
    RGBImg2->DumpImage("demo17_bitFieldFilter.jpg");
    delete RGBImg;
    delete RGBImg2;

    //  Test for RGB bit field filters with order
    cout << "  =============== Case 9 ===============\n";
    cout << "    demo : filters with order\n";
    grayImg = new GrayImage();
    grayImg->LoadImage("Image-Folder/lena.jpg");

    grayImg2 = new GrayImage();
    grayImg2->LoadImage("Image-Folder/lena.jpg");
    cout << "    filtering... (order = 20031)\n";
    filter.apply_order(grayImg2->get_grayPixels(), grayImg2->get_width(), grayImg2->get_height(), 20031);
    if(EN_X_SERVER)
    screen.displayParallel( grayImg->get_grayPixels(), grayImg->get_width(), grayImg->get_height(), grayImg2->get_grayPixels(), grayImg2->get_width(), grayImg2->get_height());
    grayImg2->DumpImage("demo18_bitFieldFilter.jpg");
    delete grayImg;
    delete grayImg2;
    

    cout << "  =============== Case 10 ==============\n";
    cout << "    demo : different order leads to different results\n";
    cout << "    original image\n";
    grayImg = new GrayImage();
    grayImg2 = new GrayImage();

    grayImg->LoadImage("Image-Folder/lena.jpg");
    if(EN_X_SERVER)
    grayImg->Display_X_Server();

    cout << "    filtering image 1... (order = 02010)\n";
    filter.apply_order(grayImg->get_grayPixels(), grayImg->get_width(), grayImg->get_height(), 2010);

    cout << "    filtering image 2... (order = 01020)\n";
    grayImg2->LoadImage("Image-Folder/lena.jpg");
    filter.apply_order(grayImg2->get_grayPixels(), grayImg2->get_width(), grayImg2->get_height(), 1020);

    if(EN_X_SERVER)
    screen.displayParallel( grayImg->get_grayPixels(), grayImg->get_width(), grayImg->get_height(), grayImg2->get_grayPixels(), grayImg2->get_width(), grayImg2->get_height());
    grayImg->DumpImage("demo19_bitFieldFilter.jpg");
    grayImg2->DumpImage("demo1A_bitFieldFilter.jpg");
    delete grayImg;
    delete grayImg2;


    #endif
// ^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

// vvvvvvvvvvvvvvvvvvvvvvvvvvvvvvv  Demostrate for photo mosaic  vvvvvvvvvvvvvvvvvvvvvvvvvvvvvv
    // some photo mosaic driven code here
    #ifdef DEMO_PHOTO_MOSAIC
    cout << "\nvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvv  Demostrate for photo mosaic  vvvvvvvvvvvvvvvvvvvvvvvvvvvvvv\n";

    PhotoMosaic mosaicObj;

    cout << "  =============== Case 1 ===============\n";
    cout << "    original image\n";
    RGBImg = new RGBImage();
    RGBImg->LoadImage("Image-Folder/girl_2x.png");
    if(EN_X_SERVER)
    RGBImg->Display_X_Server();
    delete RGBImg;

    cout << "    mosaic image\n";
    RGBImg = mosaicObj.generate("Image-Folder/cifar10", "Image-Folder/girl_2x.png");
    if(EN_X_SERVER)
    RGBImg->Display_X_Server();
    RGBImg->DumpImage("demo20_photoMosaic.jpg");
    delete RGBImg;

    cout << "  =============== Case 2 ===============\n";
    cout << "    original image\n";
    RGBImg = new RGBImage();
    RGBImg->LoadImage("Image-Folder/CKS_Memorial_Hall.jpg");
    if(EN_X_SERVER)
    RGBImg->Display_X_Server();
    delete RGBImg;

    cout << "    mosaic image\n";
    // RGBImg = new RGBImage();     // no need to new, because mosaicObj.generate already new one for that.
    RGBImg = mosaicObj.generate("Image-Folder/cifar10", "Image-Folder/CKS_Memorial_Hall.jpg");
    if(EN_X_SERVER)
    RGBImg->Display_X_Server();
    RGBImg->DumpImage("demo21_photoMosaic.jpg");
    delete RGBImg;

    cout << "  =============== Case 3 ===============\n";
    cout << "    original image\n";
    RGBImg = new RGBImage();
    RGBImg->LoadImage("Image-Folder/4k_owl.jpg");
    if(EN_X_SERVER)
    RGBImg->Display_X_Server();
    delete RGBImg;

    cout << "    mosaic image\n";
    RGBImg = mosaicObj.generate("Image-Folder/cifar10", "Image-Folder/4k_owl.jpg");
    if(EN_X_SERVER)
    RGBImg->Display_X_Server();
    RGBImg->DumpImage("demo22_photoMosaic.jpg");
    delete RGBImg;

    #endif
// ^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

    // more ...
// vvvvvvvvvvvvvvvvvvvvvvvvv  Demostrate for transparent image  vvvvvvvvvvvvvvvvvvvvvvvvvvvvvvv

    #ifdef DEMO_TRANS_IMG
    cout << "\nvvvvvvvvvvvvvvvvvvvvvvvvv  Demostrate for transparent image  vvvvvvvvvvvvvvvvvvvvvvvvvvvvvvv\n";
    cout << "    original image\n";
    RGBImg = new RGBImage();
    RGBImg->LoadImage("Image-Folder/lena.jpg");
    if(EN_X_SERVER)
    RGBImg->Display_X_Server();
    

    cout << "    transparent image\n";
    transImg = new transparentImage();
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
    if(EN_DUMP_PNG)
    transImg->DumpImage("demo30_transparentImg");
    if(EN_X_SERVER)
    transImg->Display_X_Server();

    if(EN_X_SERVER)
    screen.displayParallel( RGBImg->get_rgbPixels(), RGBImg->get_width(), RGBImg->get_height(), transImg->get_rgbPixels(), transImg->getAlpha(), transImg->get_width(), transImg->get_height());
    delete RGBImg;
    delete transImg;

    #endif
// ^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

// vvvvvvvvvvvvvvvvvvvvvvvvvvvv  Demostrate for image matting  vvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvv
    #ifdef DEMO_IMG_MATTING
    cout << "\nvvvvvvvvvvvvvvvvvvvvvvvvvvvv  Demostrate for image matting  vvvvvvvvvvvvvvvvvvvvvvvvvvvvvvvv\n";
    matting mattingObj;
    
    cout << "  =============== Case 1 ===============\n";
    cout << "    original image\n";
    RGBImg = new RGBImage();
    RGBImg->LoadImage("Image-Folder/watch.jpg");
    if(EN_X_SERVER)
    RGBImg->Display_X_Server();
    delete RGBImg;

    cout << "    matted image (mode = remove_blurred)\n";
    // no need to new transImg, since applyMatting does that
    mattingObj.setMode(mattingObj.remove_blurred);
    transImg = mattingObj.applyMatting("Image-Folder/watch.jpg");
    if(EN_X_SERVER)
    transImg->Display_X_Server();
    if(EN_DUMP_PNG)
    transImg->DumpImage("demo40_imgMatting");
    delete transImg;

    cout << "  =============== Case 2 ===============\n";
    cout << "    original image\n";
    RGBImg = new RGBImage();
    RGBImg->LoadImage("Image-Folder/bird.jpg");
    if(EN_X_SERVER)
    RGBImg->Display_X_Server();
    delete RGBImg;

    cout << "    matted image (mode = remove_blurred)\n";
    mattingObj.setMode(mattingObj.remove_blurred);
    transImg = mattingObj.applyMatting("Image-Folder/bird.jpg"); 
    if(EN_X_SERVER)
    transImg->Display_X_Server();
    if(EN_DUMP_PNG)
    transImg->DumpImage("demo41_imgMatting");
    delete transImg;

    cout << "  =============== Case 3 ===============\n";
    cout << "    original image\n";
    RGBImg = new RGBImage();
    RGBImg->LoadImage("Image-Folder/ladybug.jpg");
    if(EN_X_SERVER)
    RGBImg->Display_X_Server();
    delete RGBImg;

    cout << "    matted image (mode = remove_blurred_smoothly)\n";
    mattingObj.setMode(mattingObj.remove_blurred_smoothly);
    transImg = mattingObj.applyMatting("Image-Folder/ladybug.jpg");
    if(EN_X_SERVER)
    transImg->Display_X_Server();
    if(EN_DUMP_PNG)
    transImg->DumpImage("demo42_imgMatting");
    delete transImg;

    cout << "  =============== Case 4 ===============\n";
    cout << "    original image\n";
    RGBImg = new RGBImage();
    RGBImg->LoadImage("Image-Folder/texts.jpg");
    if(EN_X_SERVER)
    RGBImg->Display_X_Server();
    delete RGBImg;

    cout << "    matted image (mode = extract_text)\n";
    mattingObj.setMode(mattingObj.extract_text);
    transImg = mattingObj.applyMatting("Image-Folder/texts.jpg");
    if(EN_X_SERVER)
    transImg->Display_X_Server();
    if(EN_DUMP_PNG)
    transImg->DumpImage("demo43_imgMatting");
    delete transImg;

    cout << "  =============== Case 5 ===============\n";
    cout << "    original image\n";
    RGBImg = new RGBImage();
    RGBImg->LoadImage("Image-Folder/car.jpg");
    if(EN_X_SERVER)
    RGBImg->Display_X_Server();
    delete RGBImg;

    cout << "    matted image (mode = remove_blurred)\n";
    mattingObj.setMode(mattingObj.remove_blurred);
    transImg = mattingObj.applyMatting("Image-Folder/car.jpg");
    if(EN_X_SERVER)
    transImg->Display_X_Server();
    if(EN_DUMP_PNG)
    transImg->DumpImage("demo44_imgMatting");
    delete transImg;
    
    #endif
// ^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

    return 0;
}
