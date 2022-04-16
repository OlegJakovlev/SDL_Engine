#include "AudioLogger.h"

AudioLogger::AudioLogger(const std::string& newOutputFile) : Logger(newOutputFile) {
}

AudioLogger& AudioLogger::Instance() {
    AudioLogger* instance = new AudioLogger();
    return *instance;
}