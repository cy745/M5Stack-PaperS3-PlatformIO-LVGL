#pragma once

#ifndef STATUS_BAR_UI_H
#define STATUS_BAR_UI_H

#include "M5Unified.h"
#include "ui.h"

[[noreturn]]
inline void update_status_bar(void *params) {
    const auto timeStr = new char[10];
    const auto powerStr = new char[10];
    Serial.println("[update_status_bar] task started.");

    while (true) {
        const auto time = M5.Rtc.getTime();
        const auto power = M5.Power.getBatteryLevel();
        const auto isCharging = M5.Power.isCharging();
        sprintf(timeStr, "%02d:%02d", time.hours, time.minutes);
        sprintf(powerStr, "%d%%", power);

        Serial.printf("current_time_update: %s\n", timeStr);
        Serial.printf("current_power_level: %s\n", powerStr);
        Serial.printf("is_charging: %d\n", isCharging);

        lv_subject_set_int(&subject_is_charging, isCharging);
        lv_subject_copy_string(&subject_curretn_time_value, timeStr);
        lv_subject_copy_string(&subject_battery_percent_value, powerStr);
        vTaskDelay(5 * 1000 / portTICK_PERIOD_MS);
    }
}


inline void status_bar_setup() {
    if (M5.Rtc.begin()) {
        Serial.println("RTC initialized.");
    } else {
        Serial.println("RTC not found.");
    }

    if (M5.Power.begin()) {
        Serial.println("Power initialized.");
    } else {
        Serial.println("Power not found.");
    }

    xTaskCreate(update_status_bar, "update_status_bar", 4096, nullptr, 1, nullptr);
}

#endif
