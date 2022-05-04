#pragma once

#ifndef InputLogger_H
#define InputLogger_H

#include "../Logger.h"

class InputLogger : public Logger {
public:
    static InputLogger& Instance();
    void LogMessage(const std::string& msg) override;
    void LogWarning(const std::string& msg) override;
    void LogError(const std::string& msg) override;

private:
    explicit InputLogger(const std::string& newOutputFile = "input.log");
    InputLogger& operator=(const InputLogger&) = delete;
    InputLogger(const InputLogger&) = delete;
    ~InputLogger() override = default;
};

#endif
