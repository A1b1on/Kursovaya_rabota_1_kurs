#include "fileexception.h"
#include <QMessageBox>
void FileException::Output() {
    QMessageBox::warning(NULL,"File open Exception","File "+QString(this->message)+" wasnt open");
}
