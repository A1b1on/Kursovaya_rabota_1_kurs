#include "clock.h"
#include "nullptrexception.h"
#include <QDateTime>
//constructors
Clock::Clock() : QTimer() {
    this->addType = AddSec;
    this->addInterval = 1;
    this->buffer = 0;
}
Clock::Clock(Date &objD, Time &objT) {
    this->addType = AddSec;
    this->buffer = 0;
    this->addInterval = 1;

    this->SetTime(objT.GetHour(),objT.GetMinute(),objT.GetSecund());
    this->SetDate(objD.GetYear(),objD.GetMonth(),objD.GetDay());
}
Clock::Clock(Date &objD, Time &objT, unsigned addInterval) {
    this->addType = AddSec;
    this->addInterval = addInterval;
    this->buffer = 0;

    this->SetTime(objT.GetHour(),objT.GetMinute(),objT.GetSecund());
    this->SetDate(objD.GetYear(),objD.GetMonth(),objD.GetDay());
}
Clock::Clock(Date &objD, Time &objT, unsigned addInterval, AddState adst) {
    this->addType = adst;
    this->addInterval = addInterval;
    this->buffer = 0;

    this->SetTime(objT.GetHour(),objT.GetMinute(),objT.GetSecund());
    this->SetDate(objD.GetYear(),objD.GetMonth(),objD.GetDay());
}
//Setters
QString Clock::GetInfo() {
    return this->GetDate() + this->GetTime();
}
void Clock::SetAddType(AddState adst) {
    this->addType = adst;
}
void Clock::SetAddInterval(unsigned interval) {
    this->addInterval = interval;
}
//Timer
void Clock::TimerLoop(QLabel &date, QLabel &time) {
    date.setText(this->GetDate());
    time.setText(this->GetTime());
    this->buffer++;
    switch (this->addType)
    {
    case 1:
        this->addSecund(1);
        break;
    case 2:
        this->addMinute(1);
        break;
    case 3:
        this->addHour(1);
        break;
    case 4:
        this->addDay(1);
        break;
    case 5:
        this->addMonth(1);
        break;
    case 6:
        this->addYear(1);
        break;
    }
    if(this->buffer == this->addInterval )
    {
        this->buffer = 0;
        emit EndInterval();
    }
}


