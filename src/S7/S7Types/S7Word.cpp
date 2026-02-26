#include "S7/S7Types/S7Word.h"

S7Word::S7Word(void *Buffer, int Index){
    this->Buf = Buffer;
    this->index = index;
}

void S7Word::S7Execute() const{
   this->value = helper.DWordAt(this->Buf, this->index);
}