#ifndef S7TYPE_H
#define S7TYPE_H
#include <Arduino.h>
#include "Settimino.h"
#include "Config.h"
#include "S7/S7Connection/S7Read.h"


class S7Type{
/******PRIVATE*******/
private:
virtual void S7Execute() const = 0;


/******PROTECTED******/
protected:
void *buffer;
static S7Helper helper;


/*******PUBLIC********/
public:
S7Type();
void S7FactoryTypes(plcBoolVar var[MAX_NUMBER_BOOL]);
void S7FactoryTypes(plcAnalogVar var[MAX_NUMBER_ANALOG]);
};

#endif