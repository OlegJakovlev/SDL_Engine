#include "GraphicsLogger.h"

GraphicsLogger::GraphicsLogger(const std::string& newOutputFile) : Logger(newOutputFile) {
}

GraphicsLogger& GraphicsLogger::Instance() {
    GraphicsLogger* instance = new GraphicsLogger();
    return *instance;
}