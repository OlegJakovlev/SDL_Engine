#pragma once

#ifndef Timer_H
#define Timer_H

#include <chrono>

class Timer {
public:
    Timer();
    Timer& operator=(const Timer&) = default;
    Timer(const Timer&) = default;
    ~Timer() = default;

    double GetCurrentTime() const;
    double GetElapsedTime() const;
    void Stop();
    void Reset();

private:
    std::chrono::time_point<std::chrono::high_resolution_clock> startTime;
    std::chrono::time_point<std::chrono::high_resolution_clock> stopTime;
};

#endif