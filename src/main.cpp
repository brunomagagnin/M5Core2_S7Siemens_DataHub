#include <M5Unified.h>
#include "UI/ui_task.h"
#include "config.h"


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
    vTaskDelay(pdMS_TO_TICKS(500));
}