/**
 * @file status_bar_gen.c
 * @description Template source file for LVGL objects
 */

/*********************
 *      INCLUDES
 *********************/
#include "status_bar_gen.h"
#include "ui.h"

/*********************
 *      DEFINES
 *********************/

/**********************
 *      TYPEDEFS
 **********************/

/***********************
 *  STATIC VARIABLES
 **********************/

/***********************
 *  STATIC PROTOTYPES
 **********************/

/**********************
 *   GLOBAL FUNCTIONS
 **********************/

lv_obj_t * status_bar_create(lv_obj_t * parent, const char * time, const char * battery_percent)
{
    LV_TRACE_OBJ_CREATE("begin");

    static lv_style_t style_main;

    static bool style_inited = false;

    if (!style_inited) {
        
        lv_style_init(&style_main);
        lv_style_set_bg_color(&style_main, lv_color_hex(0xF0F0F0));
        lv_style_set_border_width(&style_main, 0);
        lv_style_set_radius(&style_main, 0);
        lv_style_set_width(&style_main, lv_pct(100));
        lv_style_set_height(&style_main, 50);
        lv_style_set_pad_hor(&style_main, 16);
        lv_style_set_layout(&style_main, LV_LAYOUT_FLEX);
        lv_style_set_flex_cross_place(&style_main, LV_FLEX_ALIGN_CENTER);
        lv_style_set_flex_track_place(&style_main, LV_FLEX_ALIGN_CENTER);
        lv_style_set_flex_flow(&style_main, LV_FLEX_FLOW_ROW);
        lv_style_set_text_color(&style_main, lv_color_hex(0x000000));

        style_inited = true;
    }

    lv_obj_t * lv_obj_1 = lv_obj_create(parent);
        lv_obj_add_style(lv_obj_1, &style_main, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_flag(lv_obj_1, LV_OBJ_FLAG_SCROLLABLE, false);

    lv_obj_t * text_1 = text_create(lv_obj_1, time);
    lv_obj_set_flex_grow(text_1, 1);

    lv_obj_t * icon_1 = icon_create(lv_obj_1);
    lv_obj_bind_state_if_eq(icon_1, &subject_wifi_connected, LV_STATE_DISABLED, 0);

    lv_obj_t * icon_2 = icon_create(lv_obj_1);
    lv_obj_bind_state_if_eq(icon_2, &subject_is_charging, LV_STATE_DISABLED, 0);

    lv_obj_t * icon_3 = icon_create(lv_obj_1);
    lv_obj_bind_state_if_eq(icon_3, &subject_is_charging, LV_STATE_DISABLED, 0);

    text_create(lv_obj_1, battery_percent);


    LV_TRACE_OBJ_CREATE("finished");

    return lv_obj_1;
}

/**********************
 *   STATIC FUNCTIONS
 **********************/