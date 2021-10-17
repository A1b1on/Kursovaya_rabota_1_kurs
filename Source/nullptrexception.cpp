#include "nullptrexception.h"
#include <QMessageBox>

void NullPtrException::Output() {
    QMessageBox::warning(NULL,"Null_Pointer Exception", this->message);
}
