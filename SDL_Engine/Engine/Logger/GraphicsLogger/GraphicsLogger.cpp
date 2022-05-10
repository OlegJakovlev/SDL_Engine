#include "GraphicsLogger.h"

GraphicsLogger::GraphicsLogger(const std::string& newOutputFile) : Logger(newOutputFile) {
}

GraphicsLogger& GraphicsLogger::Instance() {
    static GraphicsLogger* instance = new GraphicsLogger();
    return *instance;
}

void GraphicsLogger::LogMessage(const std::string& msg) {
    Write("[GRAPHICS][MESSAGE] " + msg);
}

void GraphicsLogger::LogWarning(const std::string& msg) {
    Write("[GRAPHICS][WARNING] " + msg);
}

void GraphicsLogger::LogError(const std::string& msg) {
    Write("[GRAPHICS][*ERROR*] " + msg);
}