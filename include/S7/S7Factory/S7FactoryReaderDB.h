#ifndef S7FACTORYREADERDB_H
#define S7FACTORYREADERDB_H
#include "S7/S7Factory/S7Factory.h"
#include "S7/S7Connection/S7Read.h"
#include <Arduino.h>

class S7FactoryReaderDB : public S7Factory
{

private:

public:
S7FactoryReaderDB();
~S7FactoryReaderDB();
void *S7Create(uint16_t DBNumber, uint16_t Amount, void *pUsrData) const override;

};


#endif