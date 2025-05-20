#include "main.hpp"
#include "M5Unified.h"
#include "FS.h"
#include <LittleFS.h>
#include "lv_port_disp_m5.hpp"

uint32_t my_tick_get_cb() {
    return esp_timer_get_time() / 1000;
}

void my_input_read_cb(lv_indev_t *indev, lv_indev_data_t *data) {
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
}

static void event_handler(lv_event_t *e) {
    const lv_event_code_t code = lv_event_get_code(e);

    if (code == LV_EVENT_CLICKED) {
        Serial.println("Clicked");
    } else if (code == LV_EVENT_VALUE_CHANGED) {
        Serial.println("Toggled");
    }
}

void lv_example_button_1() {
    lv_obj_t *label;

    lv_obj_t *btn1 = lv_button_create(lv_screen_active());
    lv_obj_add_event_cb(btn1, event_handler, LV_EVENT_ALL, NULL);
    lv_obj_align(btn1, LV_ALIGN_CENTER, 0, -40);
    lv_obj_remove_flag(btn1, LV_OBJ_FLAG_PRESS_LOCK);

    label = lv_label_create(btn1);
    lv_label_set_text(label, "Button");
    lv_obj_center(label);

    lv_obj_t *btn2 = lv_button_create(lv_screen_active());
    lv_obj_add_event_cb(btn2, event_handler, LV_EVENT_ALL, NULL);
    lv_obj_align(btn2, LV_ALIGN_CENTER, 0, 40);
    lv_obj_add_flag(btn2, LV_OBJ_FLAG_CHECKABLE);
    lv_obj_set_height(btn2, LV_SIZE_CONTENT);

    label = lv_label_create(btn2);
    lv_label_set_text(label, "Toggle");
    lv_obj_center(label);
}

void setup() {
    esp_spiram_add_to_heapalloc();
    M5_BEGIN();
    Serial.begin(115200);
    M5.Power.begin();

    lv_init();
    lv_tick_set_cb(&my_tick_get_cb);
    lv_port_disp_init();

    lv_indev_t *indev = lv_indev_create();
    lv_indev_set_type(indev, LV_INDEV_TYPE_POINTER);
    lv_indev_set_read_cb(indev, my_input_read_cb);

    if (!LittleFS.begin()) {
        Serial.println("Failed to mount LittleFS");
    } else {
        Serial.println("LittleFS mounted");
    }

    Serial.printf("PSRAM size: %d\n", esp_spiram_get_size());
    Serial.printf("Heap free size: %d\n", heap_caps_get_free_size(MALLOC_CAP_8BIT));
    Serial.printf("Heap total size: %d\n", heap_caps_get_total_size(MALLOC_CAP_8BIT));

    Serial.println("Start drawing!");
    lv_example_button_1();
}

void loop() {
    lv_timer_handler();
    vTaskDelay(1);
}
