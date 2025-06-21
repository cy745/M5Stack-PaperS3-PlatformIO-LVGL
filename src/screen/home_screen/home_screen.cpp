//
// Created by miku on 25-6-3.
//

#include <esp_log.h>
#include <FS.h>
#include <SD.h>
#include <vector>

#include "home_screen.h"
#include "epub/Epub.h"
#include "epub/canvas_buffer.h"
#include "esp_jpeg_dec.h"
#include "JPEGDEC.h"
#include "M5GFX.h"

const auto TAG = "HOME_SCREEN";
constexpr size_t STACK_SIZE = 16 * 4096;
StaticTask_t task_tcb;
StackType_t task_stack[STACK_SIZE];
auto bookX = new int[9]{0, 170, 340, 0, 170, 340, 0, 170, 340};
auto bookY = new int[9]{0, 0, 0, 250, 250, 250, 500, 500, 500};
JPEGDEC jpeg;

void load_book_shelf_task(void *params) {
    ESP_LOGI(TAG, "开始加载");

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
    auto str_template = "开始加载书架，共%d本书\n";
    auto loading_tips = (char *) malloc(strlen(str_template) + 1);
    sprintf(loading_tips, str_template, files.size());
    ESP_LOGI(TAG, "开始加载书架，共%d本书\n", files.size());


    for (const auto &file_name: files) {
        std::string path = "/sd/" + file_name;
        epubs.emplace_back(path);
    }

    for (int i = 0; i < std::min((int) epubs.size(), 9); ++i) {
        auto epub = epubs[i];
        auto result = epub.load();
        ESP_LOGI(TAG, "[%s]: 结果: %d", epub.get_path().c_str(), result);
        auto loading_progress = static_cast<int>((i + 1) * (100.0f / static_cast<float>(epubs.size())));


        if (result) {
            ESP_LOGI(TAG, "[%s]: %s", "get_title", epub.get_title().c_str());
            ESP_LOGI(TAG, "[%s]: %s", "get_base_path", epub.get_base_path().c_str());
            ESP_LOGI(TAG, "[%s]: %s", "get_cover_image_item", epub.get_cover_image_item().c_str());

            size_t image_size = 0;
            uint8_t *image_data = epub.get_item_contents(epub.get_cover_image_item(), &image_size);
            ESP_LOGI(TAG, "图片读取: %d, 大小: %d, %p", image_data != nullptr, image_size, image_data);

            jpeg.openRAM(image_data, static_cast<int>(image_size), [](JPEGDRAW *pDraw) -> int {
                auto canvas = static_cast<canvas_buffer *>(pDraw->pUser);
                canvas->setWindow(pDraw->x, pDraw->y, pDraw->iWidth, pDraw->iHeight);
                return canvas->pushPixels(pDraw->pPixels, pDraw->iBpp);
            });

            ESP_LOGI(TAG, "[JEPGDEC]: [%d: %d] JPEGType: %d, bpp: %d", jpeg.getWidth(), jpeg.getHeight(),
                     jpeg.getJPEGType(), jpeg.getBpp());

            auto image_width = jpeg.getWidth() / 8;
            auto image_height = jpeg.getHeight() / 8;

            auto canvas = new canvas_buffer(image_width, image_height);
            jpeg.setUserPointer(canvas);
            auto res = jpeg.decode(0, 0, JPEG_SCALE_EIGHTH);
            free(image_data);

            if (res) {
                printf("lv_image_set_src: %p", image_data);
            }

            // for (int i = 0; i < epub.get_spine_items_count(); ++i) {
            //     ESP_LOGI(TAG, "[SPINE:%d]: %s", i, epub.get_spine_item(i).c_str());
            // }
        }
    }

    ESP_LOGI(TAG, "加载任务结束\n");
    vTaskDelete(nullptr);
}

void load_book_shelf() {
    xTaskCreateStaticPinnedToCore(load_book_shelf_task, "LOAD_BOOKSHELF", STACK_SIZE, nullptr,
                                  1, task_stack, &task_tcb, 1);
    ESP_LOGI(TAG, "Heap free size: %d\n", heap_caps_get_free_size(MALLOC_CAP_8BIT));
}
