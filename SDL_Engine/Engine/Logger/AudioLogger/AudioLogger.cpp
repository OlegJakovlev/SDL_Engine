#include "AudioLogger.h"

AudioLogger::AudioLogger(const std::string& newOutputFile) : Logger(newOutputFile) {
}

AudioLogger& AudioLogger::Instance() {
    AudioLogger* instance = new AudioLogger();
    return *instance;
}

void AudioLogger::LogMessage(const std::string& msg) {
    Write("[AUDIO][MESSAGE] " + msg);
}

void AudioLogger::LogWarning(const std::string& msg) {
    Write("[AUDIO][WARNING] " + msg);
}

void AudioLogger::LogError(const std::string& msg) {
    Write("[AUDIO][*ERROR*] " + msg);
}