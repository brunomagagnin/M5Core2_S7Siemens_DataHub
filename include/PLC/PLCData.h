#pragma once

#include <cstdint>
#include "PLC/TagMap.h"

enum class PLCStatus : uint8_t {
    Starting,
    WiFiConnecting,
    PLCConnecting,
    Connected,
    WiFiError,
    PLCError,
    ReadError,
    ConfigError
};

struct PLCData {
    PLCStatus Status = PLCStatus::Starting;
    int Error = 0;
    bool Valid = false;
    uint32_t Time = 0;
    bool listOfBool[PlcTags::MAX_NUMBER_BOOL] = {};
    float listOfAnalogs[PlcTags::MAX_NUMBER_ANALOG] = {};
};
