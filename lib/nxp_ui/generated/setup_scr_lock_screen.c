/*
* Copyright 2025 NXP
* NXP Proprietary. This software is owned or controlled by NXP and may only be used strictly in
* accordance with the applicable license terms. By expressly accepting such terms or by downloading, installing,
* activating and/or otherwise using the software, you are agreeing that you have read, and that you agree to
* comply with and are bound by, such license terms.  If you do not agree to be bound by the applicable license
* terms, then you may not retain, install, activate or otherwise use the software.
*/

#include "lvgl.h"
#include <stdio.h>
#include "gui_guider.h"
#include "events_init.h"
#include "widgets_init.h"
#include "custom.h"



void setup_scr_lock_screen(lv_ui *ui)
{
    //Write codes lock_screen
    ui->lock_screen = lv_obj_create(NULL);
    lv_obj_set_size(ui->lock_screen, 540, 960);
    lv_obj_set_scrollbar_mode(ui->lock_screen, LV_SCROLLBAR_MODE_OFF);

    //Write style for lock_screen, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_bg_opa(ui->lock_screen, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(ui->lock_screen, lv_color_hex(0xffffff), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_grad_dir(ui->lock_screen, LV_GRAD_DIR_NONE, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes lock_screen_status_bar
    ui->lock_screen_status_bar = lv_obj_create(ui->lock_screen);
    lv_obj_set_pos(ui->lock_screen_status_bar, 0, 0);
    lv_obj_set_size(ui->lock_screen_status_bar, 540, 50);
    lv_obj_set_scrollbar_mode(ui->lock_screen_status_bar, LV_SCROLLBAR_MODE_OFF);

    //Write style for lock_screen_status_bar, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_border_width(ui->lock_screen_status_bar, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->lock_screen_status_bar, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui->lock_screen_status_bar, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(ui->lock_screen_status_bar, lv_color_hex(0xD4d4d4), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_grad_dir(ui->lock_screen_status_bar, LV_GRAD_DIR_NONE, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_top(ui->lock_screen_status_bar, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_bottom(ui->lock_screen_status_bar, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_left(ui->lock_screen_status_bar, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_right(ui->lock_screen_status_bar, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->lock_screen_status_bar, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes lock_screen_power_percent
    ui->lock_screen_power_percent = lv_label_create(ui->lock_screen_status_bar);
    lv_obj_set_pos(ui->lock_screen_power_percent, 470, 17);
    lv_obj_set_size(ui->lock_screen_power_percent, 54, 18);
    lv_label_set_text(ui->lock_screen_power_percent, "100%");
    lv_label_set_long_mode(ui->lock_screen_power_percent, LV_LABEL_LONG_WRAP);

    //Write style for lock_screen_power_percent, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_border_width(ui->lock_screen_power_percent, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->lock_screen_power_percent, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_color(ui->lock_screen_power_percent, lv_color_hex(0x000000), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui->lock_screen_power_percent, &lv_font_HarmonyOS_SansSC_Regular_20, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui->lock_screen_power_percent, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_letter_space(ui->lock_screen_power_percent, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_line_space(ui->lock_screen_power_percent, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_align(ui->lock_screen_power_percent, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui->lock_screen_power_percent, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_top(ui->lock_screen_power_percent, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_right(ui->lock_screen_power_percent, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_bottom(ui->lock_screen_power_percent, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_left(ui->lock_screen_power_percent, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->lock_screen_power_percent, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes lock_screen_wifi_icon
    ui->lock_screen_wifi_icon = lv_image_create(ui->lock_screen_status_bar);
    lv_obj_set_pos(ui->lock_screen_wifi_icon, 400, 13);
    lv_obj_set_size(ui->lock_screen_wifi_icon, 24, 24);
    lv_obj_add_flag(ui->lock_screen_wifi_icon, LV_OBJ_FLAG_CLICKABLE);
    lv_image_set_src(ui->lock_screen_wifi_icon, &_wifi_icon_RGB565A8_24x24);
    lv_image_set_pivot(ui->lock_screen_wifi_icon, 50,50);
    lv_image_set_rotation(ui->lock_screen_wifi_icon, 0);

    //Write style for lock_screen_wifi_icon, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_image_recolor_opa(ui->lock_screen_wifi_icon, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_image_opa(ui->lock_screen_wifi_icon, 255, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes lock_screen_is_charging
    ui->lock_screen_is_charging = lv_image_create(ui->lock_screen_status_bar);
    lv_obj_set_pos(ui->lock_screen_is_charging, 438, 13);
    lv_obj_set_size(ui->lock_screen_is_charging, 24, 24);
    lv_obj_add_flag(ui->lock_screen_is_charging, LV_OBJ_FLAG_CLICKABLE);
    lv_image_set_src(ui->lock_screen_is_charging, &_Is_charging_RGB565A8_24x24);
    lv_image_set_pivot(ui->lock_screen_is_charging, 50,50);
    lv_image_set_rotation(ui->lock_screen_is_charging, 0);

    //Write style for lock_screen_is_charging, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_image_recolor_opa(ui->lock_screen_is_charging, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_image_opa(ui->lock_screen_is_charging, 255, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes lock_screen_lock_time
    ui->lock_screen_lock_time = lv_label_create(ui->lock_screen);
    lv_obj_set_pos(ui->lock_screen_lock_time, 22, 125);
    lv_obj_set_size(ui->lock_screen_lock_time, 375, 137);
    lv_label_set_text(ui->lock_screen_lock_time, "00:00");
    lv_label_set_long_mode(ui->lock_screen_lock_time, LV_LABEL_LONG_WRAP);

    //Write style for lock_screen_lock_time, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_border_width(ui->lock_screen_lock_time, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->lock_screen_lock_time, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_color(ui->lock_screen_lock_time, lv_color_hex(0x000000), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui->lock_screen_lock_time, &lv_font_HarmonyOS_SansSC_Regular_144, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui->lock_screen_lock_time, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_letter_space(ui->lock_screen_lock_time, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_line_space(ui->lock_screen_lock_time, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_align(ui->lock_screen_lock_time, LV_TEXT_ALIGN_LEFT, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui->lock_screen_lock_time, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_top(ui->lock_screen_lock_time, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_right(ui->lock_screen_lock_time, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_bottom(ui->lock_screen_lock_time, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_left(ui->lock_screen_lock_time, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->lock_screen_lock_time, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

    //Write codes lock_screen_lock_date
    ui->lock_screen_lock_date = lv_label_create(ui->lock_screen);
    lv_obj_set_pos(ui->lock_screen_lock_date, 34, 286);
    lv_obj_set_size(ui->lock_screen_lock_date, 294, 32);
    lv_label_set_text(ui->lock_screen_lock_date, "2025年5月20日  星期二");
    lv_label_set_long_mode(ui->lock_screen_lock_date, LV_LABEL_LONG_WRAP);

    //Write style for lock_screen_lock_date, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_border_width(ui->lock_screen_lock_date, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->lock_screen_lock_date, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_color(ui->lock_screen_lock_date, lv_color_hex(0x000000), LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui->lock_screen_lock_date, &lv_font_HarmonyOS_SansSC_Regular_24, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui->lock_screen_lock_date, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_letter_space(ui->lock_screen_lock_date, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_line_space(ui->lock_screen_lock_date, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_text_align(ui->lock_screen_lock_date, LV_TEXT_ALIGN_LEFT, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui->lock_screen_lock_date, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_top(ui->lock_screen_lock_date, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_right(ui->lock_screen_lock_date, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_bottom(ui->lock_screen_lock_date, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_pad_left(ui->lock_screen_lock_date, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->lock_screen_lock_date, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

    //The custom code of lock_screen.


    //Update current screen layout.
    lv_obj_update_layout(ui->lock_screen);

    //Init events for screen.
    events_init_lock_screen(ui);
}
