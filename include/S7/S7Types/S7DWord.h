#ifndef S7DWORD_H
#define S7DWORD_H
#include "S7Type.h"

class S7DWord : S7Type
{

private:
    void *Buf;
    int index;
    mutable dword value;

public:
    void S7Execute() const override;
    S7DWord();
    ~S7DWord();
    S7DWord(void *Buffer, int index);
    
};

#endif