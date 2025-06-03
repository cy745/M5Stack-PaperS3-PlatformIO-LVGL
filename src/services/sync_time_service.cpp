//
// Created by miku on 25-6-3.
//

#include "sync_time_service.h"
#include <esp_wifi.h>
#include <WiFi.h>
#include <esp_sntp.h>

#include "M5Unified.hpp"

auto ntp_server_1 = "ntp.pool.org";
auto ntp_server_2 = "time.nist.gov";
auto ntp_server_3 = "ntp.aliyun.com";
static tm time_info;

constexpr auto SYNC_TIME_DELAY = 5 * 60 * 1000;
constexpr auto GMT_TIME_OFFSET = 8 * 3600;
constexpr auto SMART_CONFIG_RETRY_COUNT = 60;

bool auto_connect() {
    WiFi.begin();

    for (int i = 0; i < 10; ++i) {
        if (WiFi.status() == WL_CONNECTED) {
            Serial.printf("已连接: %s %d\n", WiFi.SSID().c_str(), i);
            Serial.printf("IP地址: %s\n", WiFi.localIP().toString().c_str());
            break;
        }
        vTaskDelay(5000 / portTICK_PERIOD_MS);
    }
    return WiFi.status() == WL_CONNECTED;
}

void smart_connect() {
    Serial.printf("开始配网\n");
    WiFi.mode(WIFI_MODE_STA);
    WiFi.beginSmartConfig(SC_TYPE_ESPTOUCH_V2, nullptr);
    auto try_count = SMART_CONFIG_RETRY_COUNT;

    while (!WiFi.smartConfigDone() && try_count--) {
        Serial.printf("等待中，剩余重试次数: %d\n", try_count);
        vTaskDelay(5000 / portTICK_PERIOD_MS);
    }

    if (WiFi.smartConfigDone()) {
        WiFi.setAutoConnect(true);
        WiFi.persistent(true);
        Serial.printf("已连接: %s\n", WiFi.SSID().c_str());
        Serial.printf("IP地址: %s\n", WiFi.localIP().toString().c_str());
    } else {
        Serial.printf("配网失败，结束流程\n");
        WiFi.mode(WIFI_MODE_NULL);
    }

    WiFi.stopSmartConfig();
}


[[noreturn]]
void sync_time_loop_task(void *params) {
    if (!auto_connect()) {
        smart_connect();
    }

    if (WiFi.status() != WL_CONNECTED) {
        Serial.printf("联网失败，结束同步时间服务\n");
        vTaskDelete(nullptr);
    }

    configTime(GMT_TIME_OFFSET, 0, ntp_server_1, ntp_server_2, ntp_server_3);
    while (true) {
        Serial.printf("同步时间中....\n");
        sntp_restart();
        if (getLocalTime(&time_info, 1000)) {
            Serial.printf("当前时间：%d年%d月%d日 星期%d %d:%d\n", time_info.tm_year, time_info.tm_mon, time_info.tm_mday,
                          time_info.tm_wday, time_info.tm_hour, time_info.tm_min);
            M5.Rtc.setDateTime(m5::rtc_datetime_t(time_info));
        } else {
            Serial.println("获取时间失败");
        }
        vTaskDelay(SYNC_TIME_DELAY / portTICK_PERIOD_MS);
    }
}

void setup_sync_time_service() {
    xTaskCreatePinnedToCore(sync_time_loop_task, "SYNC_TIME", 8192, nullptr, 1, nullptr, 1);
}
