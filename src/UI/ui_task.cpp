#include <M5Unified.h>
#include <lvgl.h>
#include <freertos/FreeRTOS.h>
#include <freertos/queue.h>
#include <freertos/task.h>

#include <cmath>
#include <cstdint>
#include <cstdio>

#include "Config.h"
#include "PLC/PLCData.h"
#include "PLC/TagMap.h"
#include "UI/lvgl_port.h"
#include "UI/ui_task.h"

namespace {
struct UiState {
    lv_obj_t* scr_main = nullptr;
    lv_obj_t* scr_chart = nullptr;
    lv_obj_t* chart = nullptr;
    lv_obj_t* current_value_label = nullptr;
    lv_obj_t* connection_label = nullptr;
    lv_obj_t* chart_status_label = nullptr;
    lv_obj_t* scale_y = nullptr;
    lv_chart_series_t* series_var = nullptr;
    int32_t minYValue = 0;
    int32_t maxYValue = 100;
    uint32_t lastValidData = 0;
    bool dataTimeoutShown = false;
};
UiState ui;

//Status de comunicação
const char* getStatusText(PLCStatus Status) {
    switch (Status) {
        case PLCStatus::Starting: return "Inicializando";
        case PLCStatus::WiFiConnecting: return "Conectando Wi-Fi";
        case PLCStatus::PLCConnecting: return "Conectando CLP";
        case PLCStatus::Connected: return "CLP conectado";
        case PLCStatus::WiFiError: return "Wi-Fi desconectado";
        case PLCStatus::PLCError: return "CLP indisponivel";
        case PLCStatus::ReadError: return "Falha de leitura S7";
        case PLCStatus::ConfigError: return "Verifique configuracao";
    }
    return "Estado desconhecido";
}

/* ###################################################################
   ###################################################################
                               SCREENS 
   ###################################################################
   ################################################################### */

void createMainScreen() {
    ui.scr_main = lv_obj_create(nullptr);
    lv_obj_t* title = lv_label_create(ui.scr_main);
    lv_label_set_text(title, "S7 DataHub");
    lv_obj_set_style_text_font(title, &lv_font_montserrat_28, 0);
    lv_obj_align(title, LV_ALIGN_CENTER, 0, -32);

    lv_obj_t* subtitle = lv_label_create(ui.scr_main);
    lv_label_set_text(subtitle, "Pressione o botao central");
    lv_obj_align(subtitle, LV_ALIGN_CENTER, 0, 5);

    ui.connection_label = lv_label_create(ui.scr_main);
    lv_label_set_text(ui.connection_label, "Inicializando");
    lv_obj_align(ui.connection_label, LV_ALIGN_CENTER, 0, 48);
}

void createChartScreen() {
    ui.scr_chart = lv_obj_create(nullptr);

    lv_obj_t* title = lv_label_create(ui.scr_chart);
    lv_label_set_text(title, "Monitoramento - Sensor 1");
    lv_obj_align(title, LV_ALIGN_TOP_LEFT, 10, 7);

    ui.current_value_label = lv_label_create(ui.scr_chart);
    lv_label_set_text(ui.current_value_label, "Valor: --");
    lv_obj_set_style_text_color(ui.current_value_label,
                                lv_palette_main(LV_PALETTE_BROWN), 0);
    lv_obj_set_style_text_font(ui.current_value_label, &lv_font_montserrat_20, 0);
    lv_obj_align(ui.current_value_label, LV_ALIGN_TOP_RIGHT, -10, 25);

    ui.chart_status_label = lv_label_create(ui.scr_chart);
    lv_label_set_text(ui.chart_status_label, "Inicializando");
    lv_obj_align(ui.chart_status_label, LV_ALIGN_TOP_LEFT, 10, 34);

    ui.scale_y = lv_scale_create(ui.scr_chart);
    lv_obj_set_size(ui.scale_y, 40, 140);
    lv_scale_set_mode(ui.scale_y, LV_SCALE_MODE_VERTICAL_LEFT);
    lv_scale_set_range(ui.scale_y, ui.minYValue, ui.maxYValue);
    lv_scale_set_total_tick_count(ui.scale_y, 11);
    lv_scale_set_major_tick_every(ui.scale_y, 2);
    lv_obj_align(ui.scale_y, LV_ALIGN_LEFT_MID, 5, 10);

    ui.chart = lv_chart_create(ui.scr_chart);
    lv_obj_set_size(ui.chart, 240, 140);
    lv_obj_align_to(ui.chart, ui.scale_y, LV_ALIGN_OUT_RIGHT_TOP, 0, 0);
    lv_chart_set_type(ui.chart, LV_CHART_TYPE_LINE);
    lv_chart_set_point_count(ui.chart, 20);
    lv_chart_set_update_mode(ui.chart, LV_CHART_UPDATE_MODE_SHIFT);
    lv_chart_set_range(ui.chart, LV_CHART_AXIS_PRIMARY_Y,
                       ui.minYValue, ui.maxYValue);
    lv_obj_set_style_bg_opa(ui.chart, LV_OPA_TRANSP, 0);
    ui.series_var = lv_chart_add_series(ui.chart,
                                      lv_palette_main(LV_PALETTE_RED),
                                      LV_CHART_AXIS_PRIMARY_Y);

    lv_obj_t* scale_x = lv_scale_create(ui.scr_chart);
    lv_obj_set_size(scale_x, 240, 30);
    lv_scale_set_mode(scale_x, LV_SCALE_MODE_HORIZONTAL_BOTTOM);
    lv_scale_set_range(scale_x, 0, 19);
    lv_scale_set_total_tick_count(scale_x, 20);
    lv_scale_set_major_tick_every(scale_x, 5);
    lv_obj_align_to(scale_x, ui.chart, LV_ALIGN_OUT_BOTTOM_LEFT, 0, 0);
}

void addChartValue(float value) {
    char text[48];
    std::snprintf(text, sizeof(text), "Valor: %.2f", double(value));
    lv_label_set_text(ui.current_value_label, text);
    if (!std::isfinite(value) || value > 1000000.0f || value < -1000000.0f) return;

    const int32_t point = static_cast<int32_t>(std::lround(value));
    bool changed = false;
    while (point > ui.maxYValue && ui.maxYValue < 1000000) {
        ui.maxYValue += 100;
        changed = true;
    }
    while (point < ui.minYValue && ui.minYValue > -1000000) {
        ui.minYValue -= 100;
        changed = true;
    }
    if (changed) {
        lv_scale_set_range(ui.scale_y, ui.minYValue, ui.maxYValue);
        lv_chart_set_range(ui.chart, LV_CHART_AXIS_PRIMARY_Y,
                           ui.minYValue, ui.maxYValue);
    }
    lv_chart_set_next_value(ui.chart, ui.series_var, point);
}

void updatePLCData(const PLCData& data) {
    const char* status = getStatusText(data.Status);
    lv_label_set_text(ui.connection_label, status);
    lv_label_set_text(ui.chart_status_label, status);
    if (!data.Valid || data.Status != PLCStatus::Connected) {
        ui.lastValidData = 0;
        lv_label_set_text(ui.current_value_label, "Valor: --");
        return;
    }
    ui.lastValidData = millis();
    ui.dataTimeoutShown = false;
    // Em uma futura etapa a selecao de sensores sera configuravel.
    addChartValue(data.listOfAnalogs[0]);
}

void changeScreen() {
    lv_screen_load(lv_screen_active() == ui.scr_main ? ui.scr_chart : ui.scr_main);
}
} // namespace



/* ###################################################################
   ###################################################################
                               UI TASK 
   ###################################################################
   ################################################################### */
void uiTask(void* pvParameters) {
    auto dataQueue = static_cast<QueueHandle_t>(pvParameters);
    lvgl_port_init();
    createMainScreen();
    createChartScreen();
    lv_screen_load(ui.scr_main);

    for (;;) {
        M5.update();
        if (M5.BtnB.wasPressed()) changeScreen();
        if (dataQueue != nullptr) {
            PLCData data;
            while (xQueueReceive(dataQueue, &data, 0) == pdTRUE) {
                updatePLCData(data);
            }
        }
        if (ui.lastValidData != 0 && !ui.dataTimeoutShown &&
            millis() - ui.lastValidData > AppConfig::PLC_STALE_MS) {
            ui.dataTimeoutShown = true;
            lv_label_set_text(ui.connection_label, "Sem dados recentes do CLP");
            lv_label_set_text(ui.chart_status_label, "Sem dados recentes");
            lv_label_set_text(ui.current_value_label, "Valor: --");
        }
        lv_timer_handler();
        vTaskDelay(pdMS_TO_TICKS(AppConfig::UI_PERIOD_MS));
    }
}
