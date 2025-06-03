//
// Created by miku on 25-6-3.
//

#pragma once

#ifndef LOCK_SCREEN_H
#define LOCK_SCREEN_H

#include "generated/gui_guider.h"

void lock_screen_setup(lv_ui *ui);

static void update_lock_screen(lv_timer_t *t);

#endif
