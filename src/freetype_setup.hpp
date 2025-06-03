#ifndef FREETYPE_SETUP_H
#define FREETYPE_SETUP_H

#include "lvgl.h"

extern "C" {
lv_font_t lv_font_HarmonyOS_SansSC_Regular_144;
lv_font_t lv_font_HarmonyOS_SansSC_Regular_24;
lv_font_t lv_font_HarmonyOS_SansSC_Regular_20;
}

inline void load_font_into(lv_font_t *font, uint32_t size, lv_freetype_font_style_t style) {
    auto target = lv_freetype_font_create("/sd/HarmonyOS_SansSC_Regular.ttf",
                                          LV_FREETYPE_FONT_RENDER_MODE_BITMAP, size,
                                          style);
    *font = target ? *target : *lv_font_get_default();
}

inline void setup_freetype_fonts() {
    load_font_into(&lv_font_HarmonyOS_SansSC_Regular_144, 144, LV_FREETYPE_FONT_STYLE_BOLD);
    load_font_into(&lv_font_HarmonyOS_SansSC_Regular_24, 24, LV_FREETYPE_FONT_STYLE_NORMAL);
    load_font_into(&lv_font_HarmonyOS_SansSC_Regular_20, 20, LV_FREETYPE_FONT_STYLE_NORMAL);
}

#endif
