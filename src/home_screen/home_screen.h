//
// Created by miku on 25-6-3.
//

#pragma once

#ifndef HOME_SCREEN_H
#define HOME_SCREEN_H

#include "generated/gui_guider.h"

void home_screen_setup(lv_ui *ui);

void load_book_shelf_task(void *params);

static void load_book_shelf();

static void update_home_screen(lv_timer_t *t);

#endif
