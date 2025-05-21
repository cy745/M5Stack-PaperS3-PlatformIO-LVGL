/**
 * @file icon_gen.c
 * @description Template source file for LVGL objects
 */

/*********************
 *      INCLUDES
 *********************/
#include "icon_gen.h"
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

lv_obj_t * icon_create(lv_obj_t * parent)
{
    LV_TRACE_OBJ_CREATE("begin");

    static lv_style_t style_main;
    static lv_style_t style_off;

    static bool style_inited = false;

    if (!style_inited) {
        
        lv_style_init(&style_main);
        lv_style_set_width(&style_main, 24);
        lv_style_set_height(&style_main, 24);
        lv_style_set_image_recolor(&style_main, lv_color_hex(0x000000));
        lv_style_set_image_recolor_opa(&style_main, 255);

        lv_style_init(&style_off);
        lv_style_set_image_opa(&style_off, 128);

        style_inited = true;
    }

    lv_obj_t * lv_image_1 = lv_image_create(parent);
        lv_obj_add_style(lv_image_1, &style_main, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_add_style(lv_image_1, &style_off, LV_PART_MAIN | LV_STATE_DISABLED);
    lv_image_set_src(lv_image_1, wifi_icon);
    lv_image_set_inner_align(lv_image_1, LV_IMAGE_ALIGN_STRETCH);


    LV_TRACE_OBJ_CREATE("finished");

    return lv_image_1;
}

/**********************
 *   STATIC FUNCTIONS
 **********************/