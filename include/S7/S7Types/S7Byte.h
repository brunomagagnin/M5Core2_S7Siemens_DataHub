#ifndef S7BYTE_H
#define S7BYTE_H
#include "S7Type.h"

class S7Byte : public S7Type
{

private:
    void *Buf;
    int index;
    mutable byte value;

protected:


public:
    void S7Execute() const override;
    S7Byte();
    ~S7Byte();
    S7Byte(void *Buffer, int index);

};

#endif