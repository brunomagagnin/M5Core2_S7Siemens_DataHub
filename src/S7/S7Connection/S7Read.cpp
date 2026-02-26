#include "S7/S7Connection/S7Read.h"

// int ReadArea(int Area, uint16_t DBNumber, uint16_t Start, uint16_t Amount, void *pUsrData);


S7Read::S7Read(uint16_t DBNumber, uint16_t Amount, void *pUsrData)
{
    this->Area = S7AreaDB;
    this->DBNumber = DBNumber;
    this->Start = 0;
    this->Amount = Amount;
    this->pUsrData = pUsrData;
    this->value = 0;
}

void S7Read::Execute()
{
   this->value = client.ReadArea(this->Area, this->DBNumber, this->Start, this->Amount, this->pUsrData);
}

int S7Read::getValue(){
    return this->value;
}
