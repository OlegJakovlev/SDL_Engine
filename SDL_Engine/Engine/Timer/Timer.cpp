#include "Timer.h"

float Timer::GetCurrentTime() const {
    //currentTime = std::chrono::system_clock::now();
    return currentTime;
}

void Timer::Reset() {
    currentTime = 0;
}
