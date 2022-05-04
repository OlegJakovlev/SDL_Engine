#include "SceneLogger.h"

SceneLogger::SceneLogger(const std::string& newOutputFile) : Logger(newOutputFile) {
}

SceneLogger& SceneLogger::Instance() {
    SceneLogger* instance = new SceneLogger();
    return *instance;
}

void SceneLogger::LogMessage(const std::string& msg) {
    Write("[SCENE][MESSAGE] " + msg);
}

void SceneLogger::LogWarning(const std::string& msg) {
    Write("[SCENE][WARNING] " + msg);
}

void SceneLogger::LogError(const std::string& msg) {
    Write("[SCENE][*ERROR*] " + msg);
}