#ifndef NULLPTREXCEPTION_H
#define NULLPTREXCEPTION_H
#include "myexception.h"
class NullPtrException : public MyException
{
public:
    NullPtrException(const char* msg) : MyException(msg) { }
    void Output();
};

#endif // NULLPTREXCEPTION_H
