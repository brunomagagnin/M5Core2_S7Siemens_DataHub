#include "PLC/PLCReader.h"

#include <cmath>
#include <cstddef>
#include <cstdint>

#include "PLC/TagMap.h"
#include "S7/S7Connection/S7Read.h"
#include "S7/S7Types/S7DataTypes.h"
#include "Config.h"

namespace {
struct DBWindow {
    uint16_t DBNumber = 0;
    uint16_t Start = 0;
    uint16_t Amount = 0;
};

constexpr size_t MAX_DB_COUNT = PlcTags::MAX_NUMBER_BOOL + PlcTags::MAX_NUMBER_ANALOG;

bool addWindow(DBWindow* windows, size_t& count, uint16_t DBNumber,
               uint16_t Start, uint16_t Amount) {
    if (Amount == 0 || uint32_t(Start) + Amount > 65536u) return false;
    const uint32_t end = uint32_t(Start) + Amount;

    for (size_t i = 0; i < count; ++i) {
        if (windows[i].DBNumber != DBNumber) continue;
        const uint32_t first = windows[i].Start < Start ? windows[i].Start : Start;
        const uint32_t previousEnd = uint32_t(windows[i].Start) + windows[i].Amount;
        const uint32_t last = previousEnd > end ? previousEnd : end;
        if (last - first > AppConfig::MAX_DB_BYTES) return false;
        windows[i].Start = static_cast<uint16_t>(first);
        windows[i].Amount = static_cast<uint16_t>(last - first);
        return true;
    }

    if (count >= MAX_DB_COUNT || Amount > AppConfig::MAX_DB_BYTES) return false;
    DBWindow& window = windows[count++];
    window.DBNumber = DBNumber;
    window.Start = Start;
    window.Amount = Amount;
    return true;
}

bool getWindows(DBWindow* windows, size_t& count) {
    count = 0;
    for (size_t i = 0; i < PlcTags::MAX_NUMBER_BOOL; ++i) {
        const auto& tag = PlcTags::listOfBool[i];
        if (tag.bitOffset > 7 ||
            !addWindow(windows, count, tag.DBNumber, tag.byteOffset, 1)) return false;
    }
    for (size_t i = 0; i < PlcTags::MAX_NUMBER_ANALOG; ++i) {
        const auto& tag = PlcTags::listOfAnalogs[i];
        const uint16_t amount = tag.tipo == PlcTags::AnalogType::Real32 ? 4 : 2;
        if (!addWindow(windows, count, tag.DBNumber, tag.byteOffset, amount)) return false;
    }
    return true;
}
} // namespace

bool PLCReader::Execute(PLCData& data, int& Error) {
    DBWindow windows[MAX_DB_COUNT] = {};
    size_t windowCount = 0;
    if (!getWindows(windows, windowCount)) {
        Error = -2;
        return false;
    }

    PLCData nextData; // Nao publica leituras parciais.
    uint8_t buffer[AppConfig::MAX_DB_BYTES] = {};
    for (size_t w = 0; w < windowCount; ++w) {
        const DBWindow& window = windows[w];
        S7Read read(window.DBNumber, window.Start, window.Amount, buffer);
        if (!read.Execute()) {
            Error = read.getValue();
            return false;
        }
        for (size_t i = 0; i < PlcTags::MAX_NUMBER_BOOL; ++i) {
            const auto& tag = PlcTags::listOfBool[i];
            if (tag.DBNumber != window.DBNumber) continue;
            const size_t offset = tag.byteOffset - window.Start;
            if (!S7DataTypes::readBool(buffer, window.Amount, offset,
                                       tag.bitOffset, nextData.listOfBool[i])) {
                Error = -2;
                return false;
            }
        }
        for (size_t i = 0; i < PlcTags::MAX_NUMBER_ANALOG; ++i) {
            const auto& tag = PlcTags::listOfAnalogs[i];
            if (tag.DBNumber != window.DBNumber) continue;
            const size_t offset = tag.byteOffset - window.Start;
            if (tag.tipo == PlcTags::AnalogType::Real32) {
                if (!S7DataTypes::readReal32(buffer, window.Amount, offset,
                                             nextData.listOfAnalogs[i]) ||
                    !std::isfinite(nextData.listOfAnalogs[i])) {
                    Error = -4; // REAL invalido ou leitura fora do buffer.
                    return false;
                }
            } else {
                int16_t value = 0;
                if (!S7DataTypes::readInt16(buffer, window.Amount, offset, value)) {
                    Error = -2;
                    return false;
                }
                nextData.listOfAnalogs[i] = static_cast<float>(value);
            }
        }
    }

    nextData.Valid = true;
    nextData.Status = PLCStatus::Connected;
    data = nextData;
    Error = 0;
    return true;
}
