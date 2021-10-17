#include "mwindow.h"
#include "Source/train.h"
#include <QApplication>
#include <QMessageBox>
#include <QFontDatabase>
#include <ctime>
#include <cstdlib>
using namespace std;
int main(int argc, char *argv[])
{
    srand(time(0));
    if(!Train::CityInit(":/citys.txt"))
            QMessageBox::warning(NULL,"Citys` name error", "File with citys` name has error");
    if(!QFontDatabase::addApplicationFont(":/fonts/RetroGaming"))
       QMessageBox::warning(NULL,"Font Load ERROR","Font \"PixelTime\" was not load");
    QApplication a(argc, argv);
    MWindow w;
    w.setWindowTitle("Розклад руху поїіздів");
    w.setWindowIcon(QIcon(":/ico/chbx.png"));
    w.setFixedSize(w.width(),w.height());
    w.show();
    return a.exec();
}
