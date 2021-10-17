#ifndef MWINDOW_H
#define MWINDOW_H
#include <QMainWindow>
#include <QPushButton>
#include <QVBoxLayout>
#include <QDebug>
#include <QWidget>
#include <QLabel>

#include "Source/train.h"
#include "Source/clock.h"
#include "Source/mycontainer.h"
#include "newelement.h"
#include "search.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MWindow; }
QT_END_NAMESPACE
//MAIN WINDOW
class MWindow : public QMainWindow {
    Q_OBJECT
    NewElement *nw;//Окошко нового элемента
    Search* src; //Окошко поиска
    Clock* clt;//Часы

    MyContainer<QWidget*> widgets;
    MyContainer<QLabel*> labels;
    MyContainer<Train*> data;

    QVBoxLayout* layer;
public:
    MWindow(QWidget *parent = nullptr);
    ~MWindow();

    void NewWidgetForData();//Создание виджета
    void SetStyle(QWidget*, QLabel*);//Задание стиля для елемента массива
    void StartGeneration();//Генерация первый 15ти елементов массива
    int sort( short type);//Сортировка
    void AddRandomFunc();
    void Print(Date*);
private slots:

    void on_RandomBnt_clicked();//Добавить рандомный елемент
    void on_AddNew_clicked();//Окно нового елемента
    void on_DelLast_clicked();//Удалить последний
    void on_SpeedSpin_valueChanged(double arg1);//Ивент изменения скорости часов
    void on_Pause_clicked();//Пауза часов
    void on_Play_clicked();//Запуск часов
    void on_SortBy_clicked();//Запуск сортировки
    void on_Search_clicked();//Окно поиска
    void on_action_triggered();//Работа с файлом

    void on_action_2_triggered();

    void on_action_3_triggered();

public slots:
    void recieveData(Train*);//Данные для нового елемента
    void recieveSearch(Train*);//Данные для поиска
    void TimerSlot();
    void TimerIntervalSlot();
private:
    Ui::MWindow *ui;
};
#endif // MWINDOW_H
