#include "Logger.h"

Logger::Logger(const std::string& newOutputFile) : outputFile(newOutputFile) {
}

Logger& Logger::Instance() {
    Logger* instance = new Logger();
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
    std::string fullMessage = "[" + std::string(buffer) + "]" + "\t" + logMessage + "\n";
    FileWriter::WriteToFile(outputFile, fullMessage, FileWriter::Mode::APPEND);
}

void Logger::LogMessage(const std::string& msg) {
    Write("[MESSAGE]\t" + msg);
}

void Logger::LogWarning(const std::string& msg) {
    Write("[WARNING]\t" + msg);
}

void Logger::LogError(const std::string& msg) {
    Write("[*ERROR*]\t" + msg);
}