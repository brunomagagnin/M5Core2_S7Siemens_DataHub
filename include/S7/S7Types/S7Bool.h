#ifndef S7BOOL_H
#define S7BOOL_H
#include "S7/S7Types/S7Type.h"

class S7Bool : public S7Type{

private:
mutable bool value = false;
void *Buf;
int ByteIndex;
byte BitIndex;

public:
void S7Execute() const override;
S7Bool(void *Buffer, int ByteIndex, byte BitIndex);
    
};
#endif