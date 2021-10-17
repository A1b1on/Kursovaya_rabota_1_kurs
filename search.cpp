#include "search.h"
#include "ui_search.h"
#include <QDebug>
#include <QMessageBox>
Search::Search(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Search)
{
    ui->setupUi(this);
}

Search::~Search()
{
    delete ui;
}


void Search::on_pushButton_clicked()
{
    Train* t;
    t = new Train(ui->lineEditA->text(), ui->lineEditB->text());
    emit send(t);
    this->close();
}


