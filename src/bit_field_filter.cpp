#include "bit_field_filter.h"
#include <iostream>
#include <cmath>
#include <algorithm>    // for "Median Filter", "Contrast Stretching Filter"
#include <vector>       // for "Median Filter", "Contrast Stretching Filter"

using namespace std;

photo_filter::photo_filter(){}

void photo_filter::apply(int **pixels, int w, int h, int8_t option){
    if(option & BOX)        this->applyBoxFilter(pixels, w, h);
    if(option & SOBEL)      this->applySobelGradient(pixels, w, h);
    if(option & CONTRAST)   this->applyContrastStretching(pixels, w, h);
    if(option & MOSAIC)     this->applyMosaicFilter(pixels, w, h, 10);
    if(option & MEDIAN)     this->applyMedianFilter(pixels, w, h);
    if(option & ANISOTROPIC)this->applyAnisotropicDiffusion(pixels, w, h, 30, 0.5, 50); // 15, 0.25, 20) 10, 0.3, 18)
}

void photo_filter::apply(int ***pixels, int w, int h, int8_t option){
    if(option & BOX)        this->applyBoxFilter(pixels, w, h);
    if(option & SOBEL)      this->applySobelGradient(pixels, w, h);
    if(option & CONTRAST)   this->applyContrastStretching(pixels, w, h);
    if(option & MOSAIC)     this->applyMosaicFilter(pixels, w, h, 10);
    if(option & MEDIAN)     this->applyMedianFilter(pixels, w, h);
}

void photo_filter::apply_order(int **pixels, int w, int h, int order){
    // Arrays to store the order of each filter
    int orders[5];

    // Extract the order of each filter from the 5-digit decimal number
    orders[0] = order % 10;
    orders[1] = (order / 10) % 10;
    orders[2] = (order / 100) % 10;
    orders[3] = (order / 1000) % 10;
    orders[4] = (order / 10000) % 10;

    // Apply the filters in the specified order
    for (int i = 1; i <= 5; ++i) {
        if(orders[0] == i)      {
            applyBoxFilter(pixels, w, h);
        }
        else if(orders[1] == i) {
            applySobelGradient(pixels, w, h);
        }
        else if(orders[2] == i) {
            applyContrastStretching(pixels, w, h);
        }
        else if(orders[3] == i) {
            applyMosaicFilter(pixels, w, h, 10);
        }
        else if(orders[4] == i) {
            applyMedianFilter(pixels, w, h);
        }
    }
    // cout << "      finish\n";
}

void photo_filter::apply_order(int ***pixels, int w, int h, int order){
    // Arrays to store the order of each filter
    int orders[5];

    // Extract the order of each filter from the 5-digit decimal number
    orders[0] = order % 10;
    orders[1] = (order / 10) % 10;
    orders[2] = (order / 100) % 10;
    orders[3] = (order / 1000) % 10;
    orders[4] = (order / 10000) % 10;

    // Apply the filters in the specified order
    for (int i = 1; i <= 5; ++i) {
        if(orders[0] == i)      {
            applyBoxFilter(pixels, w, h);
        }
        else if(orders[1] == i) {
            applySobelGradient(pixels, w, h);
        }
        else if(orders[2] == i) {
            applyContrastStretching(pixels, w, h);
        }
        else if(orders[3] == i) {
            applyMosaicFilter(pixels, w, h, 10);
        }
        else if(orders[4] == i) {
            applyMedianFilter(pixels, w, h);
        }
    }
    // cout << "      finish\n";
}

//===========================================================================================
//----------------------------      GRAY IMAGE FILTERS      ---------------------------------
//===========================================================================================

void computeGradients(int** pixels, int w, int h, std::vector<std::vector<double>>& gradientMagnitude, std::vector<std::vector<double>>& gradientDirection) {
    for (int y = 0; y < h; ++y) {
        for (int x = 0; x < w; ++x) {
            double gx = (x < w - 1) ? pixels[y][x + 1] - pixels[y][x] : 0;
            double gy = (y < h - 1) ? pixels[y + 1][x] - pixels[y][x] : 0;
            gradientMagnitude[y][x] = sqrt(gx * gx + gy * gy);
            gradientDirection[y][x] = atan2(gy, gx);
        }
    }
}

double computeWeight(double diff, double kappa) {
    return exp(-(diff * diff) / (kappa * kappa));
}

void photo_filter::applyAnisotropicDiffusion(int** pixels, int w, int h, int iterations, double lambda, double kappa) {
    cout << "      gray- Anisotropic Diffusion...\n";
    // Temporary buffer for the smoothed image
    std::vector<std::vector<int>> smoothedImage(h, std::vector<int>(w));

    // Compute gradient magnitude and direction
    std::vector<std::vector<double>> gradientMagnitude(h, std::vector<double>(w));
    std::vector<std::vector<double>> gradientDirection(h, std::vector<double>(w));
    computeGradients(pixels, w, h, gradientMagnitude, gradientDirection);

    // Apply anisotropic diffusion
    for (int iter = 0; iter < iterations; ++iter) {
        for (int y = 0; y < h; ++y) {
            for (int x = 0; x < w; ++x) {
                double c = gradientMagnitude[y][x];

                double nx = (x < w - 1) ? gradientMagnitude[y][x + 1] : c;
                double ny = (y < h - 1) ? gradientMagnitude[y + 1][x] : c;
                double n = sqrt(nx * nx + ny * ny);
                double theta = gradientDirection[y][x];
                double diff = n - c;
                double weight = computeWeight(diff, kappa);

                // Update pixel intensity using anisotropic diffusion equation
                double updatedIntensity = pixels[y][x] + lambda * weight * diff * cos(2 * theta);
                smoothedImage[y][x] = std::clamp(static_cast<int>(round(updatedIntensity)), 0, 255);
            }
        }
        // Update the original image with the smoothed image
        for (int y = 0; y < h; ++y) {
            for (int x = 0; x < w; ++x) {
                pixels[y][x] = smoothedImage[y][x];
            }
        }
        // Recompute gradients after each iteration for better results
        computeGradients(pixels, w, h, gradientMagnitude, gradientDirection);
    }
}

// Anisotropic diffusion function (deprecated)
/*void photo_filter::applyAnisotropicDiffusion(int** pixels, int w, int h, int iterations, double lambda, double kappa) {
    // Temporary buffer for the smoothed image
    std::vector<std::vector<int>> smoothedImage(h, std::vector<int>(w));

    // Compute gradient magnitude and direction
    std::vector<std::vector<double>> gradientMagnitude(h, std::vector<double>(w));
    std::vector<std::vector<double>> gradientDirection(h, std::vector<double>(w));
    for (int y = 0; y < h; ++y) {
        for (int x = 0; x < w; ++x) {
            double gx = (x < w - 1) ? pixels[y][x + 1] - pixels[y][x] : 0;
            double gy = (y < h - 1) ? pixels[y + 1][x] - pixels[y][x] : 0;
            gradientMagnitude[y][x] = sqrt(gx * gx + gy * gy);
            gradientDirection[y][x] = atan2(gy, gx);
        }
    }

    // Apply anisotropic diffusion
    for (int iter = 0; iter < iterations; ++iter) {
        for (int y = 0; y < h; ++y) {
            for (int x = 0; x < w; ++x) {
                double c = gradientMagnitude[y][x];
                double nx = (x < w - 1) ? gradientMagnitude[y][x + 1] : c;
                double ny = (y < h - 1) ? gradientMagnitude[y + 1][x] : c;
                double n = sqrt(nx * nx + ny * ny);
                double theta = gradientDirection[y][x];
                double diff = n - c;
                double weight = exp(-(diff * diff) / (kappa * kappa));

                // Update pixel intensity using anisotropic diffusion equation
                double updatedIntensity = pixels[y][x] + lambda * weight * diff * cos(2 * theta);
                smoothedImage[y][x] = round(updatedIntensity);
            }
        }
        // Update the original image with the smoothed image
        for (int y = 0; y < h; ++y) {
            for (int x = 0; x < w; ++x) {
                pixels[y][x] = smoothedImage[y][x];
            }
        }
    }
}*/



// Box Filter for gray image
void photo_filter::applyBoxFilter(int **pixels, int w, int h) {
    cout << "      gray- Box Filter...\n";

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
    cout << "      gray- Sobel Gradient...\n";

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
    cout << "      gray- Contrast Stretching...\n";

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
    cout << "      gray- Mosaic Filter...\n";

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
    cout << "      gray- Median Filter...\n";

    int kernelSize = 7;
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
    cout << "      RGB- Box Filter...\n";

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
    cout << "      RGB- Sobel Gradient...\n";

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
    cout << "      RGB- Contrast Stretching...\n";

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
    cout << "      RGB- Mosaic Filter...\n";

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
    cout << "      RGB- Median Filter...\n";

    int kernelSize = 7;
    int kernelHalf = kernelSize / 2;

    // Create a temporary buffer for the filtered image
    int ***temp = new int**[h];
    for (int i = 0; i < h; ++i) {
        temp[i] = new int*[w];
        for (int j = 0; j < w; ++j) {
            temp[i][j] = new int[3];
        }
    }

    // Apply median filter
    for (int i = 0; i < h; ++i) {
        for (int j = 0; j < w; ++j) {
            for (int c = 0; c < 3; ++c) {
                vector<int> neighborhood;

                // Collect neighboring pixels
                for (int m = -kernelHalf; m <= kernelHalf; ++m) {
                    for (int n = -kernelHalf; n <= kernelHalf; ++n) {
                        int y = i + m;
                        int x = j + n;
                        // Check boundaries
                        if (x >= 0 && x < w && y >= 0 && y < h) {
                            neighborhood.push_back(pixels[y][x][c]);
                        }
                    }
                }

                // Sort the neighborhood and find the median
                sort(neighborhood.begin(), neighborhood.end());
                temp[i][j][c] = neighborhood[neighborhood.size() / 2];
            }
        }
    }

    // Copy the filtered image back to the original pixels array
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


