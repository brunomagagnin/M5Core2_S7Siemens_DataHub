#include <M5Unified.h>
#include <lvgl.h>
#include "UI/ui_task.h"
#include "UI/lvgl_port.h"

static lv_obj_t * scr_main;
static lv_obj_t * scr_chart;
static lv_obj_t * chart;
static lv_chart_series_t * series_var;
static lv_obj_t * current_value_label;  //label do valor atual registrado

// Atualiza o gráfico
void ui_add_chart_value(int32_t value) {
    if (chart != NULL && series_var != NULL) {
        lv_chart_set_next_value(chart, series_var, value);
        
        // Label com valor númerico
        if (current_value_label != NULL) {
            lv_label_set_text_fmt(current_value_label, "Valor: %d", (int)value);
        }
    }
}

void uiTask(void *pvParameters) {
    lvgl_port_init();

    // ==========================================
    // TELA 1: INICIAL
    // ==========================================
    scr_main = lv_obj_create(NULL); 
    
    lv_obj_t * title = lv_label_create(scr_main);
    lv_label_set_text(title, "S7 DataHub");
    lv_obj_set_style_text_font(title, &lv_font_montserrat_28, 0); 
    lv_obj_align(title, LV_ALIGN_CENTER, 0, -20);

    lv_obj_t * subtitle = lv_label_create(scr_main);
    lv_label_set_text(subtitle, "Pressione o botao central");
    lv_obj_align(subtitle, LV_ALIGN_CENTER, 0, 20);

    // ==========================================
    // TELA 2: GRÁFICO
    // ==========================================
    scr_chart = lv_obj_create(NULL);
    
    // Título da Tela
    lv_obj_t * chart_title = lv_label_create(scr_chart);
    lv_label_set_text(chart_title, "Monitoramento");
    lv_obj_align(chart_title, LV_ALIGN_TOP_LEFT, 10, 10);

    //Label do valor numérico
    current_value_label = lv_label_create(scr_chart);
    lv_label_set_text(current_value_label, "Valor: --");
    lv_obj_set_style_text_color(current_value_label, lv_palette_main(LV_PALETTE_BROWN), 0);
    lv_obj_set_style_text_font(current_value_label, &lv_font_montserrat_20, 0); // Fonte média
    lv_obj_align(current_value_label, LV_ALIGN_TOP_RIGHT, -10, 10);

    // --- CRIA EIXO Y (Vertical) ---
    lv_obj_t * scale_y = lv_scale_create(scr_chart);
    lv_obj_set_size(scale_y, 40, 140);
    lv_scale_set_mode(scale_y, LV_SCALE_MODE_VERTICAL_LEFT);
    lv_scale_set_range(scale_y, 0, 100);             // Range de 0 a 100
    lv_scale_set_total_tick_count(scale_y, 11);      // 11 pontos
    lv_scale_set_major_tick_every(scale_y, 2);       // Mostra o valor a cada 2 ponto
    lv_obj_align(scale_y, LV_ALIGN_LEFT_MID, 5, 10);

    // --- CRIA GRÁFICO ---
    chart = lv_chart_create(scr_chart);
    lv_obj_set_size(chart, 240, 140);
    // Alinha o gráfico exatamente à direita do Eixo Y
    lv_obj_align_to(chart, scale_y, LV_ALIGN_OUT_RIGHT_TOP, 0, 0); 
    lv_chart_set_type(chart, LV_CHART_TYPE_LINE);
    
    // Configurado gráfico para registrar 20 aquisições
    lv_chart_set_point_count(chart, 20); 
    lv_chart_set_update_mode(chart, LV_CHART_UPDATE_MODE_SHIFT);
    lv_chart_set_range(chart, LV_CHART_AXIS_PRIMARY_Y, 0, 100);
    
    // Remove o fundo padrão do gráfico
    lv_obj_set_style_bg_opa(chart, LV_OPA_TRANSP, 0); 
    
    series_var = lv_chart_add_series(chart, lv_palette_main(LV_PALETTE_RED), LV_CHART_AXIS_PRIMARY_Y);

    // --- CRIANDO O EIXO X (Horizontal) ---
    lv_obj_t * scale_x = lv_scale_create(scr_chart);
    lv_obj_set_size(scale_x, 240, 30);
    lv_scale_set_mode(scale_x, LV_SCALE_MODE_HORIZONTAL_BOTTOM);
    lv_scale_set_range(scale_x, 0, 19);              // 20 aquisições
    lv_scale_set_total_tick_count(scale_x, 20);      // 20 pontos
    lv_scale_set_major_tick_every(scale_x, 5);       // Mostra número a cada 5 pontos
    
    lv_obj_align_to(scale_x, chart, LV_ALIGN_OUT_BOTTOM_LEFT, 0, 0);

    // Carrega a tela principal
    lv_screen_load(scr_main);

    uint32_t last_sim_time = millis();

    while(true) {
        M5.update(); 

      // Simulação de injeção de dados (1 segundo)
        if (millis() - last_sim_time > 500) {
            int32_t valor_aleatorio = random(20, 120); 
            ui_add_chart_value(valor_aleatorio);
            last_sim_time = millis();
            if(valor_aleatorio > 95){
                int32_t range_scale_y = (valor_aleatorio*20)/100;
                range_scale_y = valor_aleatorio + range_scale_y;  
                lv_chart_set_range(chart, LV_CHART_AXIS_PRIMARY_Y, 0, range_scale_y);
                lv_scale_set_range(scale_y, 0, range_scale_y);

            }
        }

        // Botão B alterna as telas
        if (M5.BtnB.wasPressed()) {
            if (lv_screen_active() == scr_main) {
                lv_screen_load(scr_chart);
            } else {
                lv_screen_load(scr_main);
            }
        }

        //lv_scale_set_range(scale_y, 0, 100);
        lv_timer_handler();
        vTaskDelay(pdMS_TO_TICKS(5)); 
    }
}