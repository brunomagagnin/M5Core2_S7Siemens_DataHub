#include "S7/S7Connection/S7Connection.h"


bool S7Connection::S7Connect(){
    int result = client.ConnectTo(PLC, RACK, SLOT);
    if(result==0){
        return true;
    }
    return false;
};