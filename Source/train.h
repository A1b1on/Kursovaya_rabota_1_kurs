#ifndef TRAIN_H
#define TRAIN_H
#include <vector>
#include "date.h"
#include "Class_Time.h"
class Train : public Time, public Date {
public:
    typedef unsigned peron;
    Train(); Train(Date&, Time&, QString a, QString b, peron);
    Train(Date&, Time&);  Train(QString a, QString b);
    Train(Train&);
    ~Train();
    QString GetPointA();  QString GetPointB();
    peron GetPeron();
    QString GetInfo() override;
    int SetPointA(QString);  int SetPointB(QString);
    int SetPeron(peron);
    int SetInfo(QString);
    using Date::SetDate; using Time::SetTime;
    int SetDate(Date&); int SetTime(Time&);
    static int CityInit(const char* path);
    static QString GetRandomCity();
    static bool DateCmp(Train*, Train*);
    static bool TimeCmp(Train*, Train*);
    static bool A_Cmp(Train*, Train*);
    static bool B_Cmp(Train*, Train*);
    static bool P_Cmp(Train*, Train*);
    friend std::ostream& operator<< (std::ostream&, Train&);
    friend std::istream& operator>> (std::istream&, Train&);
protected:
    QString* pointA;
    QString* pointB;
    peron* p;
    static std::vector<QString> citys;
};
#endif // TRAIN_H
