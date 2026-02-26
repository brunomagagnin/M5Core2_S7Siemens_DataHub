#include <M5Unified.h>
#include <lvgl.h>
#include "UI/lvgl_port.h"

#define SCREEN_WIDTH 320
#define SCREEN_HEIGHT 240

/* Buffer de renderização do LVGL */
#define DRAW_BUF_SIZE (SCREEN_WIDTH * SCREEN_HEIGHT / 10 * (LV_COLOR_DEPTH / 8))
static uint8_t draw_buf[DRAW_BUF_SIZE];

/* Callback de envio de imagem (Flush) - M5Unified*/
void my_disp_flush(lv_display_t *display, const lv_area_t *area, uint8_t * px_map) {
    uint32_t w = (area->x2 - area->x1 + 1);
    uint32_t h = (area->y2 - area->y1 + 1);

    M5.Display.startWrite();
    M5.Display.pushImage(area->x1, area->y1, w, h, (uint16_t *)px_map);
    M5.Display.endWrite();

    lv_display_flush_ready(display);
}

/* Callback de leitura do Touchpad - Nova API da M5Unified */
void my_touch_read(lv_indev_t * indev, lv_indev_data_t * data) {
    // getDetail() retorna o estado do primeiro toque detectado
    auto touch = M5.Touch.getDetail(); 

    if (touch.isPressed()) {
        data->state = LV_INDEV_STATE_PRESSED;
        data->point.x = touch.x;
        data->point.y = touch.y;
    } else {
        data->state = LV_INDEV_STATE_RELEASED;
    }
}

static uint32_t my_tick_get_cb(void) {
    return millis();
}

void lvgl_port_init() {
    lv_init();
    lv_tick_set_cb(my_tick_get_cb);

    lv_display_t * disp = lv_display_create(SCREEN_WIDTH, SCREEN_HEIGHT);
    lv_display_set_flush_cb(disp, my_disp_flush);
    lv_display_set_buffers(disp, draw_buf, NULL, DRAW_BUF_SIZE, LV_DISPLAY_RENDER_MODE_PARTIAL);

    lv_indev_t * indev = lv_indev_create();
    lv_indev_set_type(indev, LV_INDEV_TYPE_POINTER);
    lv_indev_set_read_cb(indev, my_touch_read);
}