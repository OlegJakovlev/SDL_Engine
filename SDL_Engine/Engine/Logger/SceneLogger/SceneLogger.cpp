#include "SceneLogger.h"

SceneLogger::SceneLogger(const std::string& newOutputFile) : Logger(newOutputFile) {
}

SceneLogger& SceneLogger::Instance() {
    SceneLogger* instance = new SceneLogger();
    return *instance;
}