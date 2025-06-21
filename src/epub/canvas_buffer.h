//
// Created by miku on 25-6-8.
//

#ifndef CANVAS_BUFFER_H
#define CANVAS_BUFFER_H
#include <cstdint>

class canvas_buffer {
    int width = 0;
    int height = 0;
    int window_x = 0;
    int window_y = 0;
    int window_w = 0;
    int window_h = 0;

    int output_size = 0;
    void *output = nullptr;

public:
    canvas_buffer(int width, int height);

    void *getOutput() const { return output; }
    int getOutputSize() const { return output_size; }
    int getWidth() const { return width; }
    int getHeight() const { return height; }

    void setWindow(int x, int y, int w, int h) {
        this->window_x = x;
        this->window_y = y;
        this->window_w = w;
        this->window_h = h;
    }

    int pushPixels(void *pixels, int bpp);
};


#endif //CANVAS_BUFFER_H
