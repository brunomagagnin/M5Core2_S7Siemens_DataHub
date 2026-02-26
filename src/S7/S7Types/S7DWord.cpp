#include "S7/S7Types/S7DWord.h"


S7DWord::S7DWord(void *Buffer, int index){
    this->Buf = Buffer;
    this->index = index;
}

void S7DWord::S7Execute() const{
    this->value = helper.DWordAt(this->index);
}