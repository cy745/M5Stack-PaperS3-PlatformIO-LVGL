//
// Created by miku on 25-6-3.
//

#include "lock_screen.h"

#include "M5Unified.hpp"
#include "status_bar/status_bar.h"

static lv_timer_t *timer = nullptr;
static lv_ui *m_ui = nullptr;

void lock_screen_setup(lv_ui *ui) {
    m_ui = ui;
}

extern "C" {
void on_lock_screen_loaded() {
    if (timer != nullptr) {
        lv_timer_delete(timer);
        timer = nullptr;
    }
    lv_async_call([](void *) { update_lock_screen(nullptr); }, nullptr);
    timer = lv_timer_create(update_lock_screen, 5000, nullptr);
}

void on_lock_screen_unload() {
    if (timer != nullptr) {
        lv_timer_delete(timer);
        timer = nullptr;
    }
}
}

static auto dateStr = new char[20];
static auto weekDayMap = new const char *[7]{"一", "二", "三", "四", "五", "六", "日"};

static void update_lock_screen(lv_timer_t *t) {
    status_bar_update(new STATUS_BAR_COMPONENT{
        .time = m_ui->lock_screen_lock_time,
        .power_percent = m_ui->lock_screen_power_percent
    });

    if (m_ui->lock_screen_lock_date != nullptr) {
        auto date = M5.Rtc.getDate();
        sprintf(dateStr, "%d年%d月%d日 星期%s", date.year, date.month, date.date, weekDayMap[date.weekDay]);

        auto oldDateStr = lv_label_get_text(m_ui->lock_screen_lock_date);
        if (oldDateStr != nullptr) {
            if (lv_strcmp(oldDateStr, dateStr)) {
                lv_label_set_text(m_ui->lock_screen_lock_date, dateStr);
            }
        }
    }
}
