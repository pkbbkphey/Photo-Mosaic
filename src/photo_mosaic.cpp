#include "photo_mosaic.h"
#include "rgb_image.h"
#include "image.h"
#include "data_loader.h"
#include <vector>
#include <iostream>
using namespace std;

RGBImage* PhotoMosaic::generate(string tilePath, string orignPath){
    cout << "      starting...\n";
    Data_Loader temp_loader;
    vector<string> tileNames;
    vector<float> tileRAvg, tileGAvg, tileBAvg;
    temp_loader.List_Directory(tilePath, tileNames);
    cout << "      analyzing small photos...\n";
    for(auto tileIt: tileNames){
        int w, h;
        int ***pixels = temp_loader.Load_RGB(tileIt, &w, &h);
        // vvvvvvvv find average RGB value of a tile vvvvvvvv
        float rAvg = 0, gAvg = 0, bAvg = 0;
        int smp_cnt = 0;
        for(int j = 0; (j < h) && (j < tileSize); ++j){
            for(int i = 0; (i < w) && (i < tileSize); ++i){
                rAvg += pixels[j][i][0];
                gAvg += pixels[j][i][1];
                bAvg += pixels[j][i][2];
                ++ smp_cnt;
            }
        }
        rAvg = rAvg / smp_cnt;  // (w * h)
        gAvg = gAvg / smp_cnt;
        bAvg = bAvg / smp_cnt;
        tileRAvg.push_back(rAvg);
        tileGAvg.push_back(gAvg);
        tileBAvg.push_back(bAvg);

        // Clean up pixels
        for(int j = 0; j < h; ++j){
            for(int i = 0; i < w; ++i){
                delete[] pixels[j][i];
            }
            delete[] pixels[j];
        }
        delete[] pixels;
        // ^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^
    }
    
    cout << "      reading big photo and new the mosaic photo...\n";
    int orignW, orignH; 
    int ***orignPixels = temp_loader.Load_RGB(orignPath, &orignW, &orignH);
    // int mosaicPixels[orignH][orignW][3];
    int ***mosaicPixels = new int **[orignH];
    for(int j = 0; j < orignH; ++j){
        mosaicPixels[j] = new int *[orignW];
        for(int i = 0; i < orignW; ++i){
            mosaicPixels[j][i] = new int [3];
        }
    }

    cout << "      generating mosaic photo...\n";
    for(int gridY = 0; gridY < orignH; gridY += tileSize){
        for(int gridX = 0; gridX < orignW; gridX += tileSize){

            // vvvvvvvv find average RGB value of a tile in original photo vvvvvvvv
            float rAvg = 0, gAvg = 0, bAvg = 0;
            int smp_cnt = 0;
            for(int deltaY = 0; (deltaY < tileSize) && ((gridY + deltaY) < orignH); ++deltaY){
                for(int deltaX = 0; (deltaX < tileSize) && ((gridX + deltaX) < orignW); ++deltaX){
                    rAvg += orignPixels[gridY + deltaY][gridX + deltaX][0];
                    gAvg += orignPixels[gridY + deltaY][gridX + deltaX][1];
                    bAvg += orignPixels[gridY + deltaY][gridX + deltaX][2];
                    ++smp_cnt;
                }
            }
            rAvg = rAvg / smp_cnt;    // (tileSize * tileSize)
            gAvg = gAvg / smp_cnt;
            bAvg = bAvg / smp_cnt;
            // ^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

            // vvvvvv find the tile that matches the best vvvvvv
            double min_val = 16777215;
            int min_index = 0;
            for(unsigned int idx = 0; idx < tileNames.size(); ++idx){
                int val =   (rAvg - tileRAvg[idx]) * (rAvg - tileRAvg[idx]) +
                            (gAvg - tileGAvg[idx]) * (gAvg - tileGAvg[idx]) +
                            (bAvg - tileBAvg[idx]) * (bAvg - tileBAvg[idx]);
                if(val < min_val){
                    min_val = val;
                    min_index = idx;
                }
            }
            // ^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

            // vvvvvvvvvv place the tile into place vvvvvvvvvvvv
            int tileW, tileH; 
            int ***tilePixels = temp_loader.Load_RGB(tileNames[min_index], &tileW, &tileH);
            for( int deltaY = 0; (deltaY < tileSize) && (deltaY < tileH) && ((gridY + deltaY) < orignH); ++deltaY ){
                for( int deltaX = 0; (deltaX < tileSize) && (deltaX < tileW) && ((gridX + deltaX) < orignW); ++deltaX ){
                    mosaicPixels[gridY + deltaY][gridX + deltaX][0] = tilePixels[deltaY][deltaX][0];
                    mosaicPixels[gridY + deltaY][gridX + deltaX][1] = tilePixels[deltaY][deltaX][1];
                    mosaicPixels[gridY + deltaY][gridX + deltaX][2] = tilePixels[deltaY][deltaX][2];
                }
            }
            // Clean up tilePixels
            for(int j = 0; j < tileH; ++j){
                for(int i = 0; i < tileW; ++i){
                    delete[] tilePixels[j][i];
                }
                delete[] tilePixels[j];
            }
            delete[] tilePixels;
            tilePixels = nullptr;
            // ^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^
        }
    }

    RGBImage* mosaicObj = new RGBImage(orignW, orignH, mosaicPixels);

    // Clean up orignPixels
    for(int j = 0; j < orignH; ++j){
        for(int i = 0; i < orignW; ++i){
            delete[] orignPixels[j][i];
        }
        delete[] orignPixels[j];
    }
    delete[] orignPixels;

    cout << "      finish!\n";
    return mosaicObj;
}