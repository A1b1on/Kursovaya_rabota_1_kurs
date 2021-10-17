#include "train.h"
#include "nullptrexception.h"
#include <QFile>
#include <QTextStream>
#include <QDebug>
std::vector<QString> Train::citys;
//Const|Dest-ructors
Train::Train() {
    try {
        this->p = new peron;
        this->pointA = new QString;
        this->pointB = new QString;
        if(this->p == nullptr || this->pointA == nullptr || this->pointB == nullptr )
            throw new  NullPtrException("Train object wasnt initialize");
        this->SetPointA(Train::GetRandomCity());
        this->SetPointB(Train::GetRandomCity());
        this->SetPeron(rand()%9+1);
    }  catch (MyException *a) {
        a->Output();
    }
}
Train::Train(Date& dt, Time& tm, QString a, QString b, peron p) : Train::Train(){
        this->SetPointA(a);
        this->SetPointB(b);
        this->SetPeron(p);
        this->SetDate(dt);
        this->SetTime(tm);
}
Train::Train(Date& dt, Time& tm) : Train::Train(dt, tm, Train::GetRandomCity(), Train::GetRandomCity(), rand()%9+1) { }
Train::Train(QString a, QString b) : Train::Train(){
        this->SetPointA(a);
        this->SetPointB(b);
}
Train::Train( Train &obj) : Train::Train(*new Date(obj.GetDay(), obj.GetMonth(), obj.GetYear()), *new Time(obj.GetHour(), obj.GetMinute(), obj.GetSecund()),obj.GetPointA(),obj.GetPointB(),obj.GetPeron()) { }
Train::~Train() {
    delete this->pointA;
    delete this->pointB;
    delete this->p;
}
//Getter
QString Train::GetPointA()
{  return *this->pointA;  }
QString Train::GetPointB()
{  return  *this->pointB;  }
Train::peron Train::GetPeron()
{  return *this->p;  }
QString Train::GetInfo() {
    QString temp;
    temp.push_back(this->GetDate());
    temp.push_back(" | ");
    temp.push_back(this->GetTime());
    temp.push_back(" | ");
    temp.push_back(QString::number(this->GetPeron()));
    temp.push_back(" | ");
    temp.push_back(this->GetPointA());
    temp.push_back(" - ");
    temp.push_back(this->GetPointB());
    return temp;
}
//Setter
int Train::SetPointA(QString str) {
    *this->pointA = str;
    return 1;
}
int Train::SetPointB(QString str) {
    *this->pointB = str;
    return 1;
}
int Train::SetPeron(peron p) {
    *this->p = p;
    return 1;
}
int Train::SetDate(Date &obj) {
    this->SetDay(obj.GetDay());
    this->SetMonth(obj.GetMonth());
    this->SetYear(obj.GetYear());
    return 1;
}
int Train::SetTime(Time &obj) {
    this->SetHour(obj.GetHour());
    this->SetMinute(obj.GetMinute());
    this->SetSecund(obj.GetSecund());
    return 1;
}
int Train::SetInfo(QString str) {
    QString dt = str.left(str.indexOf(' '));
    QString tm = str.mid(str.indexOf(' ')+3,str.indexOf(' ')-2);
    QString per = str.mid(str.indexOf(' ')+14,str.indexOf(' ')-9);
    QString pB = str.mid(str.indexOf('-')+2,str.length());
    QString pA  =str.mid(str.indexOf(' ')+18,str.indexOf('-'));
    pA = pA.remove(pA.indexOf(' '),pB.length()+3);
    this->SetDate(dt);
    this->SetTime(tm);
    this->SetPeron(per.toUInt());
    this->SetPointA(pA);
    this->SetPointB(pB);
    return  1;
}
//other
int Train::CityInit(const char *path) {
    QFile file(path);
    if(file.open(QIODevice::ReadOnly)) {
        QTextStream fileInputStream(&file);
        while(!fileInputStream.atEnd()) {
            Train::citys.push_back(fileInputStream.readLine());
        }
        file.close();
        return 1;
    }
    return 0;
}
QString Train::GetRandomCity()
{ return Train::citys[rand()%Train::citys.size()]; }
//compares
bool Train::A_Cmp(Train *a, Train *b)
{ return a->GetPointA() < b->GetPointA(); }
bool Train::B_Cmp(Train *a, Train *b)
{ return a->GetPointB() < b->GetPointB(); }
bool Train::DateCmp(Train *a, Train *b) {
    if( a->GetYear() < b->GetYear() )
        return 1;
    else if( a->GetYear() == b->GetYear() ) {
        if(a->GetMonth() < b->GetMonth() )
            return 1;
        else if(a->GetMonth() == b->GetMonth() )
            if(a->GetDay() < b->GetDay() )
                return 1;
    }
    return 0;
}
bool Train::TimeCmp(Train *a, Train *b) {
    if( a->GetHour() < b->GetHour() )
        return 1;
    else if( a->GetHour() == b->GetHour() ){
        if(a->GetMinute() < b->GetMinute() )
            return 1;
        else if(a->GetMinute() == b->GetMinute() )
            if(a->GetSecund() < b->GetSecund() )
                return 1;
    }
    return 0;
}
bool Train::P_Cmp(Train *a, Train *b)
{ return a->GetPeron() < b->GetPeron();  }
//opers
std::ostream& operator<< (std::ostream& out, Train &obj) {
    out<<obj.GetInfo().toStdString();
    return out;
}
std::istream& operator>> (std::istream& in, Train &obj) {
    std::string str;
    std::getline(in, str, '\n');
    obj.SetInfo(str.c_str());
    return in;
}
