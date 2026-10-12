
#pragma once

#include <Arduino.h>

// Endereços de rede
extern IPAddress PLC;
extern IPAddress Gateway;
extern IPAddress Subnet;

// Wi-Fi
extern char ssid[];
extern char pass[];

// Configurações gerais do projeto
namespace AppConfig {

    // Configuração de comunicação Siemens
    constexpr uint16_t RACK = 0;
    constexpr uint16_t SLOT = 2;

    // Períodos das tasks e comunicação
    constexpr uint32_t UI_PERIOD_MS = 5;
    constexpr uint32_t PLC_POLL_MS = 500;

    // Reconexão
    constexpr uint32_t WIFI_RETRY_MS = 10000;
    constexpr uint32_t PLC_RETRY_MS = 3000;

    // Tempo máximo sem leitura válida
    constexpr uint32_t PLC_STALE_MS = 5000;

    // Tamanho máximo de leitura de DB
    constexpr uint16_t MAX_DB_BYTES = 256;

}
