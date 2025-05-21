/**
 * @file lvgl_ui_gen.h
 */

#ifndef LVGL_UI_GEN_H
#define LVGL_UI_GEN_H

#ifndef UI_SUBJECT_STRING_LENGTH
#define UI_SUBJECT_STRING_LENGTH 256
#endif

#ifdef __cplusplus
extern "C" {
#endif

/*********************
 *      INCLUDES
 *********************/

#include "lvgl/lvgl.h"

/*Include all the widget and components of this library*/
#include "components/column/column_gen.h"
#include "components/icon/icon_gen.h"
#include "components/row/row_gen.h"
#include "components/status_bar/status_bar_gen.h"
#include "screens/home/home_gen.h"

/*********************
 *      DEFINES
 *********************/

// TODO: should these definitions be prefixed with the project name?


/**********************
 *      TYPEDEFS
 **********************/

/**********************
 * GLOBAL VARIABLES
 **********************/

/* Global Styles */

/* Fonts */


/* Images */
extern const void * battery_low;
extern const void * is_charging;
extern const void * wifi_icon;

/* Subjects */
extern lv_subject_t subject_wifi_connected;
extern lv_subject_t subject_is_charging;
extern lv_subject_t subject_battery_percent_value;
extern lv_subject_t subject_curretn_time_value;

/**********************
 * GLOBAL PROTOTYPES
 **********************/

/* callbacks */

/**
 * Initialize the component library
 */

void lvgl_ui_init_gen(const char * asset_path);

/**********************
 *      MACROS
 **********************/

#ifdef __cplusplus
} /*extern "C"*/
#endif

#endif /*LVGL_UI_GEN_H*/
