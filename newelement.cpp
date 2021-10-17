#include "newelement.h"
#include "ui_newelement.h"

NewElement::NewElement(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::NewElement)
{
    ui->setupUi(this);
}

NewElement::~NewElement()
{
    delete ui;
}

void NewElement::on_pushButton_clicked()
{
     emit sendSignal(new Train(*new Date(ui->dateEdit->date().day(),
                                    ui->dateEdit->date().month(),
                                    ui->dateEdit->date().year()),
                                    *new Time(ui->timeEdit->time().hour(),
                                    ui->timeEdit->time().minute(),
                                    ui->timeEdit->time().second()),
                                    ui->lineEditA->text(),
                                    ui->lineEditB->text(),
                                    ui->spinBox->value()));
     this->close();
}
