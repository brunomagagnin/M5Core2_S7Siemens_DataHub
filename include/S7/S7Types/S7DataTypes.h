#pragma once

#include <cstddef>
#include <cstdint>

/*   Referencia para readBool
 * buffer     : Ponteiro para o buffer de dados.
 * length     : Tamanho total do buffer em bytes.
 * byteOffset : Posição do byte dentro do buffer.
 * bitOffset  : Posição do bit dentro do byte (0 a 7). Somente para tipo Bool
 * value      : Referência que recebe o valor booleano lido.
 */

 /*   Referencia para os demais métodos
 * buffer     : Ponteiro para o buffer de dados lidos do CLP.
 * length     : Tamanho total do buffer em bytes.
 * byteOffset : Posição inicial do REAL no buffer (4 bytes).
 * value      : Referência que recebe o valor REAL convertido para float.
 */

namespace S7DataTypes {

bool readBool(const uint8_t* buffer, size_t length, size_t byteOffset, uint8_t bitOffset, bool& value);

bool readWord(const uint8_t* buffer, size_t length, size_t byteOffset, uint16_t& value);

bool readInt16(const uint8_t* buffer, size_t length, size_t byteOffset, int16_t& value);

bool readDWord(const uint8_t* buffer, size_t length, size_t byteOffset, uint32_t& value);

bool readReal32(const uint8_t* buffer, size_t length, size_t byteOffset, float& value);

}  // namespace S7DataTypes


