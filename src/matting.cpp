#include "matting.h"
#include "transparent_image.h"
#include "data_loader.h"
#include "bit_field_filter.h"   // For applySobelGradient
#include <queue> // For std::queue

// Image matting with simple threshold of color intensity
/*transparentImage* matting::applyMatting(string orignPath) {
    Data_Loader temp_loader;
    int w, h;
    int ***pixels = temp_loader.Load_RGB(orignPath, &w, &h);

    int **alpha = new int *[h];
    for (int j = 0; j < h; ++j) {
        alpha[j] = new int[w];
        for (int i = 0; i < w; ++i) {
            // Simple threshold based on intensity for demonstration purposes
            int intensity = (pixels[j][i][0] + pixels[j][i][1] + pixels[j][i][2]) / 3;
            if (intensity > 128) { // You can adjust the threshold value
                alpha[j][i] = 255; // Fully opaque
            } else {
                alpha[j][i] = 0;   // Fully transparent
            }
        }
    }
    return new transparentImage(w, h, pixels, alpha);
}*/


// Flood fill algorithm to fill enclosed areas
void floodFill(int **alpha, int w, int h, int x, int y) {
    std::queue<std::pair<int, int>> q;
    q.push({x, y});

    while (!q.empty()) {
        auto [cx, cy] = q.front();
        q.pop();

        // Not marking if it's on the edge
        if (cx < 0 || cx >= w || cy < 0 || cy >= h || alpha[cy][cx] == 255 || alpha[cy][cx] == 128)
            continue;

        alpha[cy][cx] = 128; // Mark as visited

        q.push({cx + 1, cy});
        q.push({cx - 1, cy});
        q.push({cx, cy + 1});
        q.push({cx, cy - 1});
    }
}

// Image matting which preserve the object with sharp edges
transparentImage* matting::applyMatting(string orignPath) {
    Data_Loader temp_loader;
    int w, h;
    int ***pixels = temp_loader.Load_RGB(orignPath, &w, &h);

    int **alpha = new int *[h];
    int **edges = new int *[h];

    for (int j = 0; j < h; ++j) {
        alpha[j] = new int[w];
        edges[j] = new int[w];
        std::fill(alpha[j], alpha[j] + w, 0); // Initialize alpha to fully transparent
    }

    // Convert the original RGB image into grayscale image
    for(int j = 0; j < h; ++j){
        for(int i = 0; i < w; ++i){
            edges[j][i] = (pixels[j][i][0] + pixels[j][i][1] + pixels[j][i][2]) / 3;
        }
    }

    // Eliminating noise then apply edge detection
    photo_filter temp_filter;
    temp_filter.applyMedianFilter(edges, w, h);
    temp_filter.applySobelGradient(edges, w, h);

    // Mark edge pixels as opaque
    for (int y = 1; y < h - 1; ++y) {
        for (int x = 1; x < w - 1; ++x) {
            if (edges[y][x] > 30) { // Edge threshold (50 in "mattImg.png", 40 in "mattImg1.png")
                alpha[y][x] = 255; // Fully opaque
            }
        }
    }

    // Flood fill from borders to find non-enclosed areas
    for (int x = 0; x < w; ++x) {
        if (alpha[0][x] == 0) floodFill(alpha, w, h, x, 0);
        if (alpha[h - 1][x] == 0) floodFill(alpha, w, h, x, h - 1);
    }
    for (int y = 0; y < h; ++y) {
        if (alpha[y][0] == 0) floodFill(alpha, w, h, 0, y);
        if (alpha[y][w - 1] == 0) floodFill(alpha, w, h, w - 1, y);
    }

    // Set enclosed areas to opaque
    for (int y = 1; y < h - 1; ++y) {
        for (int x = 1; x < w - 1; ++x) {
            if (alpha[y][x] == 0) {
                alpha[y][x] = 255; // Fully opaque
            } else if (alpha[y][x] == 128) {
                alpha[y][x] = 0; // Fully transparent
            }
        }
    }

    // set the boundary of the image to be transparent
    for(int i = 0; i < w; ++i){
        alpha[0][i] = 0;
        alpha[h-1][i] = 0;
    }
    for(int j = 1; j < h-1; ++j){
        alpha[j][0] = 0;
        alpha[j][w-1] = 0;
    }

    // Clean up edges array
    for (int j = 0; j < h; ++j) {
        delete[] edges[j];
    }
    delete[] edges;

    return new transparentImage(w, h, pixels, alpha);
}