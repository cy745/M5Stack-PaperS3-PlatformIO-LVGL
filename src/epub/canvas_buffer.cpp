//
// Created by miku on 25-6-8.
//

#include "canvas_buffer.h"

#include <Esp.h>


canvas_buffer::canvas_buffer(const int width, const int height) : width(width), height(height) {
    output_size = width * height * sizeof(uint16_t);
    output = ps_malloc(output_size);
}

int canvas_buffer::pushPixels(void *pixels, int bpp) {
    if (!pixels) {
        return 0;
    }

    for (int y = window_y; y < window_y + window_h; ++y) {
        auto container_before_count = y * width + window_x;
        auto pixel_before_count = (y - window_y) * window_w;

        for (int x = 0; x < window_w; ++x) {
            memcpy((uint16_t *) output + container_before_count, (uint16_t *) pixels + pixel_before_count,
                   window_w * sizeof(uint16_t));
        }
    }
    return 1;
}
