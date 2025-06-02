if(CONFIG_ESP_FREETYPE_EXAMPLE_LVGL)
    set(srcs "./example/esp_lv_example_freetype.c")
endif()

set(includes "example" 
             "include"
             "include/freetype"
             "include/freetype/config"
             "include/freetype/internal"
             "include/freetype/internal/services")

if(CONFIG_ESP_FREETYPE_EXAMPLE_LVGL)
    idf_component_register(SRCS ${srcs}
                        INCLUDE_DIRS ${includes}
                        REQUIRES lvgl)
else()
    idf_component_register(INCLUDE_DIRS ${includes})
endif()

if(CONFIG_IDF_TARGET_ESP32 OR CONFIG_IDF_TARGET_ESP32S2 OR CONFIG_IDF_TARGET_ESP32S3)
    target_link_libraries(${COMPONENT_LIB} INTERFACE  esp_freetype)
endif()
