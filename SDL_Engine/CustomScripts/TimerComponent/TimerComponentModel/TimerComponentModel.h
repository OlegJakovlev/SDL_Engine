#pragma once

#ifndef TimerComponentModel_H
#define TimerComponentModel_H

class TimerComponentModel {
public:
    void AddTime(const double seconds);
    void SubstractTime(const double seconds);

    const double GetTimeLeft() const;

private:
    double timeLeft = 0;
};

#endif