#include "mwindow.h"
#include "ui_mwindow.h"
#include <QFileDialog>
#include <QMessageBox>
#include <fstream>
#include "Source/fileexception.h"
#include "Source/rangeexception.h"
#define START_GENERATOR 15

MWindow::MWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MWindow)
{
    ui->setupUi(this);
    this->layer = new QVBoxLayout(ui->scrollAreaWidgetContents_2);

    nw = new NewElement();
    src = new Search();

    QObject::connect(nw, SIGNAL(sendSignal(Train*)), this, SLOT(recieveData(Train*)));
    QObject::connect(src, SIGNAL(send(Train*)), this, SLOT(recieveSearch(Train*)));

    clt = new Clock();
    clt->setInterval(1000);
    connect(clt,SIGNAL(timeout()), this, SLOT(TimerSlot()));
    connect(clt,SIGNAL(EndInterval()), this, SLOT(TimerIntervalSlot()));
    clt->SetAddInterval(15);
    clt->SetAddType(Clock::AddSec);
    clt->stop();

    this->ui->Date_2->setText(clt->GetDate());
    this->ui->Time_2->setText(clt->GetTime());

    StartGeneration();
}
MWindow::~MWindow() {
    delete nw;
    delete src;
    delete clt;
    delete layer;
    delete ui;
}

void MWindow::NewWidgetForData() {
    this->widgets.push_back(new QWidget());
    this->labels.push_back(new QLabel(this->widgets.back()));
    this->labels.back()->setText(this->data.back()->GetInfo());
    this->SetStyle(this->widgets.back(),this->labels.back());

    this->layer->addWidget(this->widgets.back());
}
void MWindow::on_RandomBnt_clicked() {
    this->AddRandomFunc();
}
void MWindow::SetStyle(QWidget *qwd, QLabel *qlb) {
    //Стиль чеерез КЮСС
    qwd->setFixedHeight(50);
    qwd->setFixedWidth(810);
    qwd->setStyleSheet(
                "border:3px solid black;"
                "border-bottom: 3px solid white;"
                "border-right: 3px solid white;"
                "background-color: rgb(210,210,210);");
    qlb->setGeometry(5,5,qwd->width()-10,qwd->height()-10);
    qlb->setStyleSheet("font: 16pt \"Retro Gaming\";"
                       "border: none;");
}
void MWindow::StartGeneration() {
    for(auto i = 0; i < START_GENERATOR; i++) {
        this->data.push_back(new Train(*new Date(rand()%30+1,rand()%12+1,rand()%500+2021),*new Time(rand()%24+1,rand()%60+1,rand()%60+1)));
        //Добавление виджета
        this->NewWidgetForData();
    }
}
int MWindow::sort(short type) {
    try {
        switch (type) {
        case 1: //Сортировка по дате
            for(unsigned i = 0;i<this->data.length() ;i++)
                for(unsigned i = 0;i<this->data.length()-1 ;i++)
                    if(Train::DateCmp(this->data[i],this->data[i+1]))
                            this->data.swap(i,i+1);
            break;
        case 2://Сортировка по времени
            for(unsigned i = 0;i<this->data.length() ;i++)
                for(unsigned i = 0;i<this->data.length()-1 ;i++)
                    if(Train::TimeCmp(this->data[i],this->data[i+1]))
                            this->data.swap(i,i+1);
            break;
        case 3://Сортировка по Пункту отбытия
            for(unsigned i = 0;i<this->data.length() ;i++)
                for(unsigned i = 0;i<this->data.length()-1 ;i++)
                    if(Train::A_Cmp(this->data[i],this->data[i+1]))
                            this->data.swap(i,i+1);
            break;
        case 4://Сортировка по Пункту прибытия
            for(unsigned i = 0;i<this->data.length() ;i++)
                for(unsigned i = 0;i<this->data.length()-1 ;i++)
                    if(Train::B_Cmp(this->data[i],this->data[i+1]))
                            this->data.swap(i,i+1);
            break;
        case 5://Сортировка по перону
            for(unsigned i = 0;i<this->data.length() ;i++)
                for(unsigned i = 0;i<this->data.length()-1 ;i++)
                    if(Train::P_Cmp(this->data[i],this->data[i+1]))
                            this->data.swap(i,i+1);
            break;
        default:
            qDebug()<<"Inccorect sort";
            break;
        }
    } catch (MyException *a) {
        a->Output();
    }
        for( size_t i = 0;i<this->data.length() ;i++)
            this->labels[i]->setText(this->data[i]->GetInfo());
        return 1;
}

void MWindow::AddRandomFunc()
{
    //Создание нового елемента
    this->data.push_back(new Train(*new Date(rand()%30+1,rand()%12+1,rand()%500+2021),*new Time(rand()%24+1,rand()%60+1,rand()%60+1)));
    //Добавление виджета
    this->NewWidgetForData();
}

void MWindow::Print(Date *obj)
{
    QMessageBox::information(NULL,"POLIMMORFIZM",obj->GetInfo());
}

void MWindow::on_AddNew_clicked() {
    nw->setWindowTitle("Новий елемент");
    nw->show();
    nw->exec();
}
void MWindow::recieveData(Train* trn) {
    this->data.push_back(trn);
    this->NewWidgetForData();
}
void MWindow::recieveSearch(Train* obj) {
   MyContainer<Train*> result;
   for(unsigned i = 0;i<this->data.length();++i)
   {
       if(this->data[i]->GetPointA() == obj->GetPointA() && this->data[i]->GetPointB() == obj->GetPointB())
           result.push_back(this->data[i]);
   }
   if(result.length() == 0)
   {
       QMessageBox::warning(NULL,"Помилка","Не знайдено жодного варіанту");
       return;
   }
   QString str;
   for(unsigned i = 0;i<result.length();++i)
       str.push_back(result[i]->GetInfo()+"\n");
   QMessageBox::information(NULL,"Результати пошуку", str);
}
void MWindow::TimerSlot() {
    this->clt->TimerLoop(*this->ui->Date_2, *this->ui->Time_2);
}

void MWindow::TimerIntervalSlot()
{
     this->AddRandomFunc();
}
void MWindow::on_DelLast_clicked() {
    this->labels.pop_back();
    this->widgets.pop_back();
    this->data.pop_back();
}
void MWindow::on_SpeedSpin_valueChanged(double arg1) {
    clt->setInterval(1000/arg1);
}
void MWindow::on_Pause_clicked() {
    this->clt->stop();
    this->ui->Pause->setStyleSheet("QPushButton:release{"
                                   "border : 4px solid white;"
                                   "border-bottom: 4px solid black;"
                                   "border-right: 4px solid black;"
                               "}"
                               "QPushButton{ "
                                   "border : 4px solid black;"
                                   "border-bottom: 4px solid white;"
                                   "border-right: 4px solid white;"
                              " }"
                                  " QPushButton:pressed{ "
                                   "border : 4px solid black;"
                                   "border-bottom: 4px solid white;"
                                   "border-right: 4px solid white;"
                               "}");
    this->ui->Play->setStyleSheet("QPushButton{"
                                  "border : 4px solid white;"
                                  "border-bottom: 4px solid black;"
                                  "border-right: 4px solid black;"
                             " }"
                              "QPushButton:pressed{"
                                  "border : 4px solid black;"
                                  "border-bottom: 4px solid white;"
                                  "border-right: 4px solid white;"
                              "}");
}
void MWindow::on_Play_clicked() {
    this->clt->start();
    ui->Play->setStyleSheet("QPushButton:release{"
                                  "border : 4px solid white;"
                                  "border-bottom: 4px solid black;"
                                  "border-right: 4px solid black;"
                              "}"
                              "QPushButton{"
                                  "border : 4px solid black;"
                                  "border-bottom: 4px solid white;"
                                  "border-right: 4px solid white;}"
                              "QPushButton:pressed{"
                                 "border : 4px solid black;"
                                  "border-bottom: 4px solid white;"
                                  "border-right: 4px solid white;"
                             "}");
    this->ui->Pause->setStyleSheet("QPushButton{"
                                   "border : 4px solid white;"
                                   "border-bottom: 4px solid black;"
                                   "border-right: 4px solid black;"
                               "}"
                               "QPushButton:pressed{ "
                                   "border : 4px solid black;"
                                   "border-bottom: 4px solid white;"
                                   "border-right: 4px solid white;"
                               "}");
}
void MWindow::on_SortBy_clicked() {
    switch (this->ui->comboBox->currentIndex()) {
        case 0: sort( 1); break;
        case 1: sort(2); break;
        case 2: sort( 3); break;
        case 3: sort(4); break;
        case 4: sort( 5); break;
        default:
            qDebug()<<"WTF ARE YOU DOING???";
            break;
        }
}
void MWindow::on_Search_clicked() {
    src->setWindowTitle("Пошук");
    src->show();
    src->exec();
}
void MWindow::on_action_triggered() {//Записать в файл
    QString path = QFileDialog::getSaveFileName(this, tr("Save File"),
                                               "/",
                                               tr("TEXT (*.txt)"));
    try {
        std::ofstream fout(path.toStdString().c_str() );
        if(!fout.is_open())
            throw new FileException(path.toStdString().c_str());
        MyIterator iter = data.begin();
        for(unsigned i =0 ; i< this->data.length()-1;i++)
        {
            fout<<**iter<<"\n";
            ++iter;
        }
        fout<<**iter;
        fout.close();
    }  catch (MyException* a) {
        a->Output();
    }
}
void MWindow::on_action_2_triggered() {//Считать с файла
    QString path = QFileDialog::getOpenFileName(this, tr("Load File"),
                                               "/",
                                               tr("TEXT (*.txt)"));
    try {
        std::ifstream fin(path.toStdString().c_str());
        if(!fin.is_open())
            throw new FileException(path.toStdString().c_str());

        Train* temp = new Train();
        while(!fin.eof()){
            fin>>*temp;
            this->data.push_back(temp);
            this->NewWidgetForData();
            temp = new Train;
        }
        fin.close();
    }  catch (MyException* a) {
        a->Output();
    }
}

void MWindow::on_action_3_triggered()
{
   this->Print(this->data.back());
}
