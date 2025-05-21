/**
 * @file home_gen.c
 * @description Template source file for LVGL objects
 */

/*********************
 *      INCLUDES
 *********************/
#include "home_gen.h"
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

lv_obj_t * home_create(void)
{
    LV_TRACE_OBJ_CREATE("begin");

    static lv_style_t style_screen;

    static bool style_inited = false;

    if(!style_inited) {
        
        lv_style_init(&style_screen);
        lv_style_set_width(&style_screen, lv_pct(100));
        lv_style_set_height(&style_screen, lv_pct(100));
        lv_style_set_radius(&style_screen, 0);
        lv_style_set_border_width(&style_screen, 0);
        lv_style_set_pad_all(&style_screen, 0);
        lv_style_set_bg_color(&style_screen, lv_color_hex(0xffffff));

        style_inited = true;
    }

    lv_obj_t * lv_obj_1 = lv_obj_create(NULL);
        lv_obj_add_style(lv_obj_1, &style_screen, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_flag(lv_obj_1, LV_OBJ_FLAG_SCROLLABLE, false);

    status_bar_create(lv_obj_1, &subject_curretn_time_value, &subject_battery_percent_value);


    LV_TRACE_OBJ_CREATE("finished");

    return lv_obj_1;
}

/**********************
 *   STATIC FUNCTIONS
 **********************/