#pragma once

#ifndef STATUS_BAR_H
#define STATUS_BAR_H

#include "generated/gui_guider.h"

struct STATUS_BAR_COMPONENT {
    lv_obj_t *time;
    lv_obj_t *power_percent;
};

void status_bar_setup();

void status_bar_update(const STATUS_BAR_COMPONENT *component);

#endif
