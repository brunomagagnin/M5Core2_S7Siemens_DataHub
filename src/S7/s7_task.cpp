#include <Arduino.h>
#include <WiFi.h>
#include <freertos/FreeRTOS.h>
#include <freertos/queue.h>
#include <freertos/task.h>
#include <cstring>

#include "Config.h"
#include "PLC/PLCData.h"
#include "PLC/PLCReader.h"
#include "S7/S7Connection/S7Connection.h"
#include "S7/s7_task.h"
#include "Config.h"

namespace {
void sendStatus(QueueHandle_t dataQueue, PLCStatus Status, int Error = 0) {
    PLCData data;
    data.Status = Status;
    data.Error = Error;
    data.Time = millis();
    // Fila de 1 posicao: o ultimo estado sempre substitui o anterior.
    xQueueOverwrite(dataQueue, &data);
}

void sendData(QueueHandle_t dataQueue, PLCData& data) {
    data.Time = millis();
    xQueueOverwrite(dataQueue, &data);
}

void taskDelayMs(uint32_t ms) {
    vTaskDelay(pdMS_TO_TICKS(ms));
}
} // namespace



/* ###################################################################
   ###################################################################
                            S7 TASK 
   ###################################################################
   ################################################################### */
void s7Task(void* pvParameters) {
    auto dataQueue = static_cast<QueueHandle_t>(pvParameters);
    if (dataQueue == nullptr) {
        Serial.println("S7Task: fila nao inicializada");
        vTaskDelete(nullptr);
        return;
    }

    // Credenciais nao configuradas nao disparam tentativas de rede.
    if (ssid[0] == '\0' || std::strcmp(ssid, "CONFIGURE_SSID") == 0 ||
        std::strcmp(ssid, "NONE") == 0 ||
        std::strcmp(pass, "CONFIGURE_PASSWORD") == 0 ||
        std::strcmp(pass, "yourpassword") == 0) {
        Serial.println("S7Task: configure o Wi-Fi em src/Config.cpp");
        sendStatus(dataQueue, PLCStatus::ConfigError, -3);
        vTaskDelete(nullptr);
        return;
    }

    WiFi.mode(WIFI_STA);
    WiFi.begin(ssid, pass);
    uint32_t lastWiFiAttempt = millis();
    S7Connection connection;
    PLCReader reader;
    bool connected = false;
    sendStatus(dataQueue, PLCStatus::WiFiConnecting);

    for (;;) {
        if (WiFi.status() != WL_CONNECTED) {
            if (connected) {
                connection.S7Disconnect();
                connected = false;
            }
            sendStatus(dataQueue, PLCStatus::WiFiConnecting);
            const uint32_t now = millis();
            if (now - lastWiFiAttempt >= AppConfig::WIFI_RETRY_MS) {
                WiFi.disconnect();
                WiFi.begin(ssid, pass);
                lastWiFiAttempt = now;
            }
            taskDelayMs(500);
            continue;
        }

        if (!connected) {
            sendStatus(dataQueue, PLCStatus::PLCConnecting);
            if (!connection.S7Connect()) {
                Serial.println("S7Task: falha ao conectar no CLP");
                connection.S7Disconnect();
                sendStatus(dataQueue, PLCStatus::PLCError);
                taskDelayMs(AppConfig::PLC_RETRY_MS);
                continue;
            }
            connected = true;
        }

        PLCData data;
        int Error = 0;
        if (!reader.Execute(data, Error)) {
            Serial.printf("S7Task: falha na leitura S7: %d\n", Error);
            connection.S7Disconnect();
            connected = false;
            if (Error == -2) {
                sendStatus(dataQueue, PLCStatus::ConfigError, Error);
                vTaskDelete(nullptr); // Mapa invalido requer correcao, nao retry.
                return;
            }
            sendStatus(dataQueue, PLCStatus::ReadError, Error);
            taskDelayMs(AppConfig::PLC_RETRY_MS);
            continue;
        }

        sendData(dataQueue, data);
        taskDelayMs(AppConfig::PLC_POLL_MS);
    }
}
