#pragma once

#include "Config.h"
#include "Settimino.h"

class S7Connection {
public:
    bool S7Connect();
    void S7Disconnect();

protected:
    static S7Client client;
};