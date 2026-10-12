#pragma once

#include "PLC/PLCData.h"
#include "Config.h"

class PLCReader {
public:
    bool Execute(PLCData& data, int& Error);
};
