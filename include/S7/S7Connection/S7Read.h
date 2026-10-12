#pragma once

#include <cstdint>
#include "S7/S7Connection/S7Connection.h"

// Leitura de um trecho de DB. O buffer e de propriedade do chamador e deve
// permanecer valido durante Execute(). A classe nao aciona Wi-Fi por conta propria.
class S7Read : public S7Connection {
public:
    S7Read(uint16_t DBNumber, uint16_t Start, uint16_t Amount,
           void* pUsrData);

    bool Execute();
    int getValue() const;

private:
    uint16_t DBNumber;
    uint16_t Start;
    uint16_t Amount;
    void* pUsrData;
    int value = 0;
};
