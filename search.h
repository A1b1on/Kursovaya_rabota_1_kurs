#ifndef SEARCH_H
#define SEARCH_H

#include <QDialog>
#include "Source/train.h"
#include "Source/mycontainer.h"
namespace Ui {
class Search;
}

class Search : public QDialog
{
    Q_OBJECT
    MyContainer<Train*> t;
public:
    explicit Search(QWidget *parent = nullptr);
    ~Search();

private slots:
    void on_pushButton_clicked();
signals:
     void send(Train*);

private:
    Ui::Search *ui;
};

#endif // SEARCH_H
