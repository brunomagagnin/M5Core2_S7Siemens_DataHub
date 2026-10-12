#include "S7/S7Connection/S7Connection.h"

S7Client S7Connection::client;

bool S7Connection::S7Connect() {
    return client.ConnectTo(PLC, AppConfig::RACK, AppConfig::SLOT) == 0;
}

void S7Connection::S7Disconnect() {
    client.Disconnect();
}
