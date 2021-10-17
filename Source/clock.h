#ifndef CLOCK_H
#define CLOCK_H

#include "date.h"
#include "Class_Time.h"
#include <QObject>
#include <QTimer>
#include <QLabel>

class Clock : public QTimer, public Time, public Date {
public:
    enum AddState {
        AddSec = 1,
        AddMin,
        AddHour,
        AddDay,
        AddMon,
        AddYear
    };
private:
    Q_OBJECT
    AddState addType;
    unsigned addInterval;
    unsigned buffer;
public:
    Clock();
    Clock(Date&, Time&);
    Clock(Date&, Time&,unsigned addInterval);
    Clock(Date&, Time&,unsigned addInterval, AddState);
    Clock(Clock&);
    void TimerLoop(QLabel& date, QLabel& time);
    void SetAddType(AddState);
    void SetAddInterval(unsigned);
    QString GetInfo() override;
signals:
    void EndInterval();
};


#endif // CLOCK_H
