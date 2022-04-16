#pragma once

#ifndef AudioLogger_H
#define AudioLogger_H

#include "../Logger.h"

class AudioLogger : public Logger {
public:
    static AudioLogger& Instance();

private:
    explicit AudioLogger(const std::string& newOutputFile = "audio.log");
    AudioLogger& operator=(const AudioLogger&) = delete;
    AudioLogger(const AudioLogger&) = delete;
    ~AudioLogger() override = default;
};

#endif
