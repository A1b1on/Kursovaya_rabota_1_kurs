#ifndef NEWELEMENT_H
#define NEWELEMENT_H

#include <QDialog>
#include "Source/train.h"
namespace Ui {
class NewElement;
}

class NewElement : public QDialog
{
    Q_OBJECT

public:
    explicit NewElement(QWidget *parent = nullptr);
    ~NewElement();

signals:
    void sendSignal(Train* trn);

private slots:
    void on_pushButton_clicked();
private:
    Ui::NewElement *ui;
};

#endif // NEWELEMENT_H
