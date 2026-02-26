#ifndef S7WORD_H
#define S7WORD_H
#include "S7/S7Types/S7Type.h"

class S7Word : public S7Type
{
private:
    void *Buf;
    int index;
    mutable dword value;

public:
    void S7Execute() const override;
    S7Word(void *Buffer, int Index);
    S7Word();
    ~S7Word();
    
};

#endif