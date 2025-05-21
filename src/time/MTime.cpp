//
// Created by miku on 2025/5/22.
//

#include "MTime.h"

#include "main.hpp"
#include "M5Unified.h"
#include "LittleFS.h"
#include "ui.h"

[[noreturn]]
void update_current_time(void *params) {
    const auto timeStr = new char[10];
    const auto powerStr = new char[10];

    while (true) {
        const auto time = M5.Rtc.getTime();
        const auto power = M5.Power.getBatteryLevel();
        sprintf(timeStr, "%02d:%02d:%02d", time.hours, time.minutes, time.seconds);
        sprintf(powerStr, "%d%%", power);

        Serial.printf("current_time_update: %s\n", timeStr);
        Serial.printf("current_power_level: %s\n", powerStr);

        lv_subject_copy_string(&subject_curretn_time_value, timeStr);
        lv_subject_copy_string(&subject_battery_percent_value, powerStr);
        vTaskDelay(30 * 1000 / portTICK_PERIOD_MS);
    }
}


void mtime_setup() {
    M5.Rtc.begin();
    M5.Power.begin();

    xTaskCreate(update_current_time, "update_current_time", 4096, nullptr, 1, nullptr);
}
