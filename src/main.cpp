#include <M5Unified.h>
#include <freertos/FreeRTOS.h>
#include <freertos/queue.h>
#include <freertos/task.h>

#include "PLC/PLCData.h"
#include "S7/s7_task.h"
#include "UI/ui_task.h"
#include "Config.h"

void setup() {
    Serial.begin(115200);
    auto config = M5.config();
    M5.begin(config);

    // Apenas a ultima leitura/status interessa a interface, sem backlog.
    QueueHandle_t dataQueue = xQueueCreate(1, sizeof(PLCData));
    if (dataQueue == nullptr) {
        Serial.println("Falha ao criar QueueHandle_t da comunicacao");
        return;
    }

    const BaseType_t uiStatus = xTaskCreatePinnedToCore(
        uiTask, "UITask", 
        16384, 
        dataQueue, 
        2, 
        nullptr, 
        1);
    if (uiStatus != pdPASS) {
        Serial.println("Falha ao criar UITask");
        vQueueDelete(dataQueue);
        return;
    }

    const BaseType_t s7Status = xTaskCreatePinnedToCore(
        s7Task, 
        "S7Task", 
        8192, 
        dataQueue, 
        1, 
        nullptr, 
        0);
    if (s7Status != pdPASS) {
        Serial.println("Falha ao criar S7Task");
    }
}

void loop() {
    vTaskDelay(pdMS_TO_TICKS(1000));
}
