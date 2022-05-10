#include "Logger.h"

Logger::Logger(const std::string& newOutputFile) : outputFile(newOutputFile) {
}

Logger& Logger::Instance() {
    static Logger* instance = new Logger();
    return *instance;
}

void Logger::Write(const std::string& logMessage) {
    // Get current time for logging purposes
    char buffer[32];
    struct tm newtime;
    time_t now = time(nullptr);
    localtime_s(&newtime, &now);
    strftime(buffer, sizeof buffer, "%Y-%m-%d %H:%M:%S", &newtime);

    // Write to file
    std::string fullMessage = "[" + std::string(buffer) + "]" + logMessage;
    FileWriter::WriteToFile(outputFile, fullMessage, FileWriter::Mode::APPEND);

    // Log to console
    std::printf("%s\n", fullMessage.c_str());
}

void Logger::LogMessage(const std::string& msg) {
    Write("[GENERAL][MESSAGE] " + msg);
}

void Logger::LogWarning(const std::string& msg) {
    Write("[GENERAL][WARNING] " + msg);
}

void Logger::LogError(const std::string& msg) {
    Write("[GENERAL][*ERROR*] " + msg);
}