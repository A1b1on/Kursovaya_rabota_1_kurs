#ifndef FILEEXCEPTION_H
#define FILEEXCEPTION_H

#include "myexception.h"
class FileException : public MyException
{
public:
    FileException(const char* path) : MyException(path){}
    void Output();
};

#endif // FILEEXCEPTION_H
