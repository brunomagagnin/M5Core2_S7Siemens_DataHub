#ifndef S7TYPE_H
#define S7TYPE_H
#include <Arduino.h>
#include "Settimino.h"
#include "S7/S7Connection/S7Read.h"


class S7Type{

private:
virtual void S7Execute() const = 0;

protected:
static S7Helper helper;

public:
S7Type();

};

#endif