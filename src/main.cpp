#include "main.hpp"
#include "M5Unified.h"
#include "LittleFS.h"
#include "lv_port_disp_m5.hpp"
#include "ui.h"

void setup() {
    esp_spiram_add_to_heapalloc();
    M5_BEGIN();
    Serial.begin(115200);
    M5.Power.begin();

    if (!LittleFS.begin()) {
        Serial.println("Failed to mount LittleFS");
    } else {
        Serial.println("LittleFS mounted");
    }

    lv_init();
    lv_tick_set_cb([]() -> uint32_t { return esp_timer_get_time() / 1000; });
    lv_port_disp_init();

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

    Serial.printf("PSRAM size: %d\n", esp_spiram_get_size());
    Serial.printf("Heap free size: %d\n", heap_caps_get_free_size(MALLOC_CAP_8BIT));
    Serial.printf("Heap total size: %d\n", heap_caps_get_total_size(MALLOC_CAP_8BIT));
    Serial.printf("Fs total size: %d\n", LittleFS.totalBytes());
    Serial.printf("Fs used size: %d\n", LittleFS.usedBytes());

    Serial.println("Start drawing!");
    ui_init("Z:/");
    lv_screen_load(home_create());
}

void loop() {
    lv_timer_handler();
    vTaskDelay(1);
}
