#include "TimerComponentModel.h"

void TimerComponentModel::AddTime(const double seconds) {
    timeLeft += seconds;
}

void TimerComponentModel::SubstractTime(const double seconds) {
    timeLeft -= seconds;
}

const double TimerComponentModel::GetTimeLeft() const {
    return timeLeft;
}
