#ifndef MYEXCEPTION_H
#define MYEXCEPTION_H

#include <exception>
#include <stdexcept>
#include <QMessageBox>

class MyException
{
public:
    const char* message;
    unsigned errNum;

    MyException(const char* msg) : message(msg) {}
    MyException(unsigned errNum) : errNum(errNum) {}
    MyException(unsigned err, const char* msg) : message(msg), errNum(err) {}
    virtual void Output();
};

#endif // MYEXCEPTION_H
