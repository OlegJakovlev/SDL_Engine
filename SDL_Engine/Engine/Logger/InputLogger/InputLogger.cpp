#include "InputLogger.h"

InputLogger::InputLogger(const std::string& newOutputFile) : Logger(newOutputFile) {
}

InputLogger& InputLogger::Instance() {
    InputLogger* instance = new InputLogger();
    return *instance;
}