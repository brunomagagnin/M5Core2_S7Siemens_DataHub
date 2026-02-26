#include <M5Unified.h>
#include "UI/ui_task.h"

void setup() {
    auto cfg = M5.config();
    M5.begin(cfg);
    
    xTaskCreatePinnedToCore(
        uiTask,        
        "UITask",      
        16384,         
        NULL,          
        1,             
        NULL,          
        1              
    );
}

void loop() {
    // Como M5.update() e o lv_timer_handler() estão rodando na uiTask,
    // o loop do Arduino pode simplesmente dormir e economizar processamento.
    vTaskDelay(pdMS_TO_TICKS(500));
}