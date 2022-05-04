#pragma once

#ifndef Logger_H
#define Logger_H

#include <string>
#include <fstream>
#include <ctime>
#include <iomanip>
#include "../FileWriter/FileWriter.h"

class Logger : public FileWriter {
public:
    static Logger& Instance();
    virtual void LogMessage(const std::string& msg);
    virtual void LogWarning(const std::string& msg);
    virtual void LogError(const std::string& msg);

protected:
    explicit Logger(const std::string& newOutputFile = "game.log");
    Logger& operator=(const Logger&) = delete;
    Logger(const Logger&) = delete;
    virtual ~Logger() = default;

    void Write(const std::string& logMessage);
    const std::string outputFile;
};

#endif
