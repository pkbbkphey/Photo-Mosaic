#include "bit_field_filter.h"
#include <iostream>
#include <cmath>

using namespace std;

photo_filter::photo_filter(){}

// Function to apply a Box Filter to the image
void photo_filter::applyBoxFilter(int **pixels, int w, int h) {
    int **temp = new int*[h];
    for (int i = 0; i < h; ++i) {
        temp[i] = new int[w];
        for (int j = 0; j < w; ++j) {
            temp[i][j] = pixels[i][j];
        }
    }

    int kernelSize = 3; // Adjust kernel size as needed
    int kernelHalf = kernelSize / 2;

    for (int i = kernelHalf; i < h - kernelHalf; ++i) {
        for (int j = kernelHalf; j < w - kernelHalf; ++j) {
            int sum = 0;
            for (int m = -kernelHalf; m <= kernelHalf; ++m) {
                for (int n = -kernelHalf; n <= kernelHalf; ++n) {
                    sum += pixels[i + m][j + n];
                }
            }
            temp[i][j] = sum / (kernelSize * kernelSize);
        }
    }

    // Copying back the filtered image
    for (int i = 0; i < h; ++i) {
        for (int j = 0; j < w; ++j) {
            pixels[i][j] = temp[i][j];
        }
        delete[] temp[i];
    }
    delete[] temp;
}

// Function to apply the Sobel Gradient Filter to the image
void photo_filter::applySobelGradient(int **pixels, int w, int h) {
    // Sobel operator kernels
    int kernelX[3][3] = {{-1, 0, 1},
                          {-2, 0, 2},
                          {-1, 0, 1}};

    int kernelY[3][3] = {{-1, -2, -1},
                          {0,  0,  0},
                          {1,  2,  1}};

    int **temp = new int*[h];
    for (int i = 0; i < h; ++i) {
        temp[i] = new int[w];
        for (int j = 0; j < w; ++j) {
            temp[i][j] = pixels[i][j];
        }
    }

    for (int i = 1; i < h - 1; ++i) {
        for (int j = 1; j < w - 1; ++j) {
            int sumX = 0, sumY = 0;
            for (int m = -1; m <= 1; ++m) {
                for (int n = -1; n <= 1; ++n) {
                    sumX += pixels[i + m][j + n] * kernelX[m + 1][n + 1];
                    sumY += pixels[i + m][j + n] * kernelY[m + 1][n + 1];
                }
            }
            // Calculating magnitude of gradient
            temp[i][j] = sqrt(sumX * sumX + sumY * sumY);
        }
    }

    // Copying back the filtered image
    for (int i = 0; i < h; ++i) {
        for (int j = 0; j < w; ++j) {
            pixels[i][j] = temp[i][j];
        }
        delete[] temp[i];
    }
    delete[] temp;
}