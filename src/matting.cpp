#include "matting.h"
#include "transparent_image.h"
#include "data_loader.h"
#include "bit_field_filter.h"   // For applySobelGradient
#include <queue> // For std::queue
#include <vector> // For std::vector
#include <map> // For std::map

extern bool FOR_VAL_GRIND;   // defined in main.cpp
// #define EN_PAIR !FOR_VAL_GRIND

void matting::setMode(int _mode){
    mode = _mode;
}

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


// Flood fill algorithm to eliminate non-enclosed area
void floodFill(int **alpha, int w, int h, int x, int y) {
    if(! FOR_VAL_GRIND){
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
}

// Connected component analysis to remove big fragments at the image boundary
void removeBoundaryBigFragments(int **alpha, int w, int h, int maxSize){
    int label = 1;
    std::map<int, int> componentSizes;
    std::vector<std::vector<int>> labels(h, std::vector<int>(w, 0));

    for (int y = 0; y < h; ++y) {
        for (int x = 0; x < w; ++x) {
            if (((y < h/20) || (y > h*19/20) || (x < w/20) || (x > w*19/20)) &&
                    alpha[y][x] == 255 && labels[y][x] == 0) {
                int size = 0;
                std::queue<std::pair<int, int>> q;
                q.push({x, y});
                labels[y][x] = label;

                while (!q.empty()) {
                    auto [cx, cy] = q.front();
                    q.pop();
                    size++;

                    std::vector<std::pair<int, int>> neighbors = {
                        {cx + 1, cy}, {cx - 1, cy},
                        {cx, cy + 1}, {cx, cy - 1}
                    };

                    for (auto [nx, ny] : neighbors) {
                        if (nx >= 0 && nx < w && ny >= 0 && ny < h &&
                            alpha[ny][nx] == 255 && labels[ny][nx] == 0) {
                            q.push({nx, ny});
                            labels[ny][nx] = label;
                        }
                    }
                }

                componentSizes[label] = size;
                label++;
            }
        }
    }

    for (int y = 0; y < h; ++y) {
        for (int x = 0; x < w; ++x) {
            if (labels[y][x] > 0 && componentSizes[labels[y][x]] > maxSize) {
                alpha[y][x] = 0; // Make big fragments transparent
            }
        }
    }
}

// Connected component analysis to remove small fragments
void removeSmallFragments(int **alpha, int w, int h, int minSize) {
    int label = 1;
    std::map<int, int> componentSizes;
    std::vector<std::vector<int>> labels(h, std::vector<int>(w, 0));    // 2D vector of h*w, filled with 0

    for (int y = 0; y < h; ++y) {
        for (int x = 0; x < w; ++x) {
            if (alpha[y][x] == 255 && labels[y][x] == 0) {
                int size = 0;
                std::queue<std::pair<int, int>> q;
                q.push({x, y});
                labels[y][x] = label;

                while (!q.empty()) {
                    auto [cx, cy] = q.front();
                    q.pop();
                    size++;

                    std::vector<std::pair<int, int>> neighbors = {
                        {cx + 1, cy}, {cx - 1, cy},
                        {cx, cy + 1}, {cx, cy - 1}
                    };

                    for (auto [nx, ny] : neighbors) {
                        if (nx >= 0 && nx < w && ny >= 0 && ny < h &&
                            alpha[ny][nx] == 255 && labels[ny][nx] == 0) {
                            q.push({nx, ny});
                            labels[ny][nx] = label;
                        }
                    }
                }

                componentSizes[label] = size;
                label++;
            }
        }
    }

    for (int y = 0; y < h; ++y) {
        for (int x = 0; x < w; ++x) {
            if (labels[y][x] > 0 && componentSizes[labels[y][x]] < minSize) {
                alpha[y][x] = 0; // Make small fragments transparent
            }
        }
    }
}


// Image matting which preserve the object with sharp edges
transparentImage* matting::applyMatting(string orignPath) {
    Data_Loader temp_loader;
    int w, h;
    int ***pixels = temp_loader.Load_RGB(orignPath, &w, &h);

    int **alpha = new int *[h];
    for(int j = 0; j < h; ++j) alpha[j] = new int[w];


    if(mode == extract_text){
        // int **edges = new int *[h];
        // for(int j = 0; j < h; ++j) edges[j] = new int[w];

        // // ---------- Grayscale edge detecton ------------
        // // Convert the original RGB image into grayscale image
        // for(int j = 0; j < h; ++j){
        //     for(int i = 0; i < w; ++i){
        //         edges[j][i] = (pixels[j][i][0] + pixels[j][i][1] + pixels[j][i][2]) / 3;
        //     }
        // }
        // // Apply edge detection
        // photo_filter temp_filter;
        // temp_filter.applySobelGradient(edges, w, h);

        // double avg_intensity = 0;
        // for(int j = 0; j < h; ++j){
        //     for(int i = 0; i < w; ++i){
        //         avg_intensity += (pixels[j][i][0] + pixels[j][i][1] + pixels[j][i][2]);
        //     }
        // }
        // avg_intensity /= (w * h * 3);

        #define GRID_SEG 5
        for(int grid_y = 0; grid_y < h; grid_y += h/GRID_SEG){
            for(int grid_x = 0; grid_x < w; grid_x += w/GRID_SEG){
                double avg_intensity = 0;
                #define pos_x (grid_x+delta_x)
                #define pos_y (grid_y+delta_y)
                for(int delta_y = 0; (delta_y < h/GRID_SEG) && (pos_y < h); ++delta_y){
                    for(int delta_x = 0; (delta_x < w/GRID_SEG) && (pos_x < w); ++delta_x){
                        avg_intensity += (pixels[pos_y][pos_x][0] +
                                          pixels[pos_y][pos_x][1] + 
                                          pixels[pos_y][pos_x][2]);
                    }
                }
                avg_intensity /= ((w/GRID_SEG) * (h/GRID_SEG) * 3);

                for(int delta_y = 0; (delta_y < h/GRID_SEG) && (pos_y < h); ++delta_y){
                    for(int delta_x = 0; (delta_x < w/GRID_SEG) && (pos_x < w); ++delta_x){
                        int intensity = (pixels[pos_y][pos_x][0] +
                                         pixels[pos_y][pos_x][1] + 
                                         pixels[pos_y][pos_x][2]) / 3;
                        if((intensity - avg_intensity) < 23 && (intensity - avg_intensity) > -23){
                            alpha[pos_y][pos_x] = 0;    // Fully transparent
                        }
                        else{
                            alpha[pos_y][pos_x] = 255;  // Fully opaque
                        }
                    }
                }
            }
        }

        removeBoundaryBigFragments(alpha, w, h, w * h / 8000);  // 5000
        removeSmallFragments(alpha, w, h, 3);
    }



    else if(mode == remove_blurred || mode == remove_blurred_smoothly){
        int **edges = new int *[h];
        for (int j = 0; j < h; ++j) {
            edges[j] = new int[w];
            std::fill(alpha[j], alpha[j] + w, 0); // Initialize alpha to fully transparent
        }

        int EDGE_THREH = 0;
        if(mode == remove_blurred_smoothly){
            // ---------- Grayscale edge detecton ------------
            // Convert the original RGB image into grayscale image
            for(int j = 0; j < h; ++j){
                for(int i = 0; i < w; ++i){
                    edges[j][i] = (pixels[j][i][0] + pixels[j][i][1] + pixels[j][i][2]) / 3;
                }
            }
            // Eliminating noise then apply edge detection
            photo_filter temp_filter;
            EDGE_THREH = 30;   // with applyMedianFilter
            temp_filter.applyMedianFilter(edges, w, h);
            // EDGE_THREH = 50;   // without applyMedianFilter
            temp_filter.applySobelGradient(edges, w, h);
        }
        else if(mode == remove_blurred){
            // ------------- RGB edge detection ---------------
            // Replicate the RGB image and send it into sobel gradient
            EDGE_THREH = 35;
            int ***temp_pixels = new int **[h];
            for(int j = 0; j < h; ++j){
                temp_pixels[j] = new int *[w];
                for(int i = 0; i < w; ++i){
                    temp_pixels[j][i] = new int[3];
                    temp_pixels[j][i][0] = pixels[j][i][0];
                    temp_pixels[j][i][1] = pixels[j][i][1];
                    temp_pixels[j][i][2] = pixels[j][i][2];
                }
            }
            photo_filter temp_filter;
            temp_filter.applySobelGradient(temp_pixels, w, h);
            for(int j = 0; j < h; ++j){
                for(int i = 0; i < w; ++i){
                    edges[j][i] = (temp_pixels[j][i][0] + temp_pixels[j][i][1] + temp_pixels[j][i][2]);
                }
            }
            // Clean up temp_pixels array
            for (int j = 0; j < h; ++j) {
                for(int i = 0; i < w; ++i) delete[] temp_pixels[j][i];
                delete[] temp_pixels[j];
            }
            delete[] temp_pixels;
        }

        // Mark edge pixels as opaque
        for (int y = 1; y < h - 1; ++y) {
            for (int x = 1; x < w - 1; ++x) {
                if (edges[y][x] > EDGE_THREH) {
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

        // eliminate small dots or stripes
        // removeSmallFragments(alpha, w, h, 300); // size threshold (pixels)
        removeSmallFragments(alpha, w, h, w * h / 1000);

        // Clean up edges array
        for (int j = 0; j < h; ++j) {
            delete[] edges[j];
        }
        delete[] edges;
    }

    transparentImage* temp = new transparentImage(w, h, pixels, alpha);
    // // Clean up pixels array
    // if(pixels != nullptr){
    //     for(int i = 0; i < h; ++i){
    //         for(int j = 0; j < w; ++j) delete[] pixels[i][j];
    //         delete[] pixels[i];
    //     }
    //     delete[] pixels;
    //     pixels = nullptr;
    // }
    // // Clean up alpha array
    // for (int j = 0; j < h; ++j) {
    //     delete[] alpha[j];
    // }
    // delete[] alpha;

    return temp;
}