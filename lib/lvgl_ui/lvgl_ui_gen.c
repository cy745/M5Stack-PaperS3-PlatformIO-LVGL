/**
 * @file lvgl_ui_gen.c
 */

/*********************
 *      INCLUDES
 *********************/
#include "lvgl_ui_gen.h"

#if LV_USE_XML
#endif

/*********************
 *      DEFINES
 *********************/

/**********************
 *      TYPEDEFS
 **********************/

/**********************
 *  STATIC PROTOTYPES
 **********************/

/**********************
 *  STATIC VARIABLES
 **********************/

/**********************
 *  GLOBAL VARIABLES
 **********************/

/* Global Styles */

/* Fonts */


/* Images */
const void * battery_low;
const void * is_charging;
const void * wifi_icon;

/*Subjects*/
lv_subject_t subject_wifi_connected;
lv_subject_t subject_is_charging;

/**********************
 *      MACROS
 **********************/

/**********************
 *   GLOBAL FUNCTIONS
 **********************/

void lvgl_ui_init_gen(const char * asset_path)
{
    char buf[256];

    /* Global Styles */

    /* Subjects */
    lv_subject_init_int(&subject_wifi_connected, 17);
    lv_subject_init_int(&subject_is_charging, 18);

    /* Fonts */

    /* Images */
    lv_snprintf(buf, 256, "%s%s", asset_path, "images/battery_low.png");
    battery_low = lv_strdup(buf);
    lv_snprintf(buf, 256, "%s%s", asset_path, "images/is_charging.png");
    is_charging = lv_strdup(buf);
    lv_snprintf(buf, 256, "%s%s", asset_path, "images/wifi_icon.png");
    wifi_icon = lv_strdup(buf);

    #if LV_USE_XML


        lv_xml_register_image(NULL, "battery_low", battery_low);
        lv_xml_register_image(NULL, "is_charging", is_charging);
        lv_xml_register_image(NULL, "wifi_icon", wifi_icon);

        lv_xml_register_subject(NULL, "wifi_connected", &subject_wifi_connected);
        lv_xml_register_subject(NULL, "is_charging", &subject_is_charging);

    #endif
}

/* callbacks */

/**********************
 *   STATIC FUNCTIONS
 **********************/
