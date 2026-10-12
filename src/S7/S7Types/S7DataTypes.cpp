#include "S7/S7Types/S7DataTypes.h"

#include <cstring>

namespace {
bool hasBytes(const uint8_t* buffer, size_t length, size_t byteOffset, size_t count) {
    return buffer != nullptr && byteOffset <= length && count <= length - byteOffset;
}
}  // namespace


/* ###################################################################
   ###################################################################
                    MÉTODOS PARA AQUISIÇÃO DE DADOS 
   ###################################################################
   ################################################################### */

   //Padrão dos métodos, valida os argumentos que foram passados e depois executa
  
   namespace S7DataTypes {

bool readBool(const uint8_t* buffer, size_t length, size_t byteOffset, uint8_t bitOffset, bool& value) {
    if (bitOffset > 7 || !hasBytes(buffer, length, byteOffset, 1)) return false;
    value = (buffer[byteOffset] & (uint8_t(1) << bitOffset)) != 0;
    return true;
}

bool readWord(const uint8_t* buffer, size_t length, size_t byteOffset, uint16_t& value) {
    if (!hasBytes(buffer, length, byteOffset, 2)) return false;
    value = (uint16_t(buffer[byteOffset]) << 8) | buffer[byteOffset + 1];
    return true;
}

bool readInt16(const uint8_t* buffer, size_t length, size_t byteOffset, int16_t& value) {
    uint16_t raw = 0;
    if (!readWord(buffer, length, byteOffset, raw)) return false;
    const int32_t signedValue = raw <= 0x7FFF ? int32_t(raw) : int32_t(raw) - 65536;
    value = static_cast<int16_t>(signedValue);
    return true;
}

bool readDWord(const uint8_t* buffer, size_t length, size_t byteOffset, uint32_t& value) {
    if (!hasBytes(buffer, length, byteOffset, 4)) return false;
    value = (uint32_t(buffer[byteOffset]) << 24) |
            (uint32_t(buffer[byteOffset + 1]) << 16) |
            (uint32_t(buffer[byteOffset + 2]) << 8) |
            uint32_t(buffer[byteOffset + 3]);
    return true;
}

bool readReal32(const uint8_t* buffer, size_t length, size_t byteOffset, float& value) {
    static_assert(sizeof(float) == sizeof(uint32_t), "REAL requer float IEEE-754 de 32 bits");
    uint32_t bits = 0;
    if (!readDWord(buffer, length, byteOffset, bits)) return false;
    std::memcpy(&value, &bits, sizeof(value));
    return true;
}

}  // namespace S7DataTypes
