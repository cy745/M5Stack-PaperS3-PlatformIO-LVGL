/**
 * @file status_bar_gen.h
 */

#ifndef STATUS_BAR_H
#define STATUS_BAR_H

#ifdef __cplusplus
extern "C" {
#endif

/*********************
 *      INCLUDES
 *********************/
#include "lvgl/lvgl.h"

/*********************
 *      DEFINES
 *********************/

/**********************
 *      TYPEDEFS
 **********************/

/**********************
 * GLOBAL PROTOTYPES
 **********************/

lv_obj_t * status_bar_create(lv_obj_t * parent, lv_subject_t * time, lv_subject_t * battery_percent);

/**********************
 *      MACROS
 **********************/

#ifdef __cplusplus
} /*extern "C"*/
#endif

#endif /*STATUS_BAR_H*/