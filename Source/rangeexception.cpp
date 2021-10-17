#include "rangeexception.h"
#include <QMessageBox>
void RangeException::Output() {
    QMessageBox::warning(NULL,"Out of range Exception","Out of range by index: " + QString::number(this->errNum));
}
