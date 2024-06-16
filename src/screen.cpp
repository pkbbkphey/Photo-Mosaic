
#include "screen.h"
#include <vector>


// Define the static member variable
Data_Loader Screen_::imagefile;

void Screen_::displayParallel(int **pixels1, int w1, int h1, int **pixels2, int w2, int h2) {
    int combinedWidth = w1 + w2;
    int combinedHeight = std::max(h1, h2);
    
    // Create a new buffer for the combined image
    int** combinedPixels = new int*[combinedHeight];
    for (int y = 0; y < combinedHeight; ++y) {
        combinedPixels[y] = new int[combinedWidth];
        for (int x = 0; x < combinedWidth; ++x) {
            if (x < w1 && y < h1) {
                combinedPixels[y][x] = pixels1[y][x];
            }
            else if (x >= w1 && (x - w1) < w2 && y < h2) {
                combinedPixels[y][x] = pixels2[y][x - w1];
            }
            else {
                combinedPixels[y][x] = 0; // Fill the remaining area with black
            }
        }
    }
    
    // Display the combined image using X Server
    imagefile.Display_Gray_X_Server(combinedWidth, combinedHeight, combinedPixels);
    
    // Clean up the combined buffer
    for (int y = 0; y < combinedHeight; ++y) {
        delete[] combinedPixels[y];
    }
    delete[] combinedPixels;
}

void Screen_::displayParallel(int ***pixels1, int w1, int h1, int ***pixels2, int w2, int h2) {
    int combinedWidth = w1 + w2;
    int combinedHeight = std::max(h1, h2);
    
    // Create a new buffer for the combined image
    int*** combinedPixels = new int**[combinedHeight];
    for (int y = 0; y < combinedHeight; ++y) {
        combinedPixels[y] = new int*[combinedWidth];
        for (int x = 0; x < combinedWidth; ++x) {
            combinedPixels[y][x] = new int[3];
            if (x < w1 && y < h1) {
                combinedPixels[y][x][0] = pixels1[y][x][0];
                combinedPixels[y][x][1] = pixels1[y][x][1];
                combinedPixels[y][x][2] = pixels1[y][x][2];
            } else if (x >= w1 && (x - w1) < w2 && y < h2) {
                combinedPixels[y][x][0] = pixels2[y][x - w1][0];
                combinedPixels[y][x][1] = pixels2[y][x - w1][1];
                combinedPixels[y][x][2] = pixels2[y][x - w1][2];
            } else {
                combinedPixels[y][x][0] = 0;
                combinedPixels[y][x][1] = 0;
                combinedPixels[y][x][2] = 0; // Fill the remaining area with black
            }
        }
    }
    
    // Display the combined image using X Server
    imagefile.Display_RGB_X_Server(combinedWidth, combinedHeight, combinedPixels);
    
    // Clean up the combined buffer
    for (int y = 0; y < combinedHeight; ++y) {
        for (int x = 0; x < combinedWidth; ++x) {
            delete[] combinedPixels[y][x];
        }
        delete[] combinedPixels[y];
    }
    delete[] combinedPixels;
}

void Screen_::displayParallel(int ***pixels1, int w1, int h1, int ***pixels2, int** alpha2, int w2, int h2) {
    int combinedWidth = w1 + w2;
    int combinedHeight = std::max(h1, h2);
    
    // Create a new buffer for the combined image
    int*** combinedPixels = new int**[combinedHeight];
    for (int y = 0; y < combinedHeight; ++y) {
        combinedPixels[y] = new int*[combinedWidth];
        for (int x = 0; x < combinedWidth; ++x) {
            combinedPixels[y][x] = new int[3];
            if (x < w1 && y < h1) {
                combinedPixels[y][x][0] = pixels1[y][x][0];
                combinedPixels[y][x][1] = pixels1[y][x][1];
                combinedPixels[y][x][2] = pixels1[y][x][2];
            } else if (x >= w1 && (x - w1) < w2 && y < h2) {
                combinedPixels[y][x][0] = pixels2[y][x - w1][0] * alpha2[y][x - w1] / 255;
                combinedPixels[y][x][1] = pixels2[y][x - w1][1] * alpha2[y][x - w1] / 255;
                combinedPixels[y][x][2] = pixels2[y][x - w1][2] * alpha2[y][x - w1] / 255;
            } else {
                combinedPixels[y][x][0] = 0;
                combinedPixels[y][x][1] = 0;
                combinedPixels[y][x][2] = 0; // Fill the remaining area with black
            }
        }
    }
    
    // Display the combined image using X Server
    imagefile.Display_RGB_X_Server(combinedWidth, combinedHeight, combinedPixels);
    
    // Clean up the combined buffer
    for (int y = 0; y < combinedHeight; ++y) {
        for (int x = 0; x < combinedWidth; ++x) {
            delete[] combinedPixels[y][x];
        }
        delete[] combinedPixels[y];
    }
    delete[] combinedPixels;
}

void Screen_::displayParallel(int ***pixels1, int **alpha1, int w1, int h1, int ***pixels2, int** alpha2, int w2, int h2) {
    int combinedWidth = w1 + w2;
    int combinedHeight = std::max(h1, h2);
    
    // Create a new buffer for the combined image
    int*** combinedPixels = new int**[combinedHeight];
    for (int y = 0; y < combinedHeight; ++y) {
        combinedPixels[y] = new int*[combinedWidth];
        for (int x = 0; x < combinedWidth; ++x) {
            combinedPixels[y][x] = new int[3];
            if (x < w1 && y < h1) {
                combinedPixels[y][x][0] = pixels1[y][x][0] * alpha1[y][x] / 255;
                combinedPixels[y][x][1] = pixels1[y][x][1] * alpha1[y][x] / 255;
                combinedPixels[y][x][2] = pixels1[y][x][2] * alpha1[y][x] / 255;
            } else if (x >= w1 && (x - w1) < w2 && y < h2) {
                combinedPixels[y][x][0] = pixels2[y][x - w1][0] * alpha2[y][x - w1] / 255;
                combinedPixels[y][x][1] = pixels2[y][x - w1][1] * alpha2[y][x - w1] / 255;
                combinedPixels[y][x][2] = pixels2[y][x - w1][2] * alpha2[y][x - w1] / 255;
            } else {
                combinedPixels[y][x][0] = 0;
                combinedPixels[y][x][1] = 0;
                combinedPixels[y][x][2] = 0; // Fill the remaining area with black
            }
        }
    }
    
    // Display the combined image using X Server
    imagefile.Display_RGB_X_Server(combinedWidth, combinedHeight, combinedPixels);
    
    // Clean up the combined buffer
    for (int y = 0; y < combinedHeight; ++y) {
        for (int x = 0; x < combinedWidth; ++x) {
            delete[] combinedPixels[y][x];
        }
        delete[] combinedPixels[y];
    }
    delete[] combinedPixels;
}
