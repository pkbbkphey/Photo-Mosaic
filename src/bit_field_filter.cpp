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

// Function to apply a Box Filter to the RGB image
void photo_filter::applyBoxFilter(int ***pixels, int w, int h) {
    int kernelSize = 3; // Adjust kernel size as needed
    int kernelHalf = kernelSize / 2;

    // Temporary array to store filtered pixels
    int ***temp = new int**[h];
    for (int i = 0; i < h; ++i) {
        temp[i] = new int*[w];
        for (int j = 0; j < w; ++j) {
            temp[i][j] = new int[3];
            for (int c = 0; c < 3; ++c) {
                temp[i][j][c] = pixels[i][j][c];
            }
        }
    }

    // Apply the box filter
    for (int i = kernelHalf; i < h - kernelHalf; ++i) {
        for (int j = kernelHalf; j < w - kernelHalf; ++j) {
            for (int c = 0; c < 3; ++c) {
                int sum = 0;
                for (int m = -kernelHalf; m <= kernelHalf; ++m) {
                    for (int n = -kernelHalf; n <= kernelHalf; ++n) {
                        sum += pixels[i + m][j + n][c];
                    }
                }
                temp[i][j][c] = sum / (kernelSize * kernelSize);
            }
        }
    }

    // Copy filtered pixels back to the original array
    for (int i = 0; i < h; ++i) {
        for (int j = 0; j < w; ++j) {
            for (int c = 0; c < 3; ++c) {
                pixels[i][j][c] = temp[i][j][c];
            }
            delete[] temp[i][j];
        }
        delete[] temp[i];
    }
    delete[] temp;
}

// Function to apply the Sobel Gradient Filter to the RGB image
void photo_filter::applySobelGradient(int ***pixels, int w, int h) {
    // Sobel operator kernels
    int kernelX[3][3] = {{-1, 0, 1},
                          {-2, 0, 2},
                          {-1, 0, 1}};

    int kernelY[3][3] = {{-1, -2, -1},
                          {0,  0,  0},
                          {1,  2,  1}};

    // Temporary arrays to store the gradient magnitude for each color channel
    double ***magnitude = new double**[h];
    for (int i = 0; i < h; ++i) {
        magnitude[i] = new double*[w];
        for (int j = 0; j < w; ++j) {
            magnitude[i][j] = new double[3];
            for (int c = 0; c < 3; ++c) {
                magnitude[i][j][c] = 0;
            }
        }
    }

    // Compute the gradient magnitude for each color channel using the Sobel operator
    for (int i = 1; i < h - 1; ++i) {
        for (int j = 1; j < w - 1; ++j) {
            for (int c = 0; c < 3; ++c) {
                double sumX = 0, sumY = 0;
                for (int m = -1; m <= 1; ++m) {
                    for (int n = -1; n <= 1; ++n) {
                        sumX += pixels[i + m][j + n][c] * kernelX[m + 1][n + 1];
                        sumY += pixels[i + m][j + n][c] * kernelY[m + 1][n + 1];
                    }
                }
                // Calculate the magnitude of gradient for the current color channel
                magnitude[i][j][c] = sqrt(sumX * sumX + sumY * sumY);
            }
        }
    }

    // Normalize the gradient magnitude for each color channel to 0-255
    double maxMagnitude = 0;
    for (int i = 0; i < h; ++i) {
        for (int j = 0; j < w; ++j) {
            for (int c = 0; c < 3; ++c) {
                if (magnitude[i][j][c] > maxMagnitude) {
                    maxMagnitude = magnitude[i][j][c];
                }
            }
        }
    }

    for (int i = 0; i < h; ++i) {
        for (int j = 0; j < w; ++j) {
            for (int c = 0; c < 3; ++c) {
                pixels[i][j][c] = static_cast<int>((magnitude[i][j][c] / maxMagnitude) * 255);
            }
            delete[] magnitude[i][j];
        }
        delete[] magnitude[i];
    }
    delete[] magnitude;
}