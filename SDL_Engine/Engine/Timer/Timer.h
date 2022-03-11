#pragma once

#ifndef Timer_H
#define Timer_H

#include <chrono>

class Timer {
public:
	float deltaTime;
	float const fixedDeltaTime;

private:
	Timer();
	Timer& operator=(const Timer&) = delete;
	Timer(const Timer&) = delete;
};

#endif