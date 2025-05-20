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
    esp_spiram_add_to_heapalloc();
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

    Serial.printf("PSRAM size: %d\n", esp_spiram_get_size());
    Serial.printf("Heap free size: %d\n", heap_caps_get_free_size(MALLOC_CAP_8BIT));
    Serial.printf("Heap total size: %d\n", heap_caps_get_total_size(MALLOC_CAP_8BIT));

    Serial.println("Start drawing!");
}

void loop() {
    M5_UPDATE();
    lv_timer_handler();
}
