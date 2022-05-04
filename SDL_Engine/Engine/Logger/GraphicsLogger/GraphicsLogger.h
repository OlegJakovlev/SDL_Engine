#pragma once

#ifndef GraphicsLogger_H
#define GraphicsLogger_H

#include "../Logger.h"

class GraphicsLogger : public Logger {
public:
    static GraphicsLogger& Instance();
    void LogMessage(const std::string& msg) override;
    void LogWarning(const std::string& msg) override;
    void LogError(const std::string& msg) override;

private:
    explicit GraphicsLogger(const std::string& newOutputFile = "graphics.log");
    GraphicsLogger& operator=(const GraphicsLogger&) = delete;
    GraphicsLogger(const GraphicsLogger&) = delete;
    ~GraphicsLogger() override = default;
};

#endif

