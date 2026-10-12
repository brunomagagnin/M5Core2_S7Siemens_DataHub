#include "S7/S7Connection/S7Read.h"

S7Read::S7Read(uint16_t DBNumber, uint16_t Start, uint16_t Amount,
               void* pUsrData)
    : DBNumber(DBNumber), Start(Start), Amount(Amount),
      pUsrData(pUsrData) {}

bool S7Read::Execute() {
    if (pUsrData == nullptr || Amount == 0) {
        value = -1;  // Parametros invalidos (erro local).
        return false;
    }
    value = client.ReadArea(S7AreaDB, DBNumber, Start,
                                  Amount, pUsrData);
    return value == 0;
}

int S7Read::getValue() const {
    return value;
}
