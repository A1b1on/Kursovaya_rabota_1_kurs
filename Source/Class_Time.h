#ifndef TIME_H
#define TIME_H
#include <iostream>
#include <QString>
//Abstract TIME  class
class Time {
public:
    typedef unsigned hour, minute, secund;
    Time(); Time(hour, minute, secund); Time(QString); Time(Time&);
    virtual ~Time();
    virtual hour GetHour();
    virtual minute GetMinute();
    virtual secund GetSecund();
    virtual QString GetTime();
    virtual QString GetInfo();
    virtual int SetHour(hour);
    virtual int SetMinute(minute);
    virtual int SetSecund(secund);
    virtual int SetTime(QString);
    virtual int SetTime(hour, minute, secund);
    virtual void addHour(hour);
    virtual void addMinute(minute);
    virtual void addSecund(secund);
    virtual void remHour(hour);
    virtual void remMinute(minute);
    virtual void remSecund(secund);
    virtual Time& operator+= (Time&);
    virtual Time& operator-= (Time&) ;
    virtual Time& operator= (Time&);
    friend std::ostream& operator<<(std::ostream&, Time&);
    friend std::istream& operator>>(std::istream&, Time&);
protected:
    hour* h;
    minute* m;
    secund* s;
};
#endif // TIME_H
