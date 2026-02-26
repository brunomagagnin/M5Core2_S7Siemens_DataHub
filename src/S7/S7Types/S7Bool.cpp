#include "S7/S7Types/S7Bool.h"

S7Bool::S7Bool(void *Buffer, int ByteIndex, byte BitIndex){
    this->Buf = Buffer;
    this->ByteIndex = ByteIndex;
    this->BitIndex = BitIndex;
}

S7Type::S7Type(){

}

void S7Bool::S7Execute() const{
  value = helper.BitAt(this->Buf, this->BitIndex, this->ByteIndex);
}