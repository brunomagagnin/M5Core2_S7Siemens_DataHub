#ifndef S7READ_H
#define S7READ_H
#include "S7/S7Connection/S7Connection.h"

/*
********* AREA TABLE ***********
S7AreaPE  0x81   Process Inputs
S7AreaPA  0x82   Process Outputs
S7AreaMK  0x83   Merkers.
S7AreaDB  0x84   DB
S7AreaCT  0x1C   Counters
S7AreaTM  0x1D   Timers
*/

class S7Read : public S7Connection {

private:
int Area;
uint16_t DBNumber;
uint16_t Start;
uint16_t Amount;
void *pUsrData;
int value;

public:
S7Read();
S7Read(uint16_t DBNumber, uint16_t Amount, void *pUsrData);
void Execute();
int getValue();

}; 

#endif

/*
S7Conection
Static S7Client
S7Connect()

S7Read  >> S7Connection
int Area;
uint16_t DBNumber;
uint16_t Start;
uint16_t Amount;
void *pUsrData;
int value;
void Execute()

*/