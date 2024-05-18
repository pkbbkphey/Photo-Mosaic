#include "bit_field_filter.h"
#include <iostream>
#include <cmath>
#include <algorithm>    // for "Median Filter", "Contrast Stretching Filter"
#include <vector>       // for "Median Filter", "Contrast Stretching Filter"

using namespace std;

photo_filter::photo_filter(){}

void photo_filter::apply(int **pixels, int w, int h, int8_t option){
    if(option & BOX)        applyBoxFilter(pixels, w, h);
    if(option & SOBEL)      applySobelGradient(pixels, w, h);
    if(option & CONTRAST)   applyContrastStretching(pixels, w, h);
    if(option & MOSAIC)     applyMosaicFilter(pixels, w, h, 10);
    if(option & MEDIAN)     applyMedianFilter(pixels, w, h);
}

void photo_filter::apply(int ***pixels, int w, int h, int8_t option){
    if(option & BOX)        applyBoxFilter(pixels, w, h);
    if(option & SOBEL)      applySobelGradient(pixels, w, h);
    if(option & CONTRAST)   applyContrastStretching(pixels, w, h);
    if(option & MOSAIC)     applyMosaicFilter(pixels, w, h, 10);
    if(option & MEDIAN)     applyMedianFilter(pixels, w, h);
}

//===========================================================================================
//----------------------------      GRAY IMAGE FILTERS      ---------------------------------
//===========================================================================================

// Box Filter for gray image
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

// Sobel Gradient Filter for gray image
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

// Contrast Stretching Filter for gray image
void photo_filter::applyContrastStretching(int **pixels, int w, int h) {
    std::vector<int> allPixels;
    allPixels.reserve(w * h);

    // Collect all pixel values into a vector
    for (int i = 0; i < h; ++i) {
        for (int j = 0; j < w; ++j) {
            allPixels.push_back(pixels[i][j]);
        }
    }

    // Sort the pixel values to find percentiles
    std::sort(allPixels.begin(), allPixels.end());

    // Define percentiles
    int minPercentileIndex = static_cast<int>(0.01 * allPixels.size());
    int maxPercentileIndex = static_cast<int>(0.99 * allPixels.size());

    // Get the 1st and 99th percentile values
    int minVal = allPixels[minPercentileIndex];
    int maxVal = allPixels[maxPercentileIndex];

    // Apply contrast stretching using percentile values
    for (int i = 0; i < h; ++i) {
        for (int j = 0; j < w; ++j) {
            pixels[i][j] = 255 * (pixels[i][j] - minVal) / (maxVal - minVal);
            if (pixels[i][j] < 0) pixels[i][j] = 0;
            if (pixels[i][j] > 255) pixels[i][j] = 255;
        }
    }
}

// Mosaic Filter for gray image
void photo_filter::applyMosaicFilter(int **pixels, int w, int h, int blockSize) {
    for (int i = 0; i < h; i += blockSize) {
        for (int j = 0; j < w; j += blockSize) {
            // Calculate the average color in the block
            int sum = 0;
            int count = 0;

            for (int bi = i; bi < i + blockSize && bi < h; ++bi) {
                for (int bj = j; bj < j + blockSize && bj < w; ++bj) {
                    sum += pixels[bi][bj];
                    ++count;
                }
            }

            int average = sum / count;

            // Set the block to the average color
            for (int bi = i; bi < i + blockSize && bi < h; ++bi) {
                for (int bj = j; bj < j + blockSize && bj < w; ++bj) {
                    pixels[bi][bj] = average;
                }
            }
        }
    }
}

// Median Filter for gray image
void photo_filter::applyMedianFilter(int **pixels, int w, int h) {
    int kernelSize = 10;
    int kernelHalf = kernelSize / 2;

    int **temp = new int*[h];
    for (int i = 0; i < h; ++i) {
        temp[i] = new int[w];
        for (int j = 0; j < w; ++j) {
            temp[i][j] = pixels[i][j];
        }
    }

    for (int i = kernelHalf; i < h - kernelHalf; ++i) {
        for (int j = kernelHalf; j < w - kernelHalf; ++j) {
            std::vector<int> neighborhood;
            for (int m = -kernelHalf; m <= kernelHalf; ++m) {
                for (int n = -kernelHalf; n <= kernelHalf; ++n) {
                    neighborhood.push_back(pixels[i + m][j + n]);
                }
            }
            std::sort(neighborhood.begin(), neighborhood.end());
            temp[i][j] = neighborhood[neighborhood.size() / 2];
        }
    }

    for (int i = 0; i < h; ++i) {
        for (int j = 0; j < w; ++j) {
            pixels[i][j] = temp[i][j];
        }
        delete[] temp[i];
    }
    delete[] temp;
}

//===========================================================================================
//----------------------------      RGB IMAGE FILTERS       ---------------------------------
//===========================================================================================

// Box Filter for RGB image
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

// Sobel Gradient Filter for RGB image
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

// Contrast Stretching Filter for RGB image
void photo_filter::applyContrastStretching(int ***pixels, int w, int h) {
    for (int c = 0; c < 3; ++c) { // Process each color channel independently
        std::vector<int> allPixels;
        allPixels.reserve(w * h);

        // Collect all pixel values of the current channel into a vector
        for (int i = 0; i < h; ++i) {
            for (int j = 0; j < w; ++j) {
                allPixels.push_back(pixels[i][j][c]);
            }
        }

        // Sort the pixel values to find percentiles
        std::sort(allPixels.begin(), allPixels.end());

        // Define percentiles
        int minPercentileIndex = static_cast<int>(0.01 * allPixels.size());
        int maxPercentileIndex = static_cast<int>(0.99 * allPixels.size());

        // Get the 1st and 99th percentile values
        int minVal = allPixels[minPercentileIndex];
        int maxVal = allPixels[maxPercentileIndex];

        // Apply contrast stretching using percentile values
        for (int i = 0; i < h; ++i) {
            for (int j = 0; j < w; ++j) {
                pixels[i][j][c] = 255 * (pixels[i][j][c] - minVal) / (maxVal - minVal);
                if (pixels[i][j][c] < 0) pixels[i][j][c] = 0;
                if (pixels[i][j][c] > 255) pixels[i][j][c] = 255;
            }
        }
    }
}

// Mosaic Filter for RGB image
void photo_filter::applyMosaicFilter(int ***pixels, int w, int h, int blockSize) {
    for (int i = 0; i < h; i += blockSize) {
        for (int j = 0; j < w; j += blockSize) {
            // Calculate the average color in the block
            int sum[3] = {0, 0, 0};
            int count = 0;

            for (int bi = i; bi < i + blockSize && bi < h; ++bi) {
                for (int bj = j; bj < j + blockSize && bj < w; ++bj) {
                    for (int c = 0; c < 3; ++c) {
                        sum[c] += pixels[bi][bj][c];
                    }
                    ++count;
                }
            }

            for (int c = 0; c < 3; ++c) {
                sum[c] /= count;
            }

            // Set the block to the average color
            for (int bi = i; bi < i + blockSize && bi < h; ++bi) {
                for (int bj = j; bj < j + blockSize && bj < w; ++bj) {
                    for (int c = 0; c < 3; ++c) {
                        pixels[bi][bj][c] = sum[c];
                    }
                }
            }
        }
    }
}

// Median Filter for RGB image
void photo_filter::applyMedianFilter(int ***pixels, int w, int h) {
    int kernelSize = 10;
    int kernelHalf = kernelSize / 2;

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

    for (int i = kernelHalf; i < h - kernelHalf; ++i) {
        for (int j = kernelHalf; j < w - kernelHalf; ++j) {
            for (int c = 0; c < 3; ++c) {
                std::vector<int> neighborhood;
                for (int m = -kernelHalf; m <= kernelHalf; ++m) {
                    for (int n = -kernelHalf; n <= kernelHalf; ++n) {
                        neighborhood.push_back(pixels[i + m][j + n][c]);
                    }
                }
                std::sort(neighborhood.begin(), neighborhood.end());
                temp[i][j][c] = neighborhood[neighborhood.size() / 2];
            }
        }
    }

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
