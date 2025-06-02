/*
* Copyright 2025 NXP
* NXP Proprietary. This software is owned or controlled by NXP and may only be used strictly in
* accordance with the applicable license terms. By expressly accepting such terms or by downloading, installing,
* activating and/or otherwise using the software, you are agreeing that you have read, and that you agree to
* comply with and are bound by, such license terms.  If you do not agree to be bound by the applicable license
* terms, then you may not retain, install, activate or otherwise use the software.
*/

#include "events_init.h"
#include <stdio.h>
#include "lvgl.h"

#if LV_USE_GUIDER_SIMULATOR && LV_USE_FREEMASTER
#include "freemaster_client.h"
#endif

void on_home_screen_loaded();
void on_home_screen_unload();

static void home_screen_event_handler (lv_event_t *e)
{
    lv_event_code_t code = lv_event_get_code(e);
    switch (code) {
    case LV_EVENT_SCREEN_LOADED:
    {
        on_home_screen_loaded();
        break;
    }
    case LV_EVENT_SCREEN_UNLOAD_START:
    {
        on_home_screen_unload();
        break;
    }
    default:
        break;
    }
}

static void home_screen_status_bar_event_handler (lv_event_t *e)
{
    lv_event_code_t code = lv_event_get_code(e);
    switch (code) {
    case LV_EVENT_CLICKED:
    {
        ui_load_scr_animation(&guider_ui, &guider_ui.lock_screen, guider_ui.lock_screen_del, &guider_ui.home_screen_del, setup_scr_lock_screen, LV_SCR_LOAD_ANIM_NONE, 0, 0, true, true);
        break;
    }
    default:
        break;
    }
}

void events_init_home_screen (lv_ui *ui)
{
    lv_obj_add_event_cb(ui->home_screen, home_screen_event_handler, LV_EVENT_ALL, ui);
    lv_obj_add_event_cb(ui->home_screen_status_bar, home_screen_status_bar_event_handler, LV_EVENT_ALL, ui);
}

static void lock_screen_event_handler (lv_event_t *e)
{
    lv_event_code_t code = lv_event_get_code(e);
    switch (code) {
    case LV_EVENT_CLICKED:
    {
        ui_load_scr_animation(&guider_ui, &guider_ui.home_screen, guider_ui.home_screen_del, &guider_ui.lock_screen_del, setup_scr_home_screen, LV_SCR_LOAD_ANIM_NONE, 0, 0, true, true);
        break;
    }
    default:
        break;
    }
}

void events_init_lock_screen (lv_ui *ui)
{
    lv_obj_add_event_cb(ui->lock_screen, lock_screen_event_handler, LV_EVENT_ALL, ui);
}


void events_init(lv_ui *ui)
{

}
