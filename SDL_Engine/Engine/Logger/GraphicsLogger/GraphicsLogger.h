#pragma once

#ifndef GraphicsLogger_H
#define GraphicsLogger_H

#include "../Logger.h"

class GraphicsLogger : public Logger {
    explicit GraphicsLogger(const std::string& newOutputFile = "graphics.log");
    GraphicsLogger& operator=(const GraphicsLogger&) = delete;
    GraphicsLogger(const GraphicsLogger&) = delete;
    ~GraphicsLogger() override = default;
};

#endif

