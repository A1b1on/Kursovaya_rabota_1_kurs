#ifndef DATE_H
#define DATE_H
#include <QString>
#include <iostream>
//Abstract DATЕ class
class Date {
public:
    typedef unsigned year, month, day;
    Date(); Date(QString); Date(year, month, day); Date(Date&);
    virtual ~Date();
    virtual int SetYear(year);
    virtual int SetMonth(month);
    virtual int SetMonth(QString);
    virtual int SetDay(day);
    virtual int SetDate(QString);
    virtual int SetDate(year,month,day);
    virtual year GetYear();
    virtual month GetMonth();
    virtual day GetDay();
    virtual QString GetMonthStr();
    virtual QString GetDate();
    virtual QString GetInfo();
    virtual void addYear(year);
    virtual void addMonth(month);
    virtual void addDay(day);
    virtual void remYear(year);
    virtual void remMonth(month);
    virtual void remDay(day);
    virtual Date& operator+= (Date&);
    virtual Date& operator-= (Date&);
    virtual Date& operator= (Date&);
    friend std::ostream& operator<< (std::ostream&, Date&);
    friend std::istream& operator>> (std::istream&, Date&);
protected:
    year* y;
    month* m;
    day* d;
};
#endif // DATE_H
