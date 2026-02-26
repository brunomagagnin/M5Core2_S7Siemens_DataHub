#include "S7/S7Factory/S7FactoryReaderDB.h"

S7FactoryReaderDB::S7FactoryReaderDB()
{}

void *S7FactoryReaderDB::S7Create(uint16_t DBNumber, uint16_t Amount, void *pUsrData) const 
{
    S7Read *reader = new S7Read(DBNumber, Amount, pUsrData);
    return reader;
}

//DECIDI FAZER UMA FACTORY QUE DEVOLVERA UM S7READ CORRESPONDENTE PARA CADA TIPO DE VARIAVEL.