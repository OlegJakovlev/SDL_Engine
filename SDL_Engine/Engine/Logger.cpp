#include "Logger.h"

Logger::Logger() {
}

Logger& Logger::Instance() {
    static Logger* instance = new Logger();
    return *instance;
}

void Logger::WriteToFile(std::string logMessage) {
    std::ofstream myLogFile;

    // Open in append mode
    myLogFile.open(outputFile, std::ios_base::app);

    if (!myLogFile.is_open()) return;

    // Get current time for logging purposes
    char buffer[32];
    struct tm newtime;
    time_t now = time(0);
    localtime_s(&newtime, &now);
    strftime(buffer, sizeof buffer, "%Y-%m-%d %H:%M:%S", &newtime);

    // Write to file
    myLogFile << "[" << buffer << "]" << "\t" << logMessage << "\n";

    myLogFile.close();
}

void Logger::LogMessage(std::string msg) {
    WriteToFile("[MESSAGE]\t" + msg);
}

void Logger::LogWarning(std::string msg) {
    WriteToFile("[WARNING]\t" + msg);
}

void Logger::LogError(std::string msg) {
    WriteToFile("[*ERROR*]\t" + msg);
}