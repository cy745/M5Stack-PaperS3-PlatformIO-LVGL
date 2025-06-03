#include "status_bar.h"
#include "M5Unified.h"

const auto timeStr = new char[10];
const auto powerStr = new char[10];

void status_bar_update(const STATUS_BAR_COMPONENT *component) {
    // const auto isCharging = M5.Power.isCharging();

    if (component->time != nullptr) {
        const auto time = M5.Rtc.getTime();
        sprintf(timeStr, "%02d:%02d", time.hours, time.minutes);


        auto oldTimeStr = lv_label_get_text(component->time);
        if (oldTimeStr != nullptr) {
            if (lv_strcmp(oldTimeStr, timeStr)) {
                lv_label_set_text(component->time, timeStr);
            }
        }
    }

    if (component->power_percent != nullptr) {
        const auto power = M5.Power.getBatteryLevel();
        sprintf(powerStr, "%d%%", power);

        auto oldPowerStr = lv_label_get_text(component->power_percent);
        if (oldPowerStr != nullptr) {
            if (lv_strcmp(oldPowerStr, powerStr)) {
                lv_label_set_text(component->power_percent, powerStr);
            }
        }
    }

    delete component;
}

void status_bar_setup() {
    Serial.println(M5.Rtc.begin() ? "RTC initialized." : "RTC not found.");
    Serial.println(M5.Power.begin() ? "Power initialized." : "Power not found.");
}
