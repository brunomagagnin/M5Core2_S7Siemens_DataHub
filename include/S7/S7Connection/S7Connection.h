#ifndef S7CONNECTION_H
#define S7CONNECTION_H
#include "Settimino.h"
#include "Config.h"

class S7Connection {
private:

protected:
static S7Client client;

public:
bool S7Connect();

};


#endif