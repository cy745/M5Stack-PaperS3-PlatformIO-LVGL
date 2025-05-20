#include "main.hpp"
#include "M5Unified.h"
#include "FS.h"
#include <LittleFS.h>
#include "lv_port_disp_m5.hpp"

uint32_t my_tick_get_cb() {
    return esp_timer_get_time() / 1000;
}

lv_obj_t *label;

void setup() {
    M5_BEGIN();
    Serial.begin(115200);
    M5.Power.begin();

    lv_init();
    lv_tick_set_cb(&my_tick_get_cb);
    lv_port_disp_init();

    if (!LittleFS.begin()) {
        Serial.println("Failed to mount LittleFS");
    } else {
        Serial.println("LittleFS mounted");
    }

    label = lv_label_create(lv_screen_active());
    lv_label_set_text(label, "Hello Arduino, I'm LVGL!");

    Serial.println("Start drawing!");
}

void loop() {
    M5_UPDATE();
    lv_timer_handler();
}
