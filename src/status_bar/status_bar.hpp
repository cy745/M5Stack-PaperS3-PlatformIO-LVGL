#pragma once

#ifndef STATUS_BAR_UI_H
#define STATUS_BAR_UI_H

#include "M5Unified.h"
#include "generated/gui_guider.h"

static lv_ui *m_ui = nullptr;
static lv_timer_t *timer;
const auto timeStr = new char[10];
const auto powerStr = new char[10];

void update_cb(lv_timer_t *t) {
    const auto time = M5.Rtc.getTime();
    const auto power = M5.Power.getBatteryLevel();
    const auto isCharging = M5.Power.isCharging();
    sprintf(timeStr, "%02d:%02d", time.hours, time.minutes);
    sprintf(powerStr, "%d%%", power);

    if (m_ui == nullptr) return;

    if (m_ui->home_screen_time != nullptr) {
        auto oldTimeStr = lv_label_get_text(m_ui->home_screen_time);
        if (lv_strcmp(oldTimeStr, timeStr)) {
            lv_label_set_text(m_ui->home_screen_time, timeStr);
        }
    }

    if (m_ui->home_screen_power_percent != nullptr) {
        auto oldPowerStr = lv_label_get_text(m_ui->home_screen_power_percent);
        if (lv_strcmp(oldPowerStr, powerStr)) {
            lv_label_set_text(m_ui->home_screen_power_percent, powerStr);
        }
    }
}

extern "C" {
void on_home_screen_loaded() {
    if (timer != nullptr) {
        lv_timer_delete(timer);
        timer = nullptr;
    }
    timer = lv_timer_create(update_cb, 5000, nullptr);
}

void on_home_screen_unload() {
    if (timer != nullptr) {
        lv_timer_delete(timer);
        timer = nullptr;
    }
}
}

inline void status_bar_setup(lv_ui *ui) {
    m_ui = ui;

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
}

#endif
