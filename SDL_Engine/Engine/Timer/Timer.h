#pragma once

#ifndef Timer_H
#define Timer_H

#include <chrono>

class Timer {
public:
    Timer() = default;
    Timer& operator=(const Timer&) = default;
    Timer(const Timer&) = default;
    ~Timer() = default;

    float GetCurrentTime() const;
    void Reset();

private:
    float currentTime;
};

#endif
