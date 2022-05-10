#include "InputLogger.h"

InputLogger::InputLogger(const std::string& newOutputFile) : Logger(newOutputFile) {
}

InputLogger& InputLogger::Instance() {
    static InputLogger* instance = new InputLogger();
    return *instance;
}

void InputLogger::LogMessage(const std::string& msg) {
    Write("[INPUT][MESSAGE] " + msg);
}

void InputLogger::LogWarning(const std::string& msg) {
    Write("[INPUT][WARNING] " + msg);
}

void InputLogger::LogError(const std::string& msg) {
    Write("[INPUT][*ERROR*] " + msg);
}