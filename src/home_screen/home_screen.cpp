//
// Created by miku on 25-6-3.
//

#include "home_screen.h"
#include "status_bar/status_bar.h"

static lv_timer_t *timer = nullptr;
static lv_ui *m_ui = nullptr;

void home_screen_setup(lv_ui *ui) {
    m_ui = ui;
}

extern "C" {
void on_home_screen_loaded() {
    if (timer != nullptr) {
        lv_timer_delete(timer);
        timer = nullptr;
    }
    lv_async_call([](void *) { update_home_screen(nullptr); }, nullptr);
    timer = lv_timer_create(update_home_screen, 5000, nullptr);
}

void on_home_screen_unload() {
    if (timer != nullptr) {
        lv_timer_delete(timer);
        timer = nullptr;
    }
}
}

static void update_home_screen(lv_timer_t *t) {
    status_bar_update(new STATUS_BAR_COMPONENT{
        .time = m_ui->home_screen_time,
        .power_percent = m_ui->home_screen_power_percent
    });
}
