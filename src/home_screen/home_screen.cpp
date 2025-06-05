//
// Created by miku on 25-6-3.
//

#include "home_screen.h"
#include <esp_log.h>
#include <FS.h>
#include <SD.h>
#include <vector>

#include "status_bar/status_bar.h"
#include "epub/Epub.h"

static lv_timer_t *timer = nullptr;
static lv_ui *m_ui = nullptr;
const auto TAG = "HOME_SCREEN";

void home_screen_setup(lv_ui *ui) {
    m_ui = ui;
}

extern "C" {
void on_home_screen_loaded() {
    load_book_shelf();

    if (timer != nullptr) {
        lv_timer_delete(timer);
        timer = nullptr;
    }
    lv_async_call([](void *) { update_home_screen(nullptr); }, nullptr);
    timer = lv_timer_create(update_home_screen, 5000, nullptr);
}

void on_home_screen_unload() {
    if (timer != nullptr) {
        lv_timer_delete(timer);
        timer = nullptr;
    }
}
}

static void update_home_screen(lv_timer_t *t) {
    status_bar_update(new STATUS_BAR_COMPONENT{
        .time = m_ui->home_screen_time,
        .power_percent = m_ui->home_screen_power_percent
    });
}

void load_book_shelf_task(void *params) {
    auto files = std::vector<std::string>();

    File root = SD.open("/");
    File file = root.openNextFile();
    while (file) {
        auto name = file.name();
        if (strstr(name, ".epub") != nullptr && strstr(name, "./") == nullptr && name != nullptr && name[0] != '.') {
            files.emplace_back(name);
        }
        file = root.openNextFile();
    }
    file.close();

    auto epubs = std::vector<Epub>();

    ESP_LOGI(TAG, "开始加载书架，共%d本书\n", files.size());
    for (const auto &file_name: files) {
        std::string path = "/sd/" + file_name;
        epubs.emplace_back(path);
    }

    for (auto epub: epubs) {
        auto result = epub.load();
        ESP_LOGI(TAG, "[%s]: 结果: %d", epub.get_path().c_str(), result);

        if (result) {
            ESP_LOGI(TAG, "[%s]: %s", "get_title", epub.get_title().c_str());
            ESP_LOGI(TAG, "[%s]: %s", "get_base_path", epub.get_base_path().c_str());
            ESP_LOGI(TAG, "[%s]: %s", "get_cover_image_item", epub.get_cover_image_item().c_str());

            for (int i = 0; i < epub.get_spine_items_count(); ++i) {
                ESP_LOGI(TAG, "[SPINE:%d]: %s", i, epub.get_spine_item(i).c_str());
            }
        }
    }

    vTaskDelete(nullptr);
}

void load_book_shelf() {
    xTaskCreatePinnedToCore(load_book_shelf_task, "LOAD_BOOKSHELF", 32 * 1024, nullptr, tskIDLE_PRIORITY,
                            nullptr, 1);
}
