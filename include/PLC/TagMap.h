#pragma once

#include <cstddef>
#include <cstdint>

namespace PlcTags {

struct plcBoolVar {
    const char* nome;
    uint16_t DBNumber;
    uint16_t byteOffset;
    uint8_t bitOffset;
};

enum class AnalogType : uint8_t { Int16, Real32 };

struct plcAnalogVar {
    const char* nome;
    uint16_t DBNumber;
    uint16_t byteOffset;
    AnalogType tipo;
};

constexpr size_t MAX_NUMBER_BOOL = 8;
constexpr size_t MAX_NUMBER_ANALOG = 5;

extern const plcBoolVar listOfBool[MAX_NUMBER_BOOL];
extern const plcAnalogVar listOfAnalogs[MAX_NUMBER_ANALOG];

}  // namespace PlcTags
