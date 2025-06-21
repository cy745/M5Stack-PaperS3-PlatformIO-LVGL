#include "main.hpp"

#include "M5Unified.h"
#include "LittleFS.h"
#include "sd_card/sd_card.hpp"
#include "font_render/OpenFontRender.h"

static OpenFontRender render;

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

    render.setSerial(Serial);
    render.showFreeTypeVersion(); // print FreeType version
    render.showCredit(); // print FTL credit

    if (render.loadFont("/sd/HarmonyOS_SansSC_Regular.ttf")) {
        Serial.println("Render initialize error");
        return;
    }

    M5.Display.fillScreen(TFT_WHITE);

    render.setDrawer(M5.Display);
    render.setCursor(10, 10);

    render.printf("St\n");
    unsigned long t_start = millis();

    render.setFontColor(TFT_WHITE);
    render.printf("Hello World\n");
    render.seekCursor(0, 10);

    render.setFontSize(30);
    render.setFontColor(TFT_GREEN);
    render.printf("完全なUnicodeサポート\n");
    render.seekCursor(0, 10);

    render.setFontSize(40);
    render.setFontColor(TFT_ORANGE);
    render.printf("こんにちは世界\n");

    unsigned long t_end = millis();
    Serial.printf("Time: %ld ms\n", t_end - t_start);
}

void loop() {
    vTaskDelay(10 / portTICK_PERIOD_MS);
}
