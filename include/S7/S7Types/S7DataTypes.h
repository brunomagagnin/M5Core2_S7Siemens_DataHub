#ifndef S7DATATYPES_H
#define S7DATATYPES_H
#include "S7Type.h"

/**************************************************** 
                  GET BOOL VARIABLE
*****************************************************/
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

/**************************************************** 
            GET WORD(INTEGER) VARIABLE
*****************************************************/
class S7Word : public S7Type
{
private:
    void *Buf;
    int index;
    mutable dword value;

public:
    void S7Execute() const override;
    S7Word(void *Buffer, int Index); 
};

/**************************************************** 
            GET DWORD(REAL) VARIABLE
*****************************************************/
class S7DWord : public S7Type
{
private:
    void *Buf;
    int index;
    mutable dword value;

public:
    void S7Execute() const override;
    S7DWord(void *Buffer, int index);
};

#endif

