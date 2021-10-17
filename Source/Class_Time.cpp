#include "Class_Time.h"
#include <QDebug>
#include <QDateTime>
#include "nullptrexception.h"
//Con/De-structors
Time::Time() {
    try{
        this->h = new hour;
        this->m = new minute;
        this->s = new secund;
        if(h==nullptr || m==nullptr || s==nullptr)
            throw NullPtrException("Time object creation fail");
        QDateTime qdt = QDateTime::currentDateTime();
        this->SetHour(qdt.time().hour());
        this->SetMinute(qdt.time().minute());
        this->SetSecund(qdt.time().second());
    } catch (MyException* a) {
        a->Output();
    }
}
Time::Time(hour h, minute m, secund s) : Time::Time() {
    this->SetHour(h);
    this->SetMinute(m);
    this->SetSecund(s);
}
Time::Time(QString str) : Time::Time() {
    this->SetTime(str);
}
Time::Time(Time& obj) : Time::Time(obj.GetHour(), obj.GetMinute(), obj.GetSecund()) { }
Time::~Time() {
    delete this->h;
    delete this->m;
    delete this->s;
}
//Getter
Time::hour Time::GetHour()
{  return *this->h;  }
Time::minute Time::GetMinute()
{  return *this->m;  }
Time::secund Time::GetSecund()
{  return *this->s;  }
QString Time::GetTime() {
    QString temp;
    if(this->GetHour() > 9)
        temp.push_back(QString::number(this->GetHour()));
    else{
        temp.push_back('0');temp.push_back(QString::number(this->GetHour()));
    }
    temp.push_back(':');
    if(this->GetMinute() > 9)
        temp.push_back(QString::number(this->GetMinute()));
    else{
        temp.push_back('0');temp.push_back(QString::number(this->GetMinute()));
    }
    temp.push_back(':');
    if(this->GetSecund() > 9)
        temp.push_back(QString::number(this->GetSecund()));
    else{
        temp.push_back('0');temp.push_back(QString::number(this->GetSecund()));
    }
    return temp;
}
QString Time::GetInfo() {
    return this->GetTime();
}
//Setter
int Time::SetHour(hour h) {
    if( h < 0 || h > 23)
        return 0;
    *this->h = h;
    return 1;
}
int Time::SetMinute(minute m){
    if( m < 0 || m >59)
        return 0;
    *this->m = m;
    return 1;
}
int Time::SetSecund(secund s){
    if( s < 0 || s > 59)
        return 0;
    *this->s = s;
    return 1;
}
int Time::SetTime(QString str) {
    this->SetHour(str.left(2).toInt());
    this->SetMinute(str.mid(4,5).toInt());
    this->SetSecund(str.right(2).toInt());
    return 1;
}
int Time::SetTime(hour h, minute m, secund s) {
    this->SetHour(h);
    this->SetMinute(m);
    this->SetSecund(s);
    return 1;
}
//adds & removes
void Time::addHour(hour h)
{    this->SetHour((h+this->GetHour())%24);   }
void Time::addMinute(minute m) {
    this->addHour(m/60);
    this->SetMinute((m + this->GetMinute())%60);
}
void Time::addSecund(secund s) {
    this->addMinute(s/60);
    this->SetSecund((s+this->GetSecund())%60);
}
void Time::remHour(hour h)
{    this->addHour(-(h%24));   }
void Time::remMinute(minute m) {
    this->remHour(m/60);
    this->addMinute(-(m%60));
}
void Time::remSecund(secund s) {
    this->remMinute(s/60);
    this->addSecund(-(s%60));
}
//operators
Time& Time::operator+=(Time &obj) {
    this->addHour(obj.GetHour());
    this->addMinute(obj.GetMinute());
    this->addSecund(obj.GetSecund());
    return *this;
}
Time& Time::operator-=(Time &obj) {
    this->remHour(obj.GetHour());
    this->remMinute(obj.GetMinute());
    this->remSecund(obj.GetSecund());
    return *this;
}
Time& Time::operator=(Time &obj)
{
    this->SetHour(obj.GetHour());
    this->SetMinute(obj.GetMinute());
    this->SetSecund(obj.GetSecund());
    return *this;
}
std::ostream& operator<<(std::ostream& out, Time& obj) {
    out<<obj.GetTime().toStdString();
    return out;
}
std::istream& operator>>(std::istream& in, Time& obj) {
    std::string str;
    in>>str;
    obj.SetTime(str.c_str());
    return in;
}
