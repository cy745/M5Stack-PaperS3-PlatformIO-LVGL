#include "main.hpp"

#include "freetype_setup.hpp"
#include "M5Unified.h"
#include "LittleFS.h"
#include "lv_port_disp_m5.hpp"
#include "sd_card/sd_card.hpp"
#include "generated/gui_guider.h"
#include "home_screen/home_screen.h"
#include "lock_screen/lock_screen.h"
#include "status_bar/status_bar.h"

auto bookX = new int[9]{0, 170, 340, 0, 170, 340, 0, 170, 340};
auto bookY = new int[9]{0, 0, 0, 250, 250, 250, 500, 500, 500};
lv_ui guider_ui = lv_ui{};

void check_for_force_refresh() {
    if (NEED_FORCE_REFRESH) {
        Serial.println("Performing full screen refresh to clear ghosting...");
        lv_obj_invalidate(lv_screen_active()); // 标记整个屏幕为无效区域
        lv_refr_now(lv_display_get_default()); // 强制立即刷新
        NEED_FORCE_REFRESH = 0;
    }
}

void setup() {
    M5_BEGIN();
    Serial.begin(115200);
    M5.Power.begin();
    M5.Display.setTextPadding(12);
    M5.Display.setTextSize(2);

    sd_card_setup();

    const auto little_fs_result = LittleFS.begin();
    M5.Display.println(little_fs_result ? "LittleFS mounted" : "Failed to mount LittleFS");
    Serial.println(little_fs_result ? "LittleFS mounted" : "Failed to mount LittleFS");

    Serial.printf("PSRAM size: %d\n", esp_spiram_get_size());
    Serial.printf("Heap free size: %d\n", heap_caps_get_free_size(MALLOC_CAP_8BIT));
    Serial.printf("Heap total size: %d\n", heap_caps_get_total_size(MALLOC_CAP_8BIT));
    Serial.printf("Fs total size: %d\n", LittleFS.totalBytes());
    Serial.printf("Fs used size: %d\n", LittleFS.usedBytes());
    M5.Display.printf("PSRAM size: %d\n", esp_spiram_get_size());
    M5.Display.printf("Heap free size: %d\n", heap_caps_get_free_size(MALLOC_CAP_8BIT));
    M5.Display.printf("Heap total size: %d\n", heap_caps_get_total_size(MALLOC_CAP_8BIT));
    M5.Display.printf("Fs total size: %d\n", LittleFS.totalBytes());
    M5.Display.printf("Fs used size: %d\n", LittleFS.usedBytes());

    M5.Display.println("Lvgl initializing!");

    lv_port_disp_init();
    setup_freetype_fonts();

    setup_ui(&guider_ui);
    status_bar_setup();
    home_screen_setup(&guider_ui);
    lock_screen_setup(&guider_ui);

    M5.Display.println("Start drawing!");
}

void loop() {
    vTaskDelay(lv_task_handler() / portTICK_PERIOD_MS);
}
