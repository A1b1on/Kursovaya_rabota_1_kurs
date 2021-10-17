#include "myexception.h"

void MyException::Output()
{
    QMessageBox::warning(NULL, "Exception", "Exception " + QString::number(this->errNum) + "was invoke\n" + QString(this->message));
}
