#ifndef RANGEEXCEPTION_H
#define RANGEEXCEPTION_H
#include "myexception.h"
class RangeException : public MyException
{
public:
    RangeException(unsigned err): MyException(err)  {}
    void Output();
};

#endif // RANGEEXCEPTION_H
