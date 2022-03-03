#pragma once

#ifndef Logger_H
#define Logger_H

#include <string>
#include <fstream>
#include <ctime>
#include <iomanip>

class Logger {
public:
    static Logger& Instance();
    void LogMessage(std::string msg);
    void LogWarning(std::string msg);
    void LogError(std::string msg);

protected:
    Logger();
    Logger& operator=(const Logger&) = delete;
    Logger(const Logger&) = delete;

    void WriteToFile(std::string logMessage);
    std::string outputFile = "something.log";
};

#endif
