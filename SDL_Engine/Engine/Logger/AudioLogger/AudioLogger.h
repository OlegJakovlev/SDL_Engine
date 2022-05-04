#pragma once

#ifndef AudioLogger_H
#define AudioLogger_H

#include "../Logger.h"

class AudioLogger : public Logger {
public:
    static AudioLogger& Instance();
    void LogMessage(const std::string& msg) override;
    void LogWarning(const std::string& msg) override;
    void LogError(const std::string& msg) override;

private:
    explicit AudioLogger(const std::string& newOutputFile = "audio.log");
    AudioLogger& operator=(const AudioLogger&) = delete;
    AudioLogger(const AudioLogger&) = delete;
    ~AudioLogger() override = default;
};

#endif
