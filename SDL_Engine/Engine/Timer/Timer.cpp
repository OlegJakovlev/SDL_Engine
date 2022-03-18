#include "Timer.h"

Timer::Timer() {
    Reset();
}

double Timer::GetCurrentTime() const {
    return std::chrono::duration<double>(std::chrono::duration_cast<std::chrono::seconds>(std::chrono::high_resolution_clock::now().time_since_epoch())).count();
}

double Timer::GetElapsedTime() const {
    return std::chrono::duration<double>(std::chrono::duration_cast<std::chrono::seconds>(stopTime - startTime)).count();
}

void Timer::Reset() {
    startTime = std::chrono::high_resolution_clock::now();
}

void Timer::Stop() {
    stopTime = std::chrono::high_resolution_clock::now();
}
