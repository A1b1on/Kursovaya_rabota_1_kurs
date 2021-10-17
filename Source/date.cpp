#include "date.h"
#include <QDateTime>
#include <QDebug>
#include "nullptrexception.h"
//const/destr-ructors
Date::Date() {
    try {
        this->d = new day;
        this->m = new month;
        this->y = new year;
        if( this->d == nullptr || this->m == nullptr || this->y == nullptr)
            throw new NullPtrException("Date object creation fail");
        QDateTime qdt = QDateTime::currentDateTime();
        this->SetYear(qdt.date().year());
        this->SetMonth(qdt.date().month());
        this->SetDay(qdt.date().day());
    }  catch (MyException* a) {
        a->Output();
    }
}
Date::Date(QString str) : Date::Date() {
    this->SetDate(str);
}
Date::Date(day d, month m, year y) : Date::Date(){
    this->SetDay(d);
    this->SetMonth(m);
    this->SetYear(y);
}
Date::Date(Date &obj) : Date::Date(obj.GetDay(), obj.GetMonth(), obj.GetYear()) { }
Date::~Date() {
    delete this->y;
    delete this->m;
    delete this->d;
}
//Getter
Date::year Date::GetYear()
{    return *this->y;    }
Date::month Date::GetMonth()
{    return *this->m;    }
QString Date::GetMonthStr() {
    QString temp = NULL;
    switch(this->GetMonth()) {
    case 1:  temp = "янв";  break;
    case 2: temp = "фев";  break;
    case 3: temp = "мар";  break;
    case 4: temp = "апр";  break;
    case 5: temp = "май";  break;
    case 6: temp = "июн"; break;
    case 7: temp = "июл"; break;
    case 8: temp = "авг"; break;
    case 9: temp = "сен"; break;
    case 10: temp = "окт"; break;
    case 11: temp = "ноя"; break;
    case 12: temp = "дек"; break;
    default:
        qDebug()<<"Incorrect month data";
        break;
    }
    return temp;
}
Date::day Date::GetDay()
{   return *this->d;   }
QString Date::GetDate() {
    QString temp;
    if(this->GetDay() > 9)
        temp.push_back(QString::number(this->GetDay()));
    else {
        temp.push_back('0'); temp.push_back(QString::number(this->GetDay()));
    }
    temp.push_back('.');
    if(this->GetMonth() > 9)
        temp.push_back(QString::number(this->GetMonth()));
    else {
        temp.push_back('0'); temp.push_back(QString::number(this->GetMonth()));
    }
    temp.push_back('.');
    temp.push_back(QString::number(this->GetYear()));
    return temp;
}
QString Date::GetInfo() {
    return this->GetDate();
}
//Setter
int Date::SetYear(year y) {
    *this->y = y;
    return 1;
}
int Date::SetMonth(month m) {
    if(m > 12 || m < 1)
        return 0;
    *this->m = (m);
    return 1;
}
int Date::SetMonth(QString str) {
    if(str == "янв") { this->SetMonth(1); }
    else if(str =="фев") { this->SetMonth(2); }
    else if(str == "мар") { this->SetMonth(3); }
    else if(str == "апр") { this->SetMonth(4); }
    else if(str == "май") { this->SetMonth(5); }
    else if(str == "июн") { this->SetMonth(6); }
    else if(str == "июл") { this->SetMonth(7); }
    else if(str == "авг") { this->SetMonth(8); }
    else if(str == "сен") { this->SetMonth(9); }
    else if(str == "окт") { this->SetMonth(10); }
    else if(str == "ноя") { this->SetMonth(11); }
    else if(str == "дек") { this->SetMonth(12); }
    else {
        qDebug()<<"Incorrect input , plz enter like \"апр\" ,\"май\"...";
        return 0;
    }
    return 1;
}
int Date::SetDay(day d) {
    if(d > 30 || d < 1)
        return 0;
    *this->d = (d);
    return 1;
}
int Date::SetDate(QString str) {
    this->SetDay(str.left(2).toInt());
    this->SetMonth(str.mid(5,6).toInt());
    this->SetYear(str.right(4).toInt());
    return 1;
}
int Date::SetDate(year y, month m, day d) {
    this->SetMonth(m);
    this->SetDay(d);
    this->SetYear(y);
    return 1;
}
//Add & Remove
void Date::addYear(year y) {
    this->SetYear((y+this->GetYear()));
}
void Date::addMonth(month m) {
    this->addYear(m/12);
    this->SetMonth((m + this->GetMonth())%12);
}
void Date::addDay(day d) {
    this->addMonth(d/12);
    this->SetDay((d+this->GetDay())%30);
}
void Date::remYear(year y) {
    if(y > this->GetYear()) {
        this->SetYear(0);
        return;
    }
    this->addYear(-y);
}
void Date::remMonth(month m) {
    this->remYear(m/12);
    this->addMonth((-m)%12);
}
void Date::remDay(day d) {
    this->remMonth(d/30);
    this->addDay((-d)%30);
}
//operators
std::ostream& operator<< (std::ostream& out, Date &obj) {
    out<<obj.GetDate().toStdString();
    return out;
}
std::istream& operator>> (std::istream& in, Date &obj) {
    std::string str;
    in>>str;
    obj.SetDate(str.c_str());
    return in;
}
Date& Date::operator= (Date &obj) {
    this->SetYear(obj.GetYear());
    this->SetMonth(obj.GetMonth());
    this->SetDay(obj.GetDay());
    return *this;
}
Date& Date::operator+=(Date &obj) {
    this->addYear(obj.GetYear());
    this->addMonth(obj.GetMonth());
    this->addDay(obj.GetDay());
    return *this;
}
Date& Date::operator-=(Date &obj) {
    this->remYear(obj.GetYear());
    this->remMonth(obj.GetMonth());
    this->remDay(obj.GetDay());
    return *this;
}
