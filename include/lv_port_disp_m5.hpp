/**
 * @file lv_port_disp_m5.hpp
 *
 */

/*Copy this file as "lv_port_disp.c" and set this value to "1" to enable content*/
#if 1
/*********************
 *      INCLUDES
 *********************/
#include "lv_port_disp_template.h"

/*********************
 *      DEFINES
 *********************/
#ifndef MY_DISP_HOR_RES
#warning Please define or replace the macro MY_DISP_HOR_RES with the actual screen width, default value 320 is used for now.
#define MY_DISP_HOR_RES    320
#endif

#ifndef MY_DISP_VER_RES
#warning Please define or replace the macro MY_DISP_VER_RES with the actual screen height, default value 240 is used for now.
#define MY_DISP_VER_RES    240
#endif

#define BYTE_PER_PIXEL (LV_COLOR_FORMAT_GET_SIZE(LV_COLOR_FORMAT_RGB565)) /*will be 2 for RGB565 */

/**********************
 *      TYPEDEFS
 **********************/

/**********************
 *  STATIC PROTOTYPES
 **********************/
static void disp_init();

static void disp_flush(lv_display_t *disp, const lv_area_t *area, uint8_t *px_map);

static void touch_init();

/**********************
 *  STATIC VARIABLES
 **********************/

/**********************
 *      MACROS
 **********************/

/**********************
 *   GLOBAL FUNCTIONS
 **********************/

inline void lv_port_disp_init() {
    disp_init();
    lv_init();

    // 创建Display
    lv_display_t *disp = lv_display_create(MY_DISP_HOR_RES, MY_DISP_VER_RES);
    lv_display_set_flush_cb(disp, disp_flush);

    // 创建显示缓冲区，必须要开启PSRAM，否则内存不够！
    constexpr auto buffer_size = (MY_DISP_HOR_RES * MY_DISP_VER_RES * BYTE_PER_PIXEL);
    auto *buf_1_1_d = ps_malloc(buffer_size);
    lv_display_set_buffers(disp, buf_1_1_d, nullptr, buffer_size, LV_DISPLAY_RENDER_MODE_PARTIAL);

    // 设置刷新回调
    lv_tick_set_cb([]() -> uint32_t { return esp_timer_get_time() / 1000; });

    // 初始化触摸
    touch_init();
}

/**********************
 *   STATIC FUNCTIONS
 **********************/

constexpr uint8_t FULL_REFRESH_INTERVAL = 20; // 局部刷新次数
constexpr uint32_t MIN_FULL_REFRESH_INTERVAL_MS = 5000; // 最小刷新间隔 ms
static uint8_t flush_counter = 0;
static uint32_t last_full_refresh_time = 0;
static int NEED_FORCE_REFRESH = 0;

static void handle_global_refresh_counter() {
    flush_counter++;
    const uint32_t now = millis();

    // 判断是否需要进行全屏刷新
    if (!NEED_FORCE_REFRESH && flush_counter >= FULL_REFRESH_INTERVAL && (now - last_full_refresh_time) >=
        MIN_FULL_REFRESH_INTERVAL_MS) {
        Serial.println("Setting flag to full screen refresh to clear ghosting...");

        NEED_FORCE_REFRESH = 1;

        flush_counter = 0;
        last_full_refresh_time = now;
    }
}

static void disp_init() {
    M5.Display.setRotation(0);
}

static void touch_init() {
    lv_indev_t *indev = lv_indev_create();
    lv_indev_set_type(indev, LV_INDEV_TYPE_POINTER);
    lv_indev_set_read_cb(indev, [](lv_indev_t *_index, lv_indev_data_t *data) {
        M5_UPDATE();
        const auto count = M5.Touch.getCount();

        if (count == 0) {
            data->state = LV_INDEV_STATE_RELEASED;
        } else {
            const auto touch = M5.Touch.getDetail(0);
            data->state = LV_INDEV_STATE_PRESSED;
            data->point.x = touch.x;
            data->point.y = touch.y;
        }
    });
}

volatile bool disp_flush_enabled = true;

inline void disp_enable_update() {
    disp_flush_enabled = true;
}

inline void disp_disable_update() {
    disp_flush_enabled = false;
}

static void disp_flush(lv_display_t *disp_drv, const lv_area_t *area, uint8_t *px_map) {
    if (!disp_flush_enabled) {
        lv_display_flush_ready(disp_drv);
        return;
    }

    const uint32_t w = area->x2 - area->x1 + 1;
    const uint32_t h = area->y2 - area->y1 + 1;

    handle_global_refresh_counter();

    M5.Display.startWrite();
    M5.Display.setWindow(area->x1, area->y1, area->x2, area->y2);
    M5.Display.writePixelsDMA((uint16_t *) px_map, w * h);
    M5.Display.endWrite();

    lv_display_flush_ready(disp_drv);
}

#else /*Enable this file at the top*/

/*This dummy typedef exists purely to silence -Wpedantic.*/
typedef int keep_pedantic_happy;
#endif
