#ifndef S7FACTORY_H
#define S7FACTORY_H
#include <Arduino.h>

/******************************
 **** ABSTRACT CLASS **********
TO FACTORY S7READ TO READING 
S7 MEMORY 
*******************************/

/******************************
 **** REFERENCE ***************
int       Ref
1   >>>   bool
2   >>>   byte
3   >>>   word
4   >>>   dword
*******************************/

class S7Factory {

private:

public:
S7Factory();
virtual ~S7Factory();
virtual void* S7Create(uint16_t DBNumber, uint16_t Amount, void *pUsrData) const = 0;


};


#endif