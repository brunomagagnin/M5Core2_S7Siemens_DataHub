#include "S7/S7Types/S7Byte.h"


S7Byte::S7Byte(void *Buffer, int index){
    this->Buf =Buffer;
    this->index = index;
}

void S7Byte::S7Execute() const{
    this->value = helper.ByteAt(this->index);
}