#include "S7\S7Types\S7DataTypes.h"
#include "DBAdress.h"



//BOOL METHODS
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


//WORD METHODS
S7Word::S7Word(void *Buffer, int Index){
    this->Buf = Buffer;
    this->index = index;
}

void S7Word::S7Execute() const{
   this->value = helper.DWordAt(this->Buf, this->index);
}


//DWORD METHODS
S7DWord::S7DWord(void *Buffer, int index){
    this->Buf = Buffer;
    this->index = index;
}

void S7DWord::S7Execute() const{
    this->value = helper.DWordAt(this->index);
}


/**********************************************
***************FACTORY TYPES*******************
************************************************/
void S7Type::S7FactoryTypes(plcBoolVar var[MAX_NUMBER_BOOL]){
    for(int i = 0; i < MAX_NUMBER_BOOL; i++){
        S7DataBool[i] = new S7Bool(buffer, var[i].byteOffset, var[i].bitOffset);
    }
}

void S7Type::S7FactoryTypes(plcAnalogVar var[MAX_NUMBER_ANALOG]){
    for(int i = 0; i < MAX_NUMBER_ANALOG; i++){
        S7DataAnalog[i] = new S7DWord(buffer, var[i].offset);
    }
}