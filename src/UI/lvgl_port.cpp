#include <M5Unified.h>
#include <lvgl.h>
#include "UI/lvgl_port.h"

namespace {
    constexpr int kWidth = 320;
    constexpr int kHeight = 240;

    // Quantidade de linhas utilizadas no buffer LVGL
    constexpr int kDrawBufferLines = 8;

    // Tamanho do buffer em bytes
    constexpr size_t kDrawBufferBytes =
        kWidth * kDrawBufferLines * (LV_COLOR_DEPTH / 8);

    uint8_t drawBuffer[kDrawBufferBytes];

void flushDisplay(lv_display_t* display, const lv_area_t* area, uint8_t* pixelMap) {
    const uint32_t width = area->x2 - area->x1 + 1;
    const uint32_t height = area->y2 - area->y1 + 1;

    M5.Display.startWrite();
    M5.Display.pushImage(area->x1, area->y1, width, height,
                         reinterpret_cast<uint16_t*>(pixelMap));
    M5.Display.endWrite();
    lv_display_flush_ready(display);
}

void readTouch(lv_indev_t*, lv_indev_data_t* data) {
    const auto touch = M5.Touch.getDetail();
    if (touch.isPressed()) {
        data->state = LV_INDEV_STATE_PRESSED;
        data->point.x = touch.x;
        data->point.y = touch.y;
    } else {
        data->state = LV_INDEV_STATE_RELEASED;
    }
}

uint32_t lvTick() { return millis(); }
}  // namespace

void lvgl_port_init() {
    lv_init();
    lv_tick_set_cb(lvTick);

    lv_display_t* display = lv_display_create(kWidth, kHeight);
    lv_display_set_flush_cb(display, flushDisplay);
    lv_display_set_buffers(display, drawBuffer, nullptr, sizeof(drawBuffer),
                           LV_DISPLAY_RENDER_MODE_PARTIAL);

    lv_indev_t* touch = lv_indev_create();
    lv_indev_set_type(touch, LV_INDEV_TYPE_POINTER);
    lv_indev_set_display(touch, display);
    lv_indev_set_read_cb(touch, readTouch);
}
